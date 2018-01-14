#pragma once
#include "Module.h"
#include "..\json.hpp"
#include <iostream>
#include "Mathgeolib\Math\float3.h"

using json = nlohmann::json;

class ModuleTest :
	public Module
{
public:
	ModuleTest();
	~ModuleTest();

	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();

public:
	json j;
	float3 f;
};

