#ifndef _TIMER_

#define _TIMER_

#include "Globals.h"
#include "SDL\include\SDL.h"

class Timer 
{
public:
	Timer();
	~Timer();

	void Start();
	void Stop();

	Uint32 Read();

private:
	bool running;
	Uint32	started_at;
	Uint32	stopped_at;
	Uint32  pausedTimeStart;
	Uint32  pausedTimeStop;
	Uint32  totalPausedTime;
};

#endif // !_TIMER_

