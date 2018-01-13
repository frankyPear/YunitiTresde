#pragma once
#include "Module.h"
class ModuleWindow :
	public Module
{
public:
	ModuleWindow();
	~ModuleWindow();

	bool Init();
	bool Start();
	update_status Update(float deltaTime);
	bool CleanUp();
};

