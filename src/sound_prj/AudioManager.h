#pragma once
#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

typedef struct _Mix_Music Mix_Music;
class Mix_Chunk;

#include <memory>

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	static AudioManager* GetInstance();

	static bool Init();
	static bool Shutdown();

	void update() {};

	void playWAV(const char* path);
	void playMUS(const char* path);

private:
	static std::unique_ptr<AudioManager> instance;

	Mix_Chunk* wav = nullptr;
	Mix_Music* mus = nullptr;

	void loadWAV(const char* path);
	void loadMUS(const char* path);
};
#endif // AUDIOMANAGER_H
