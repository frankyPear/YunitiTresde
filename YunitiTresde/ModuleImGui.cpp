#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include <Windows.h>
#include "ModuleImGui.h"
#include "imgui-1.53\imgui_impl_sdl_gl3.h"


ModuleImGui::ModuleImGui()
{
}

ModuleImGui::~ModuleImGui()
{
}

bool ModuleImGui::Init()
{
	bool ret = true;

	//ImGui_ImplSdlGL3_Init(App->window->GetWindow());

	return ret;
}

update_status ModuleImGui::Update()
{
	return UPDATE_CONTINUE;
}