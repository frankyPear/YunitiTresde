#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"

ModuleRender::ModuleRender()
{

}

// Destructor
ModuleRender::~ModuleRender()
{}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;


	return ret;
}

update_status ModuleRender::PreUpdate()
{
	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update()
{

	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");


	return true;
}

