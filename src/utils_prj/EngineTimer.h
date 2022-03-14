#ifndef CUSTOMTIMER_H
#define CUSTOMTIMER_H

class EngineTimer
{
public:
	EngineTimer();
	~EngineTimer();

	void reset();
	unsigned int currTime() const;
	void pause();
	void resume();

private:
	bool paused;
	unsigned int startTime;
	unsigned int pauseTime;
};
#endif // CUSTOMTIMER_H