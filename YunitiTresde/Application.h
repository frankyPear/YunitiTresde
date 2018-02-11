#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include<list>
#include "Module.h"
#include "Timer.h"


class ModuleRenderer;
class ModuleWindow;
class ModuleInput;
class ModuleImGui;
class ModuleCamera;
class ModuleTextures;
class ModuleScene;
class ModuleImGui;
class ModuleResources;
class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	void StartTimer();
	void CalculateDt();
	
public:
	ModuleRenderer* renderer;
	ModuleWindow* window;
	ModuleInput* input;
	ModuleImGui* imgui;
	ModuleCamera* cam;
	ModuleTextures* textures;
	ModuleScene* scene;
	ModuleResources *resources;
	bool switchmap = false;
private:
	Timer ms_timer_;
	float dt_;
	float startTime_;
	std::list<Module*> modules;

};

extern Application* App;

#endif // __APPLICATION_CPP__