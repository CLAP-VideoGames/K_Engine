/*
 * Copyright (c) 2018, 2019 Amine Ben Hassouna <amine.benhassouna@gmail.com>
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any
 * person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the
 * Software without restriction, including without
 * limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software
 * is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice
 * shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF
 * ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
 * SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 * IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

//#include <stdbool.h>
#include <iostream>

#include <SDL.h> // Esto da error
#include <SDL_mixer.h>

//#define WAVES_SOUND "assets/clap.wav"

//#define CLAP_SOUND             
//#define SNARE_SOUND             "assets/snare.mp3"
//#define TECHNO_CLAP_SNARE_SOUND "assets/claps-and-snares/snare.mp3"
//#define REVERB_SNARE_SOUND      "assets/claps-and-snares/dubstep-reverb-snare.ogg"



int main(int argc, char* argv[])
{
	const char* SNARE_SOUND = "assets/snare.mp3";
	const char* WAVES_SOUND = "assets/clap.wav";

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		/*printf("SDL could not be initialized!\n"
			"SDL_Error: %s\n", SDL_GetError());
		return 0;*/

	}

	//Initialize SDL2_mixer
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		/*printf("SDL2_mixer could not be initialized!\n"
			"SDL_Error: %s\n", SDL_GetError());
		return 0;*/
		std::cout << "SDL2_mixer could not be initialized \n";
	}

	// Load .WAV sound
	Mix_Chunk* waves = Mix_LoadWAV(WAVES_SOUND);
	if (!waves)
	{
		/*printf(".WAV sound '%s' could not be loaded!\n"
			"SDL_Error: %s\n", WAVES_SOUND, SDL_GetError());*/
		std::cout << ".wav sound could not be loaded \n";
		return 0;
	}

	// Load .OGG sounds
	//Mix_Music* clapnsnare1 = Mix_LoadMUS(CLAP_SOUND);
	Mix_Music* clapnsnare2 = Mix_LoadMUS(SNARE_SOUND);
	//Mix_Music* clapnsnare3 = Mix_LoadMUS(TECHNO_CLAP_SNARE_SOUND);
	//Mix_Music* clapnsnare4 = Mix_LoadMUS(REVERB_SNARE_SOUND);
	if (!clapnsnare2)
	{
		std::cout << "One of the .mp3 sounds could not be loaded!\n SDL_Error: ";
		std::cout << SDL_GetError();
		return 0;
	}

	// Play waves sound
	if (Mix_PlayChannel(-1, waves, 0) == -1)
	{
		std::cout << "Waves sound could not be played!\n SDL_Error: ";
		std::cout << SDL_GetError();

		Mix_FreeChunk(waves);
		return 0;
	}

	// Event loop exit flag
	bool quit = false;

	// Event loop
	while (!quit)
	{
		SDL_Event e;

		// Wait indefinitely for the next available event
		SDL_WaitEvent(&e);

		// User requests quit
		if (e.type == SDL_QUIT)
		{
			quit = true;
		}
		else if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_SPACE:
				if (Mix_Paused(-1))
					Mix_Resume(-1);
				else
					Mix_Pause(-1);
				break;

			case SDLK_RIGHT:
				/*if (Mix_PlayMusic(clapnsnare1, 1) == -1)
				{
					printf(".OGG sound could not be played!\n"
						"SDL_Error: %s\n", SDL_GetError());
				}*/
				break;

			case SDLK_LEFT:
				if (Mix_PlayMusic(clapnsnare2, 1) == -1)
				{
					/*printf(".OGG sound could not be played!\n"
						"SDL_Error: %s\n", SDL_GetError());*/
					std::cout << (".mp3 sound could not be played\n"
						"SDL_Error: %s\n", SDL_GetError());
				}
				break;

			case SDLK_UP:
				/*if (Mix_PlayMusic(clapnsnare3, 1) == -1)
				{
					printf(".OGG sound could not be played!\n"
						"SDL_Error: %s\n", SDL_GetError());
				}*/
				break;

			case SDLK_DOWN:
				/*if (Mix_PlayMusic(clapnsnare4, 1) == -1)
				{
					printf(".OGG sound could not be played!\n"
						"SDL_Error: %s\n", SDL_GetError());
				}*/
				break;
			}
		}
	}

	// Clean up audio
	Mix_FreeChunk(waves);
	//Mix_FreeMusic(clapnsnare1);
	Mix_FreeMusic(clapnsnare2);
	//Mix_FreeMusic(clapnsnare3);
	//Mix_FreeMusic(clapnsnare4);

	// Quit SDL2_mixer
	Mix_CloseAudio();

	// Quit SDL
	SDL_Quit();

	return 0;
}

