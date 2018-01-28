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

	

private:

	bool show_demo_window = true;
	bool show_about_window = true;
	const char* license_;
};



#endif // !_MODULEIMGUI_

