#ifndef __MODULESTIMER_H__
#define __MODULESTIMER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"



class ModuleTimer : public Module
{
public:
	ModuleTimer(bool start_enabled = true);
	~ModuleTimer();

	bool Start();
	update_status Update();
	bool CleanUp();
	
public:
	int secondsRealTime;	
private:

};

#endif // __MODULETimer_H__


