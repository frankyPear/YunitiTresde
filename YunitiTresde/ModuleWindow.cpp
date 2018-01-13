#include "ModuleWindow.h"



ModuleWindow::ModuleWindow()
{
}


ModuleWindow::~ModuleWindow()
{
}

bool ModuleWindow::Init() {
	return true;
}

bool ModuleWindow::Start() {
	return true;
}

update_status ModuleWindow::Update(float deltaTime) {
	return UPDATE_CONTINUE;
}

bool ModuleWindow::CleanUp() {
	return true;
}