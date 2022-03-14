#include "EngineTimer.h"

#include <SDL_timer.h>

EngineTimer::EngineTimer() 
{
	reset();
}

EngineTimer::~EngineTimer() = default;

void EngineTimer::reset()
{
	startTime = SDL_GetTicks();
	paused = false;
}

unsigned int EngineTimer::currTime() const 
{
	return paused ? pauseTime - startTime : SDL_GetTicks() - startTime;
}

void EngineTimer::pause()
{
	if (!paused) {
		paused = true;
		pauseTime = SDL_GetTicks();
	}
}

void EngineTimer::resume()
{
	if (paused) {
		startTime += (SDL_GetTicks() - pauseTime);
		paused = false;
	}
}