#ifndef __MODULEWINDOW_H__
#define __MODULEWINDOW_H__

#include "Module.h"


class ModuleWindow : public Module
{
public:

	ModuleWindow();

	// Destructor
	virtual ~ModuleWindow();

	// Called before quitting
	bool Init();

	// Called before quitting
	bool CleanUp();


public:

};

#endif // __MODULEWINDOW_H__