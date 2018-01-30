#ifndef _MODULEIMGUI_
#define _MODULEIMGUI_

#include "Module.h"
#include "Globals.h"
#include "imgui-1.53\imgui.h"


class ModuleImGui :
	public Module
{

public:
	ModuleImGui();
	~ModuleImGui();

	bool Init();

	update_status PreUpdate(float dt);
	update_status Update(float dt);

	bool CleanUp();

public:

	float posx, posy, posz, posw;
	float frontx, fronty, frontz, frontw;
	float upx, upy, upz, upw;
	int format_, width_, heigth_, mag_, min_, wraps_, wrapt_ = 0;
	

private:

	bool show_demo_window = true;
	bool show_about_window = true;
	const char* license_;
};



#endif // !_MODULEIMGUI_

