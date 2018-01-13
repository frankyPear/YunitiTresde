#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include<list>

//#include "Module.h"
//
//class ModuleRender;
//class ModuleWindow;
//class ModuleInput;
//class ModuleFonts;
//class ModuleTimer;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	//TODO GLOBALS update_status Update();
	bool CleanUp();

	//void RerunTimer();

public:
	//ModuleRender* renderer;
	//ModuleWindow* window;
	//ModuleTextures* textures;
	//ModuleInput* input;
	//ModuleAudio* audio;
	//ModuleFonts* fonts;
	//ModuleFadeToBlack* fade;
	//ModulePlayer* player;
	//ModuleSceneSega* scene_sega;
	//ModuleSceneStage* scene_stage;
	//ModuleSceneMusic* scene_music;
	//ModuleCollision* colliders;
	//ModuleTimer* Rtimer;
	bool switchmap = false;
private:

	//TODO MODULE.Hstd::list<Module*> modules;

};

extern Application* App;

#endif // __APPLICATION_CPP__