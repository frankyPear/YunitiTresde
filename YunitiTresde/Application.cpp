#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer.h"
#include "ModuleInput.h"
#include "ModuleTest.h"
//Included mathgeolib
#include "Mathgeolib\MathBuildConfig.h"
#include "Mathgeolib\MathGeoLib.h"
#include <thread>

using namespace std;

Application::Application()
{
	// Order matters: they will init/start/pre/update/post in this order
	modules.push_back(input = new ModuleInput());
	modules.push_back(window = new ModuleWindow());
	modules.push_back(renderer = new ModuleRenderer());
	modules.push_back(test = new ModuleTest());
}

Application::~Application()
{
	for (list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it)
		RELEASE(*it);
}

bool Application::Init()
{
	bool ret = true;

		for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
			ret = (*it)->Init(); // we init everything, even if not anabled
	
		for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		{
			if ((*it)->IsEnabled() == true)
				ret = (*it)->Start();
		}
	
		// Start the first scene

	return ret;
}


update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->PreUpdate();

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->Update();

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->PostUpdate();

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->CleanUp();

	return ret;
}


