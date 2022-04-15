#pragma once
#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

#include <ecs_prj/Component.h>

namespace K_Engine {
	class AudioManager;
	class __declspec(dllexport) AudioSource : public Component
	{
	public:
		AudioSource(Entity* e);
		virtual ~AudioSource();

		static std::string GetId();

		// Play Audio
		void playSong(const char* path);
		void playSoundEffect(const char* path, int nLoop);

		// Volume
		int getMusicVolume();
		int getEffectVolume();
		void setGeneralVolume(int vol);
		void setMusicVolume(int vol);
		void setEffectVolume(int vol);

		// All Audio
		void stopAudio();
		void pauseAudio();
		void resumeAudio();

		// One specific sound effect
		void stopOneSoundEffect(const char* path);
		void pauseOneSoundEffect(const char* path);
		void resumeOneSoundEffect(const char* path);

	private:

		//Required
		static std::string name;

		// Volume of audio
		int musicVolume;
		int effectVolume;

		K_Engine::AudioManager* audioM;
	};
}
#endif // AUDIOSOURCE_H