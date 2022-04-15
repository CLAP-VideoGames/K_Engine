#pragma once
#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <memory>
#include <unordered_map>

typedef struct _Mix_Music Mix_Music;
class Mix_Chunk;

namespace K_Engine {
	class  __declspec(dllexport) AudioManager {
	public:
		AudioManager();
		~AudioManager();

		static AudioManager* GetInstance();

		static bool Init();
		static bool Shutdown();

		void update() {};

		void playWAV(const char* path, int vol,int loop = 0);
		void playMUS(const char* path, int loop = 0);

		void pauseMUS();
		void pauseWAV(int channel);

		void resumeMUS();
		void resumeWAV(int channel);

		void stopMUS();
		void stopWAV(int channel);

		void setVolumeWAV(int channel, int vol);
		void setVolumeMUS(int vol);

		int locateAudioFile(const char* path,bool add);

	private:
		static std::unique_ptr<AudioManager> instance;
		
		// Organize all audio files and its asigned channel
		std::unordered_map<std::string, int> AudioAndChannel;
		int lastChannel = 0;

		// Wav file
		Mix_Chunk* wav = nullptr; 
		
		// OGG file (MP3 and other files not available)
		Mix_Music* mus = nullptr;
		
		void loadWAV(const char* path);
		void loadMUS(const char* path);
	};
}
#endif // AUDIOMANAGER_H