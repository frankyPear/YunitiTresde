#pragma once
#include "Module.h"
#include "Mathgeolib\include\Algorithm\Random\LCG.h"

class ModuleRNG :
	public Module
{
public:
	ModuleRNG();
	~ModuleRNG();

	bool Init();
	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	int GetRandomNumber();
	float GetRandomNumberFloat();
	float GetRandomNumberRangeFloat(float min, float max);

public:
	LCG lcg;
};

