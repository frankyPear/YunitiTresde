#ifndef _MODULEIMGUI_
#define _MODULEIMGUI_

#include "Module.h"
#include "Globals.h"
#include "imgui-1.53\imgui.h"
#include "Math.h"


class ModuleImGui :
	public Module
{

public:
	ModuleImGui();
	~ModuleImGui();

	bool Init();

	update_status PreUpdate();
	update_status Update();

	bool CleanUp();

	//Matrix
	//float4x4 
	float posx, posy, posz, posw;
	float frontx, fronty, frontz, frontw;
	float upx, upy, upz, upw;
	int format, width, heigth, mag, min =0;

private:

	bool show_demo_window = true;
	bool show_about_window = true;
	const char* license_;
};



#endif // !_MODULEIMGUI_

