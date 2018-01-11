#include "Globals.h"
#include "Application.h"
#include "ModuleTimer.h"

#include <SDL_mixer.h>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>


ModuleTimer::ModuleTimer(bool start_enabled) : Module(start_enabled)
{
}

ModuleTimer::~ModuleTimer()
{}

// Load assets
bool ModuleTimer::Start()
{
	LOG("Loading Timer");
	secondsRealTime = 0;
	return true;
}
// UnLoad assets
bool ModuleTimer::CleanUp()
{
	LOG("Unloading timer");

	return true;
}

update_status ModuleTimer::Update()
{
	if(secondsRealTime>=60)	secondsRealTime = 0;
	Sleep(1000);
	secondsRealTime++;
	return UPDATE_CONTINUE;
}


