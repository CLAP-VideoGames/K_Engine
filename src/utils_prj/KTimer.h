#pragma once
#ifndef CUSTOMTIMER_H
#define CUSTOMTIMER_H

namespace K_Engine {
	class KTimer {
	public:
		KTimer();
		~KTimer();

		void reset();
		unsigned int currTime() const;
		void pause();
		void resume();

	private:
		bool paused;
		unsigned int startTime;
		unsigned int pauseTime;
	};
}
#endif // CUSTOMTIMER_H