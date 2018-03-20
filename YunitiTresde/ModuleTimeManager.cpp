#pragma once
#include "Globals.h"
#include "Application.h"
#include "ModuleTimeManager.h"
#include <Windows.h>



ModuleTimeManager::ModuleTimeManager(bool start_enabled)
{
}

ModuleTimeManager::~ModuleTimeManager()
{
}

bool ModuleTimeManager::Start()
{
	LOG("Loading Timer");
	secondsRealTime = 0;
	return true;
}

update_status ModuleTimeManager::Update()
{
	if (secondsRealTime >= 60)	secondsRealTime = 0;
	Sleep(1000);
	secondsRealTime++;
	return UPDATE_CONTINUE;
}
