#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <shellapi.h>

#include "imgui-1.53\imgui.h"
#include "imgui-1.53\imgui_impl_sdl_gl3.h"
#include "Application.h"
#include "ModuleImGui.h"
#include "ModuleWindow.h"
#include <string>


ModuleImGui::ModuleImGui()
{
	//TODO string liscense
	license_ = "   GNU GENERAL PUBLIC LICENSE\n Version 3, 29 June 2007\n"
		"Copyright(C) 2007 Free Software Foundation, Inc. <http://fsf.org/>\n"
		"Everyone is permitted to copy and distribute verbatim copies\n"
		"of this license document, but changing it is not allowed.";

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

	if (show_about_window)
	{
	
		ImGui::Begin("Configuration", &show_about_window);
		if (ImGui::CollapsingHeader("View Matrix")) {
			ImGui::Text("[%f][%f][%f]\n",posx,posy,posz);
			ImGui::Text("[%f][%f][%f]\n",frontx,fronty,frontz);
			ImGui::Text("[%f][%f][%f]\n",upx,upy,upz);
		}
		if (ImGui::CollapsingHeader("Texture")) {
			ImGui::Text("WIDTH: %d",width);
			ImGui::Text("HEIGTH: %d", heigth);
			ImGui::Text("MAG: %d", mag);
			ImGui::Text("MIN: %d", min);
			if (format== FORMATPNG)ImGui::Text("FORMAT: PNG");
		}
		if (ImGui::CollapsingHeader("Camera"))
		{
			ImGui::Text("Active\n");
			ImGui::Text("Front\n");
			ImGui::Text("Position\n");
			ImGui::Text("Mov Speed\n");
			ImGui::Text("Rot Speed\n");
			ImGui::Text("Zoom Speed\n");
			ImGui::Text("Frustum Culling\n");
			ImGui::Text("Near Plane\n");
			ImGui::Text("Far Plane\n");
			ImGui::Text("Field of View\n");
			ImGui::Text("Aspect Ratio\n");
			ImGui::Text("Background\n");
			ImGui::Text("Current\n");
			ImGui::Text("Pick Another\n");
			//ImGui::CheckboxFlags("Is Active camera\n",1,1);
			//ImGui::ShowDemoWindow(&show_about_window);
		}
		ImGui::CollapsingHeader("About", &show_about_window);
		ImGui::Text("3D Engine made with C++ and OpenGL");
		if (ImGui::CollapsingHeader("Authors"))
		{
			if (ImGui::MenuItem("Oscar Lopez"))
			{
				ShellExecuteA(NULL, "open", "https://www.github.com/OscarLopezFabregas", NULL, NULL, SW_SHOWNORMAL);
			}
			if (ImGui::MenuItem("Francesc Perez"))
			{
				ShellExecuteA(NULL, "open", "https://www.github.com/frankyPear", NULL, NULL, SW_SHOWNORMAL);
			}
			if (ImGui::MenuItem("Max Puncernau"))
			{
				ShellExecuteA(NULL, "open", "https://www.github.com/OscarLopezFabregas", NULL, NULL, SW_SHOWNORMAL);
			}
			if (ImGui::MenuItem("Alex Espinet"))
			{
				ShellExecuteA(NULL, "open", "https://www.github.com/OscarLopezFabregas", NULL, NULL, SW_SHOWNORMAL);
			}
		}
		if (ImGui::CollapsingHeader("Libraries used"))
		{
			if (ImGui::MenuItem("SDL 2.0.4"))
			{
				ShellExecuteA(NULL, "open", "https://www.libsdl.org/index.php", NULL, NULL, SW_SHOWNORMAL);
			}
			if (ImGui::MenuItem("MathGeoLib 1.3"))
			{
				ShellExecuteA(NULL, "open", "http://clb.demon.fi/MathGeoLib/nightly/", NULL, NULL, SW_SHOWNORMAL);
			}
			if (ImGui::MenuItem("ImGui 1.52 WIP"))
			{
				ShellExecuteA(NULL, "open", "https://github.com/ocornut/imgui", NULL, NULL, SW_SHOWNORMAL);
			}
			if (ImGui::MenuItem("Bullet 2.84"))
			{
				ShellExecuteA(NULL, "open", "http://bulletphysics.org/wordpress/", NULL, NULL, SW_SHOWNORMAL);
			}
			if (ImGui::MenuItem("Brofiler 1.1.2"))
			{
				ShellExecuteA(NULL, "open", "http://brofiler.com/", NULL, NULL, SW_SHOWNORMAL);
			}
			if (ImGui::MenuItem("Glew 2.0.0"))
			{
				ShellExecuteA(NULL, "open", "http://glew.sourceforge.net/", NULL, NULL, SW_SHOWNORMAL);
			}
			if (ImGui::MenuItem("OpenGl 3.3"))
			{
				ShellExecuteA(NULL, "open", "https://www.opengl.org/", NULL, NULL, SW_SHOWNORMAL);
			}
			if (ImGui::MenuItem("DevIL 1.8.0"))
			{
				ShellExecuteA(NULL, "open", "http://openil.sourceforge.net/", NULL, NULL, SW_SHOWNORMAL);
			}
			if (ImGui::MenuItem("Assimp 3.0"))
			{
				ShellExecuteA(NULL, "open", "http://assimp.sourceforge.net/lib_html/", NULL, NULL, SW_SHOWNORMAL);
			}
		}
		if (ImGui::CollapsingHeader("License"))
		{
			ImGui::Text(license_);
		}
		ImGui::End();
	}
	ImGui::Render();
	return UPDATE_CONTINUE;
}