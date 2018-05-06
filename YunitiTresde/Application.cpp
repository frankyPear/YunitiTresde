#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer.h"
#include "ModuleInput.h"
#include "ModuleImGui.h"
#include "ModuleCamera.h"
#include "ModuleTextures.h"
#include "ModuleScene.h"
#include "ModuleImGui.h"
#include "ModuleFX.h"
#include "ModuleAnimation.h"
#include "ModuleRNG.h"
#include "ModuleUI.h"
#include "ModuleAudio.h"
#include "ModuleShader.h"

//Included mathgeolib
#include "Mathgeolib\include\MathBuildConfig.h"
#include "Mathgeolib\include\MathGeoLib.h"
#include <thread>

using namespace std;

Application::Application()
{
	// Order matters: they will init/start/pre/update/post in this order
	
	input = new ModuleInput();
	window = new ModuleWindow();
	renderer = new ModuleRenderer();
	imgui = new ModuleImGui();
	cam = new ModuleCamera();
	textures = new ModuleTextures();
	anim = new ModuleAnimation();
	scene = new ModuleScene();
	fx = new ModuleFX();
	rng = new ModuleRNG();
	ui = new ModuleUI();
	audio = new ModuleAudio();
	shader = new ModuleShader();

	modules.push_back(input);
	modules.push_back(window);
	modules.push_back(renderer);
	modules.push_back(imgui);
	modules.push_back(cam);
	modules.push_back(audio);
	modules.push_back(textures);
	modules.push_back(anim);
	modules.push_back(rng);
	modules.push_back(fx);
	modules.push_back(scene);
	modules.push_back(shader);
	modules.push_back(ui);
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
			ret = (*it)->Init(); 
	
		for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		{
			if ((*it)->IsEnabled() == true)
				ret = (*it)->Start();
		}
	

	return ret;
}


update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	StartTimer();

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->PreUpdate(dt_);

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->Update(dt_);

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->PostUpdate(dt_);

	CalculateDt();
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

void Application::StartTimer()
{
	ms_timer_.Start();
	startTime_ = (float)ms_timer_.Read() / 1000.0f;
}

void Application::CalculateDt()
{
	dt_ =(float) ms_timer_.Read() / 1000.0f - startTime_;
}