#include "KTimer.h"

#include <SDL_timer.h>

namespace K_Engine {
	KTimer::KTimer()
	{
		reset();
	}

	KTimer::~KTimer() = default;

	void KTimer::reset()
	{
		startTime = SDL_GetTicks();
		paused = false;
	}

	unsigned int KTimer::currTime() const
	{
		return paused ? pauseTime - startTime : SDL_GetTicks() - startTime;
	}

	void KTimer::pause()
	{
		if (!paused) {
			paused = true;
			pauseTime = SDL_GetTicks();
		}
	}

	void KTimer::resume()
	{
		if (paused) {
			startTime += (SDL_GetTicks() - pauseTime);
			paused = false;
		}
	}
}