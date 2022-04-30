#pragma once
#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <memory>
#include <unordered_map>

typedef struct _Mix_Music Mix_Music;
class Mix_Chunk;

namespace K_Engine {
	enum class AudioType {
		SOUND_EFFECT,
		MUSIC
	};

	struct Audio {
		const char* audio_path;
		AudioType type;
		union {
			Mix_Chunk* sfx; // Wav file
			Mix_Music* mus; // OGG file (MP3 and other files not available)
		};
		int channel;
	};

	class  __declspec(dllexport) AudioManager {
	public:
		AudioManager();
		~AudioManager();

		static AudioManager* GetInstance();

		static bool Init();
		static bool Shutdown();

		Mix_Chunk* loadSFX(const char* path);
		Mix_Music* loadMUS(const char* path);

		void play(Audio* aud, int vol, int loop = 0);
		void pause(Audio* aud);
		void resume(Audio* aud);
		void stop(Audio* aud);

		bool hasEnded(Audio* aud);

		void setMasterVolume(float newVol);
		void setMusicVolume(float newVol);
		void setSFXVolume(float newVol);

		float getMasterVolume();
		float getMusicVolume();
		float getSFXVolume();

	private:
		static std::unique_ptr<AudioManager> instance;

		// 0 -> muted; 1 -> full
		float masterVolume, musicVolume, sfxVolume;

		void initAudio();
		void closeAudio();
	};
}
#endif // AUDIOMANAGER_H