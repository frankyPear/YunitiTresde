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
	void RenderImGui();
	uint GetImGuiWindowFlags();
	void ShowIDEWindow(bool * pOpen);
	bool SaveScript(const std::string & path, const std::string & content);
	bool LoadScript(const std::string & path, std::string & outputString);
	void AboutImgui();

public:

	float posx, posy, posz, posw;
	float frontx, fronty, frontz, frontw;
	float upx, upy, upz, upw;
	int format_, width_, heigth_, mag_, min_, wraps_, wrapt_ = 0;
	
	

private:
	
	bool show_demo_window = true;
	bool show_about_window = true;
	const char* license_;
	uint imgui_window_flags_ = 0;
};



#endif // !_MODULEIMGUI_

