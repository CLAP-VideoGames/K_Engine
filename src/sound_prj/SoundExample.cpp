#include "SoundExample.h"

#include <iostream>
#include <string>

#include <SDL.h> 
#include <SDL_mixer.h>

SoundExample::SoundExample() 
{
	init();
}

SoundExample::~SoundExample()
{
	shutdown();
}

void SoundExample::init() {
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) 
		std::cout << "SDL could not be initialized!\n";

	//Initialize SDL2_mixer
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		std::cout << "SDL2_mixer could not be initialized!\n";
}

void SoundExample::loadWAV(const char* path)
{
	wav = Mix_LoadWAV(path);

	if (!wav) 
		std::cout << ".wav sound could not be loaded \n";
}

void SoundExample::loadMP3(const char* path)
{
	mus = Mix_LoadMUS(path);

	if (!mus)
		std::cout << ".wav sound could not be loaded \n";
}

void SoundExample::playWAV(const char* path)
{
	loadWAV(path);

	if (Mix_PlayChannel(-1, wav, 0) == -1)
		std::cout << "WAV sound could not be played!\n";
}

void SoundExample::playMP3(const char* path)
{
	loadMP3(path);

	if (Mix_PlayMusic(mus, 0) == -1)
		std::cout << "MP3 sound could not be played!\n";
}

void SoundExample::shutdown()
{
	Mix_FreeChunk(wav);
	Mix_FreeMusic(mus);

	Mix_CloseAudio();

	SDL_Quit();
}