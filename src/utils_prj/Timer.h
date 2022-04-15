#pragma once
#ifndef TIMER_H
#define TIMER_H

namespace K_Engine {
	class  __declspec(dllexport) Timer {
	public:
		Timer();
		~Timer();

		/// <summary>
		/// Resets the timer to its initial value
		/// </summary>
		void reset();

		/// <summary>
		/// Returns the current value of the timer
		/// </summary>
		unsigned int currTime() const;

		/// <summary>
		/// Pause the timer
		/// </summary>
		void pause();

		/// <summary>
		/// Resume the timer
		/// </summary>
		void resume();

	private:
		bool paused;
		unsigned int startTime;
		unsigned int pauseTime;
	};
}
#endif //TIMER_H