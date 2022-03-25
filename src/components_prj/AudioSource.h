#pragma once
#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

#include <ecs_prj/Component.h>
namespace K_Engine {
	class AudioManager;
}

class AudioSource : public Component
{
public:
	AudioSource(Entity* e);
	~AudioSource();
	static std::string GetId();

	void playSong(const char* path);
	void playSoundEffect(const char* path, int nLoop);

	int getMusicVolume();
	int getEffectVolume();
	void setGeneralVolume(int vol);
	void setMusicVolume(int vol);
	void setEffectVolume(int vol);
	
	void stopAudio();
	void pauseAudio();
	void resumeAudio();

	// void stopSoundEffect // Parar X efecto de sonido en especifico (Aplicable para play,pause y resume)
	//virtual void debug();
	//virtual void update();
	//virtual void onEnable();
	//virtual void onDisable();

private:

	//Required
	static std::string name;

	// Volume of audio
	int musicVolume;
	int effectVolume;

	K_Engine::AudioManager* audioM;
};

#endif // AUDIOSOURCE_H