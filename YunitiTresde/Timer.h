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
	bool running_;
	Uint32	started_at_;
	Uint32	stopped_at_;
	Uint32  pausedTimeStart_;
	Uint32  pausedTimeStop_;
	Uint32  totalPausedTime_;
};

#endif // !_TIMER_

