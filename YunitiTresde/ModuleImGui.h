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

	update_status PreUpdate();
	update_status Update();

	bool CleanUp();

public:

	

private:

	bool show_demo_window = true;
	
};



#endif // !_MODULEIMGUI_

