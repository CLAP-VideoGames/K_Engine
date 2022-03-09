#include "InputManager.h"

#include <iostream>

#include <SDL.h>
#include <SDL_syswm.h>

std::unique_ptr<InputManager> InputManager::instance = nullptr;

InputManager::InputManager() = default;

InputManager::~InputManager() = default;

InputManager* InputManager::getInstance()
{
	return instance.get();
}

bool InputManager::Init()
{
	instance.reset(new InputManager());
	Uint32 SDL_system_init = SDL_WasInit(SDL_INIT_EVERYTHING);
	if (!SDL_system_init)
		std::cout << "SDL not initialized\n";
	return true;
}

bool InputManager::Shutdown()
{
	instance.reset(nullptr);

	return true;
}
