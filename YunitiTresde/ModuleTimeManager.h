#ifndef __MODULETIMEMANAGER__
#define __MODULETIMEMANAGER__

#include "Module.h"
#include "Timer.h"
#include "Globals.h"

class ModuleTimeManager : public Module
{
public:

	ModuleTimeManager(bool start_enabled = true);
	~ModuleTimeManager();

	bool Start();
	update_status Update();
	

public:
	int secondsRealTime;

private:


};

#endif // __APPLICATION_CPP__