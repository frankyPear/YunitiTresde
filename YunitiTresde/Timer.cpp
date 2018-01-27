#include "Timer.h"


Timer::Timer()
{
	Start();
}

Timer::~Timer()
{

}

// ---------------------------------------------
void Timer::Start()
{
	running_ = true;
	started_at_ = SDL_GetTicks();
}


// ---------------------------------------------
void Timer::Stop()
{
	running_ = false;
	stopped_at_ = SDL_GetTicks();
	pausedTimeStart_ = SDL_GetTicks();
}


// ---------------------------------------------
Uint32 Timer::Read()
{
	if (running_ == true)
	{
		return SDL_GetTicks() - started_at_;
	}
	else
	{
		return stopped_at_ - started_at_;
	}
}


