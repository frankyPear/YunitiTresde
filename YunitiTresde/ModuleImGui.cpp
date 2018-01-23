#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "SDL\include\SDL.h"

#include "ModuleImGui.h"
#include "OpenGL.h"

#include "imgui-1.53\imgui.h"
#include "imgui-1.53\imgui_impl_sdl_gl3.h"
#include "imgui-1.53\glfw\include\GLFW\glfw3.h"


#pragma comment (lib, "imgui-1.53/glfw/lib-vc2010-32/glfw3.lib")
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