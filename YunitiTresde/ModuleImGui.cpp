#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <shellapi.h>
#include <string>
#include <fstream>
#include <iostream>


#include "imgui-1.53\imgui.h"
#include "imgui-1.53\imgui_impl_sdl_gl3.h"

#include <fstream>

#include "Application.h"
#include "ModuleImGui.h"
#include "ModuleWindow.h"
#include "ModuleRenderer.h"
#include "ModuleScene.h"
#include "ModuleShader.h"
#include "Brofiler/include/Brofiler.h"
#pragma comment( lib, "Brofiler/libx86/ProfilerCore32.lib")
using namespace std;
ModuleImGui::ModuleImGui()
{
	//TODO string liscense
	license_ = "   GNU GENERAL PUBLIC LICENSE\n Version 3, 29 June 2007\n"
		"Copyright(C) 2007 Free Software Foundation, Inc. <http://fsf.org/>\n"
		"Everyone is permitted to copy and distribute verbatim copies\n"
		"of this license document, but changing it is not allowed.";

	//ImGui Window Flags by default:
	imgui_window_flags_ |= ImGuiWindowFlags_NoMove;
	imgui_window_flags_ |= ImGuiWindowFlags_NoCollapse;
	imgui_window_flags_ |= ImGuiWindowFlags_NoResize;



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
update_status ModuleImGui::PreUpdate(float dt)
{
	ImGui_ImplSdlGL3_NewFrame(App->window->GetWindow());
	return UPDATE_CONTINUE;
}
		
update_status ModuleImGui::Update(float dt)
	{
	AboutImgui();
		return UPDATE_CONTINUE;
	}
void ModuleImGui::RenderImGui()
{
	ImGui::Render();

}
void ModuleImGui::AboutImgui()
{
	//Rendering before than that of Module Render, shall we changed?
	if (show_demo_window)
	{
		ImGui::ShowDemoWindow(&show_demo_window);
	}
	if (show_about_window)
	{
		ImGui::SetNextWindowPos(ImVec2(App->window->GetWidth()-300, App->window->GetHeight()-300));
		ImGui::SetNextWindowSize(ImVec2(300, 300));
		ImGui::Begin("Configuration", &show_about_window);
		if (ImGui::CollapsingHeader("View Matrix")) {
			ImGui::Text("POSITION:  [%f][%f][%f]\n", posx, posy, posz);
			ImGui::Text("FRONT:        [%f][%f][%f]\n", frontx, fronty, frontz);
			ImGui::Text("HEIGHT:    [%f][%f][%f]\n", upx, upy, upz);
		}
		//ImGui::Begin("Select Texture: ", &show_about_window);
		static const char* selected_item_ = NULL;
		ImGui::LabelText("", "Select Texture: ");

		{
			const char* textures_[] = { IMAGE1, IMAGE2, IMAGE3, IMAGE4 };

			if (ImGui::BeginCombo("", selected_item_))
			{
				for (int n = 0; n < IM_ARRAYSIZE(textures_); n++)
				{
					bool is_selected = (selected_item_ == textures_[n]);
					if (ImGui::Selectable(textures_[n], is_selected)) {
						selected_item_ = textures_[n];
						ImGui::SetItemDefaultFocus();
						App->renderer->SetIdImage(n);
					}
				}
				ImGui::EndCombo();
			}
		}



		if (ImGui::CollapsingHeader("Texture")) {
			ImGui::Text("WIDTH: %d", width_);
			ImGui::Text("HEIGTH: %d", heigth_);
			ImGui::Text("File: %s", selected_item_);
			ImGui::Text("FORMAT: %d", format_);
		}
		BROFILER_FRAME("ThreadImguiStatus");
		BROFILER_CATEGORY("CHECK STATUS", Profiler::Color::GreenYellow);
		ImGui::Text("CPUs: %i (Cache: %iKB)", SDL_GetCPUCount(), SDL_GetCPUCacheLineSize());
		ImGui::Text("System RAM: %iGB", SDL_GetSystemRAM() / 1000);
		//ImGui::Text("CollissionwithQuadTree: %d", App->scene->imguiCollisionTestQuadtree++);
		//ImGui::Text("CollissionwithoutQuadTree: %d", App->scene->imguiCollisionTest++);


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
}

uint ModuleImGui::GetImGuiWindowFlags()
{
	return imgui_window_flags_;
}

void ModuleImGui::ShowIDEWindow(bool* pOpen)
{
	static char text[1024 * 16] = "";
	static char text2[1024 * 16] = "";
	static char fileName[256] = "Vertex Shadder";
	static std::string lastLog = "";
	static bool showExtendedSaveMenu = false;
	static bool showExtendedLoadMenu = false;
	static const char* selected_item_ = NULL;

	ImGui::SetNextWindowPos(ImVec2(0, ImGui::GetWindowHeight()));
	ImGui::SetNextWindowSize(ImVec2(450, 570));
	ImGui::Begin("YunitiTresDe IDE - 2018 - vr0.2", pOpen, ImGuiWindowFlags_NoCollapse);
	std::string line;
	std::string line2;
	const char* File[] = { VERTEXSHFILE, FRAGMENTSHFILE, LUAFILE };//Comented for next update with uberfiles, UBERSHFILE };
	//	selected_item_ = VERTEXSHFILE;
	bool is_selected = false;
	ImGui::LabelText("", "Select Texture: ");
	{

		if (ImGui::BeginCombo("", selected_item_))
		{
			for (int n = 0; n < IM_ARRAYSIZE(File); n++)
			{
				is_selected = (selected_item_ == File[n]);
				if (ImGui::Selectable(File[n], is_selected)) {
					selected_item_ = File[n];
					ImGui::SetItemDefaultFocus();
					App->renderer->SetIdImage(n);
				}
			}
			ImGui::EndCombo();
		}
	}
	if (selected_item_ != NULL) {
		ifstream myfile(selected_item_);
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				line2 = line2 + line + "\n";
			}
			strcpy_s(text, line2.c_str());
			myfile.close();
		}
		ImGui::InputTextMultiline("", text, IM_ARRAYSIZE(text), ImVec2(430.f, ImGui::GetTextLineHeight() * 32), ImGuiInputTextFlags_AllowTabInput);
	}
	//ImGui::InputText("File Name", fileName, IM_ARRAYSIZE(fileName));
	if (ImGui::Button("Compile", ImVec2(125.0f, 25.0f)))
	{
		showExtendedSaveMenu = true;
		showExtendedLoadMenu = false;
		App->shader->CompileVertexShader();
	}

	ImGui::SameLine(0.0f, 42.0f);

	if (ImGui::Button("Load", ImVec2(125.0f, 25.0f)))
	{
		showExtendedLoadMenu = true;
		showExtendedSaveMenu = false;
	}

	if (showExtendedSaveMenu)
	{
		ImGui::Text("Are you sure you want to save?");
		if (ImGui::Button("Save & Compile", ImVec2(125.0f, 25.0f)))
		{
			showExtendedSaveMenu = false;
			if (SaveScript(fileName, text))
				lastLog = "File Compiled.";
			else
				lastLog = "File could NOT be saved.";
		}

		ImGui::SameLine(0.0f, 42.0f);

		if (ImGui::Button("Cancel Save & Compile", ImVec2(125.0f, 25.0f)))
			showExtendedSaveMenu = false;
	}

	if (showExtendedLoadMenu)
	{
		ImGui::Text("Are you sure you want to load?");
		if (ImGui::Button("Confirm Load", ImVec2(125.0f, 25.0f)))
		{
			showExtendedLoadMenu = false;
			std::string fileContent;
			if (LoadScript(fileName, fileContent))
			{
				lastLog = "File loaded.";
				strcpy_s(text, 1024 * 16, fileContent.c_str());
			}
			else
				lastLog = "File could NOT be loaded.";
		}

		ImGui::SameLine(0.0f, 42.0f);

		if (ImGui::Button("Cancel Load", ImVec2(125.0f, 25.0f)))
			showExtendedLoadMenu = false;
	}
	ImGui::SameLine();


	ImGui::End();
}

bool ModuleImGui::SaveScript(const std::string& path, const std::string& content)
{
	std::ofstream outFile(path);
	if (outFile.good())
	{
		outFile << content;
		return true;
	}
	return false;
}

bool ModuleImGui::LoadScript(const std::string& path, std::string& outputString)
{
	outputString = "";
	std::string line;
	std::ifstream inFile(path);
	if (inFile.good())
	{
		while (getline(inFile, line))
		{
			outputString += line + '\n';
		}
		inFile.close();
		return true;
	}

	return false;
}
