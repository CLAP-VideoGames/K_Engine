#include "Timer.h"

#include <SDL_timer.h>

namespace K_Engine {
	Timer::Timer(){
		reset();
	}

	Timer::~Timer() = default;

	void Timer::reset()
	{
		startTime = SDL_GetTicks();
		paused = false;
	}

	unsigned int Timer::currTime() const
	{
		return paused ? pauseTime - startTime : SDL_GetTicks() - startTime;
	}

	void Timer::pause()
	{
		if (!paused) {
			paused = true;
			pauseTime = SDL_GetTicks();
		}
	}

	void Timer::resume()
	{
		if (paused) {
			startTime += (SDL_GetTicks() - pauseTime);
			paused = false;
		}
	}
}