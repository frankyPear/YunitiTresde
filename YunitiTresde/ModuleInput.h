#pragma once
#include "Module.h"
class ModuleInput :
	public Module
{
public:
	ModuleInput();
	~ModuleInput();

	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();
};

