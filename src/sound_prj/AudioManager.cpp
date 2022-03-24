#include "AudioManager.h"

#include <iostream>
#include <string>

#include <SDL.h> 
#include <SDL_mixer.h>
#include <fmod.h>

namespace K_Engine {
	std::unique_ptr<AudioManager> AudioManager::instance = nullptr;

	AudioManager::AudioManager() = default;

	AudioManager::~AudioManager() = default;

	AudioManager* AudioManager::GetInstance() {
		return instance.get();
	}

	bool AudioManager::Init() {
		instance.reset(new AudioManager());

		// Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
			std::cout << "SDL could not be initialized!\n";

		//Initialize SDL2_mixer
		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
			std::cout << "SDL2_mixer could not be initialized!\n";

		return true;
	}

	bool AudioManager::Shutdown()
	{
		Mix_FreeChunk(instance->wav);
		Mix_FreeMusic(instance->mus);

		Mix_CloseAudio();

		SDL_Quit();

		instance.reset(nullptr);

		return true;
	}

	//-------------------------------------------------------------------------------

	// It loads a WAV file 
	void AudioManager::loadWAV(const char* path)
	{
		wav = Mix_LoadWAV(path);

		if (!wav)
			std::cout << "WAV sound could not be loaded \n";
	}

	// It loads a OGG file (MP3 and other not available)
	void AudioManager::loadMUS(const char* path)
	{
		mus = Mix_LoadMUS(path);

		if (!mus)
			std::cout << "MUS sound could not be loaded \n";
	}

	//-------------------------------------------------------------------------------

	void AudioManager::playWAV(const char* path, int vol, int loop)
	{
		// Load and set volume
		loadWAV(path);
		Mix_VolumeChunk(wav, vol);

		if (Mix_PlayChannel(-1, wav, loop) == -1)
			std::cout << "WAV sound could not be played!\n";
	}

	void AudioManager::playMUS(const char* path, int loop)
	{
		loadMUS(path);

		if (Mix_PlayMusic(mus, loop) == -1)
			std::cout << "MUS sound could not be played!\n";
	}

	//-------------------------------------------------------------------------------

	void AudioManager::pauseMUS()
	{
		if (mus != nullptr)
		{
			//if(Mix_PlayingMusic())
			Mix_PauseMusic();
		}
		else
		{
			std::cout << "There is no MUS to pause\n";
		}
	}

	void AudioManager::pauseWAV(int channel)
	{
		// If channel = -1, then all channels will be paused
		// If channel = -1, then all channels will be resumed
		// If channel exists and it's not paused, then it will be resumed
		if (channel == -1 || (Mix_GetChunk(channel) != nullptr && !Mix_Paused(channel)))
		{
			Mix_Pause(channel);
		}
		else
		{
			std::cout << "There is no WAV to pause\n";
		}
	}

	//-------------------------------------------------------------------------------

	void AudioManager::resumeMUS()
	{
		if (mus != nullptr)
		{
			Mix_ResumeMusic(); // This is safe to use on halted, paused, and already playing music.
		}
		else
		{
			std::cout << "There is no MUS to resume\n";
		}
	}

	void AudioManager::resumeWAV(int channel)
	{
		// Resume an especific WAV if it's paused
		// If channel = -1, then all channels will be resumed
		// If channel exists and it's paused, then it will be resumed
		if (channel == -1 || (Mix_GetChunk(channel) != nullptr && Mix_Paused(channel)))
		{
			Mix_Resume(channel);
		}
		else
		{
			std::cout << "There is no WAV to resume\n";
		}
	}

	//-------------------------------------------------------------------------------

	void AudioManager::stopMUS()
	{
		if (mus != nullptr)
		{
			Mix_HaltMusic();
		}
		else
		{
			std::cout << "There is no MUS to pause\n";
		}
	}

	void AudioManager::stopWAV(int channel)
	{
		// If channel = -1, then all channels will be stopped
		// If the channel don't have a Mix_Chunk, then it's empty
		if (channel == -1 || Mix_GetChunk(channel) != nullptr)
		{
			Mix_HaltChannel(channel);
		}
		else
		{
			std::cout << "There is no WAV to pause\n";
		}
	}

	void AudioManager::setVolumeMUS(int vol)
	{
		if (vol > 0 && vol < 128)
		{
			Mix_VolumeMusic(vol);
		}
	}

	void AudioManager::setVolumeWAV(int channel, int vol)
	{
		if (vol > 0 && vol < 128)
		{
			Mix_Volume(channel, vol); // If channel = -1, all channel will have the same volume
		}
	}

	//-------------------------------------------------------------------------------
}