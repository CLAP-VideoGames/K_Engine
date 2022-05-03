#include "AudioManager.h"

#include <iostream>
#include <string>

#include <SDL_mixer.h>

#include <log_prj/LogManager.h>

#include <utils_prj/checkML.h>

namespace K_Engine {
	std::unique_ptr<AudioManager> AudioManager::instance = nullptr;

	AudioManager::AudioManager() = default;

	AudioManager::~AudioManager() = default;

	AudioManager* AudioManager::GetInstance() {
		return instance.get();
	}

	bool AudioManager::Init() {
		try {
			instance.reset(new AudioManager());

			instance.get()->initAudio();
		}
		catch (const std::exception& e) {
			return K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::FATAL, SDL_GetError());
		}

		return K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::INFO, "Audio manager initialization success");
	}

	bool AudioManager::Shutdown()
	{
		try {
			instance.get()->closeAudio();

			instance.reset(nullptr);
		}
		catch (const std::string e) {
			return K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::FATAL, SDL_GetError());
		}

		return K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::INFO, "Audio manager shutdown success");
	}

	//-------------------------------------------------------------------------------

	// It loads a WAV file 
	Mix_Chunk* AudioManager::loadSFX(const char* path)
	{
		Mix_Chunk* sfx = Mix_LoadWAV(path);
		if (!sfx) 
			K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::FATAL, "SFX sound could not be loaded \n");

		return sfx;
	}

	// It loads a OGG file (MP3 and other not available)
	Mix_Music* AudioManager::loadMUS(const char* path)
	{
		Mix_Music* mus = Mix_LoadMUS(path);
		if (!mus)
			K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::FATAL, "MUS sound could not be loaded \n");

		return mus;
	}

	//-------------------------------------------------------------------------------

	void AudioManager::play(Audio* aud, int loop)
	{
		playingAudios.push_back(aud);

		if (aud->type == AudioType::SOUND_EFFECT) {
			Mix_VolumeChunk(aud->sfx, masterVolume * sfxVolume * aud->volume * MIX_MAX_VOLUME);

			if (Mix_PlayChannel(aud->channel, aud->sfx, loop) == -1)
				// Gets the first empty channel and assign the audio file to that channel, and starts playing
				K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::WARNING, "SFX sound could not be played");
		}
		else {
			Mix_VolumeMusic(masterVolume * musicVolume * aud->volume * MIX_MAX_VOLUME);

			if (Mix_PlayMusic(aud->mus, loop) == -1)
				K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::WARNING, "Music sound could not be played");
		}
	}

	//-------------------------------------------------------------------------------

	void AudioManager::pause(Audio* aud)
	{
		if (aud->type == AudioType::SOUND_EFFECT) 
			Mix_Pause(aud->channel);
		else 
			Mix_PauseMusic();
	}

	//-------------------------------------------------------------------------------

	void AudioManager::resume(Audio* aud)
	{
		if (aud->type == AudioType::SOUND_EFFECT)
			Mix_Resume(aud->channel);
		else
			Mix_ResumeMusic();
	}

	//-------------------------------------------------------------------------------

	void AudioManager::stop(Audio* aud)
	{
		removePlayingAudio(aud);

		if (aud->type == AudioType::SOUND_EFFECT)
			Mix_HaltChannel(aud->channel);
		else
			Mix_HaltMusic();
	}

	//-------------------------------------------------------------------------------

	bool AudioManager::hasEnded(Audio* aud)
	{
		bool ended = false;
		if (aud->type == AudioType::SOUND_EFFECT)
			ended = !Mix_Playing(aud->channel);
		else
			ended = !Mix_PlayingMusic();

		if (ended)
			removePlayingAudio(aud);

		return ended;
	}

	//-------------------------------------------------------------------------------

	void AudioManager::setMasterVolume(float newVol) {
		masterVolume = newVol;
		setVolume();
	}

	void AudioManager::setMusicVolume(float newVol) {
		musicVolume = newVol;
		setVolume();
	}

	void AudioManager::setSFXVolume(float newVol) {
		sfxVolume = newVol;
		setVolume();
	}

	float AudioManager::getMasterVolume() {
		return masterVolume;
	}

	float AudioManager::getMusicVolume() {
		return musicVolume;
	}

	float AudioManager::getSFXVolume() {
		return sfxVolume;
	}

	//-------------------------------------------------------------------------------

	void AudioManager::initAudio() {
		//Initialize SDL2_mixer
		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
			throw std::exception("SDL2_mixer could not be initialized");

		masterVolume = musicVolume = sfxVolume = 1;
	}

	void AudioManager::closeAudio() {
		Mix_CloseAudio();
	}

	void AudioManager::setVolume() {
		for (size_t i = 0; i < playingAudios.size(); i++) {
			if (playingAudios[i]->type == AudioType::SOUND_EFFECT)
				Mix_VolumeChunk(playingAudios[i]->sfx, masterVolume * sfxVolume * playingAudios[i]->volume * MIX_MAX_VOLUME);
			else
				Mix_VolumeMusic(masterVolume * musicVolume * playingAudios[i]->volume * MIX_MAX_VOLUME);
		}
	}

	void AudioManager::removePlayingAudio(Audio* aud) {
		for (auto it = playingAudios.begin(); it != playingAudios.end(); ++it) {
			if (*it == aud) {
				playingAudios.erase(it);
				break;
			}
		}
	}
}