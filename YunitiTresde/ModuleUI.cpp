#include "ModuleUI.h"
#include "OpenGL.h"


ModuleUI::ModuleUI()
{
}

ModuleUI::~ModuleUI()
{
}

bool ModuleUI::Init()
{
	return true;
}

bool ModuleUI::Start()
{
	return true;
}

update_status ModuleUI::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleUI::Update(float dt)
{
	//adding screenUI
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, 640, 480, 0.0f, 1.0f, -1.0f);

	return UPDATE_CONTINUE;
}

bool ModuleUI::CleanUp()
{
	return true;
}
