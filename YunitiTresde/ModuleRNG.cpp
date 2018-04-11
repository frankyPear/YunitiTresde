#include "ModuleRNG.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>


using namespace std;

ModuleRNG::ModuleRNG()
{

}


ModuleRNG::~ModuleRNG()
{
}


int ModuleRNG::GetRandomNumber()
{
	return lcg.Int();
}

bool ModuleRNG::Init()
{
	return true;
}

bool ModuleRNG::Start()
{
	lcg = LCG();
	return true;
}

update_status ModuleRNG::Update(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleRNG::CleanUp() 
{
	return true;
}

float ModuleRNG::GetRandomNumberFloat()
{
	return lcg.Float();
}

float ModuleRNG::GetRandomNumberRangeFloat(float min, float max)
{
	return lcg.Float(min,max);
}