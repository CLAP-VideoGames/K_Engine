#include "AudioSource.h"
#include <sound_prj/AudioManager.h>
#include <ecs_prj/Entity.h>

namespace K_Engine {
	//Required
	std::string AudioSource::name = "AudioSource";

	AudioSource::AudioSource(Entity* e) : Component("AudioSource", e)
	{
		audioM = K_Engine::AudioManager::GetInstance();
		name = id;
		musicVolume = effectVolume = 50;
	}

	AudioSource::~AudioSource() {}

	std::string AudioSource::GetId() {
		return name;
	}

	/// <summary>
	/// If there's another song playing already, it will be replaced by the new one
	/// </summary>
	void AudioSource::playSong(const char* path)
	{
		audioM->playMUS(path, -1);
	}

	/// <summary>
	/// Play a certain sound effect, as many times as necessary
	/// </summary>
	void AudioSource::playSoundEffect(const char* path, int nLoop)
	{
		audioM->playWAV(path, effectVolume, nLoop);
	}

	/// <summary>
	/// Set the volume for Music and Sound Effects
	/// </summary>
	void AudioSource::setGeneralVolume(int vol)
	{
		setMusicVolume(vol);
		setEffectVolume(vol);
	}

	/// <summary>
	/// Set the volume of the Music
	/// </summary>
	void AudioSource::setMusicVolume(int vol)
	{
		musicVolume = vol;
		audioM->setVolumeMUS(vol);
	}

	/// <summary>
	/// Set the volume of ALL the sound effects
	/// </summary>
	void AudioSource::setEffectVolume(int vol)
	{
		effectVolume = vol;
		audioM->setVolumeWAV(-1, vol);
	}

	/// <summary>
	/// Returns the volume of the Music
	/// </summary>
	int AudioSource::getMusicVolume()
	{
		return musicVolume;
	}

	/// <summary>
	/// Returns the volume of the Sound effects
	/// </summary>
	int AudioSource::getEffectVolume()
	{
		return effectVolume;
	}

	/// <summary>
	/// Stops the Music and all the Sound Effects
	/// </summary>
	void AudioSource::stopAudio()
	{
		audioM->stopMUS();
		audioM->stopWAV(-1);
	}

	/// <summary>
	/// Pause all the Music and all the Sound Effects
	/// </summary>
	void AudioSource::pauseAudio()
	{
		audioM->pauseMUS();
		audioM->pauseWAV(-1);
	}

	/// <summary>
	/// Resume all the Music and all the Sound Effects
	/// </summary>
	void AudioSource::resumeAudio()
	{
		audioM->resumeMUS();
		audioM->resumeWAV(-1);
	}

	/// <summary>
	/// Stop the sound effect we introduce (if it doesn't exist, it will write an error message, but won't stop the program)
	/// </summary>
	void AudioSource::stopOneSoundEffect(const char* path)
	{
		audioM->stopWAV(audioM->locateAudioFile(path,false));
	}

	/// <summary>
	/// Pause the sound effect we introduce (if it doesn't exist, it will write an error message, but won't stop the program)
	/// </summary>
	void AudioSource::pauseOneSoundEffect(const char* path)
	{
		audioM->pauseWAV(audioM->locateAudioFile(path,false));
	}

	/// <summary>
	/// Resume the sound effect we introduce (if it doesn't exist or it's not paused, it will write an error message, but won't stop the program)
	/// </summary>
	void AudioSource::resumeOneSoundEffect(const char* path)
	{
		audioM->resumeWAV(audioM->locateAudioFile(path,false));
	}
}