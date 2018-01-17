#pragma once
#include "Module.h"
#include "..\json.hpp"
#include <iostream>
#include "Mathgeolib\include\MathBuildConfig.h"
#include"Mathgeolib\include\MathGeoLib.h"

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

