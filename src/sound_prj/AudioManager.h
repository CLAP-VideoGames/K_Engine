#pragma once
#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

typedef struct _Mix_Music Mix_Music;
class Mix_Chunk;

#include <memory>

namespace K_Engine {
	class AudioManager
	{
	public:
		AudioManager();
		~AudioManager();

		static AudioManager* GetInstance();

		static bool Init();
		static bool Shutdown();

		void update() {};

		void playWAV(const char* path, int loop = 0);
		void playMUS(const char* path, int loop = 0);

		void pauseMUS();
		void pauseWAV(int channel);

		void resumeMUS();
		void resumeWAV(int channel);

		void stopMUS();
		void stopWAV(int channel);

		void setVolumeWAV(int channel, int vol);
		void setVolumeMUS(int vol);
		int getVolumeWAV();
		int getVolumeMUS();

	private:
		static std::unique_ptr<AudioManager> instance;

		Mix_Chunk* wav = nullptr;
		Mix_Music* mus = nullptr;
		int volumeWAV = 50; // Values between 0 and 128
		int volumeMUS = 50; // Values between 0 and 128


		void loadWAV(const char* path);
		void loadMUS(const char* path);
	};
}
#endif // AUDIOMANAGER_H