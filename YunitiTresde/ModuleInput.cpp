#include "ModuleInput.h"



ModuleInput::ModuleInput()
{
}


ModuleInput::~ModuleInput()
{
}

bool ModuleInput::Init() {
	return true;
}

bool ModuleInput::Start() {
	return true;
}

update_status ModuleInput::Update() {
	return UPDATE_CONTINUE;
}

bool ModuleInput::CleanUp() {
	return true;
}