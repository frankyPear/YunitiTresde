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
	bool Start();

	update_status Update();

	bool CleanUp();


private:

};



#endif // !_MODULEIMGUI_

