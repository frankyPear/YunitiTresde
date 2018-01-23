#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <shellapi.h>

#include "imgui-1.53\imgui.h"
#include "imgui-1.53\imgui_impl_sdl_gl3.h"
#include "Application.h"
#include "ModuleImGui.h"
#include "ModuleWindow.h"


ModuleImGui::ModuleImGui()
{
	//TODO sting liscense
}

ModuleImGui::~ModuleImGui()
{

}

bool ModuleImGui::Init()
{
	bool ret = true;

	ImGui_ImplSdlGL3_Init(App->window->GetWindow());
	ImGui::StyleColorsDark();
	
	

	return ret;
}

bool ModuleImGui::CleanUp()
{
	bool ret = true;			
	ImGui_ImplSdlGL3_Shutdown();

	return ret;
}
update_status ModuleImGui::PreUpdate()
{
	ImGui_ImplSdlGL3_NewFrame(App->window->GetWindow());
	return UPDATE_CONTINUE;
}
update_status ModuleImGui::Update()
{
	//Rendering before than that of Module Render, shall we changed?
	ImGui::ShowDemoWindow(&show_demo_window);
	ImGui::Render();

	return UPDATE_CONTINUE;
}