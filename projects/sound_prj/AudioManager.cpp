#include "AudioManager.h"
#include <iostream>
#include <string>

#include <SDL.h> 
#include <SDL_mixer.h>

AudioManager* AudioManager::getInstance() {
	return instance.get();
}

void AudioManager::Init() {

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		std::cout << "SDL could not be initialized!\n";

	//Initialize SDL2_mixer
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		std::cout << "SDL2_mixer could not be initialized!\n";
}

void AudioManager::Shutdown()
{
	instance.reset(nullptr);
	Mix_FreeChunk(wav);
	Mix_FreeMusic(mus);

	Mix_CloseAudio();

	SDL_Quit();
}


/// <summary>
/// Load and Play audio sources
/// </summary>
void AudioManager::loadWAV(const char* path)
{
	wav = Mix_LoadWAV(path);

	if (!wav)
		std::cout << "WAV sound could not be loaded \n";
}

void AudioManager::loadMUS(const char* path)
{
	mus = Mix_LoadMUS(path);

	if (!mus)
		std::cout << "MUS sound could not be loaded \n";
}

void AudioManager::playWAV(const char* path)
{
	loadWAV(path);

	if (Mix_PlayChannel(-1, wav, 0) == -1)
		std::cout << "WAV sound could not be played!\n";
}

void AudioManager::playMUS(const char* path)
{
	loadMUS(path);

	if (Mix_PlayMusic(mus, 0) == -1)
		std::cout << "MUS sound could not be played!\n";
}

