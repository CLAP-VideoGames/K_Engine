#include "AudioSource.h"

#include <SDL_mixer.h>

#include <sound_prj/AudioManager.h>

#include <ecs_prj/Entity.h>

#include <utils_prj/K_Map.h>
#include <utils_prj/checkML.h>

namespace K_Engine {
	//Required
	std::string AudioSource::name = "AudioSource";

	std::string AudioSource::GetId() {
		return name;
	}

	AudioSource::AudioSource() : Component() {}

	AudioSource::AudioSource(Entity* e) : Component(e) {}

	AudioSource::AudioSource(Entity* e, AudioType type, std::string path, float vol, bool loop, bool start) {
		audio = new Audio;

		audio->audio_path = path;
		audio->type = type;

		volume = vol;

		loopable = loop;
		playStart = start;

		playing = false; paused = false;
	}

	AudioSource::~AudioSource() = default;

	void AudioSource::init(K_Map* information) {
		audio = new Audio;

		audio->audio_path = information->value("path").c_str();
		audio->type = (AudioType)information->valueToNumber("type");

		volume = information->valueToNumber("volume");

		loopable = information->valueToBool("loopable");
		playStart = information->valueToBool("playOnStart");

		playing = false; paused = false;
	}

	void AudioSource::start()
	{
		audioMan = AudioManager::GetInstance();

		if (audio->type == AudioType::SOUND_EFFECT) 
			audio->sfx = audioMan->loadSFX(audio->audio_path.c_str());
		else
			audio->mus = audioMan->loadMUS(audio->audio_path.c_str());

		if (playStart)
			play();
	}

	void AudioSource::update(int frameTime) {
		playing = audioMan->hasEnded(audio);
		paused = playing ? paused : playing;
	}

	/// <summary>
	/// If there's another song playing already, it will be replaced by the new one
	/// </summary>
	void AudioSource::play() {
		if (!playing) {
			audioMan->play(audio, volume, loopable ? -1 : 0);
			playing = true;
		}
	}

	/// <summary>
	/// Pause all the Music and all the Sound Effects
	/// </summary>
	void AudioSource::pause() {
		if (playing && !paused) {
			audioMan->pause(audio);
			paused = true;
		}
	}

	/// <summary>
	/// Resume all the Music and all the Sound Effects
	/// </summary>
	void AudioSource::resume() {
		if (playing && paused) {
			audioMan->resume(audio);
			paused = false;
		}
	}

	/// <summary>
	/// Stops the Music and all the Sound Effects
	/// </summary>
	void AudioSource::stop() {
		if (playing || paused) {
			audioMan->stop(audio);
			playing = false; paused = false;
		}
	}

	/// <summary>
	/// Set the volume for Music and Sound Effects
	/// </summary>
	void AudioSource::setVolume(float vol) {
		volume = vol;
	}

	/// <summary>
	/// Returns the volume of the Music
	/// </summary>
	float AudioSource::getVolume() {
		return volume;
	}
}