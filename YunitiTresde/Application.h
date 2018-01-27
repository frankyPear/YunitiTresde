#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include<list>
#include "Module.h"



class ModuleRenderer;
class ModuleWindow;
class ModuleInput;
class ModuleImGui;
class ModuleCamera;
class ModuleTextures;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	//void RerunTimer();

public:
	ModuleRenderer* renderer;
	ModuleWindow* window;
	ModuleInput* input;
	ModuleImGui* imgui;
	ModuleCamera* cam;
	ModuleTextures* textures;

	bool switchmap = false;
private:

	std::list<Module*> modules;

};

extern Application* App;

#endif // __APPLICATION_CPP__