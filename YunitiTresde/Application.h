#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include<list>
#include "Module.h"



class ModuleRenderer;
class ModuleWindow;
class ModuleInput;

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

	bool switchmap = false;
private:

	std::list<Module*> modules;

};

extern Application* App;

#endif // __APPLICATION_CPP__