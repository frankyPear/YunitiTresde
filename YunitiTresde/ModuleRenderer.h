#pragma once
#include "Module.h"
class ModuleRenderer :
	public Module
{
public:
	ModuleRenderer();
	~ModuleRenderer();

	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();
};

