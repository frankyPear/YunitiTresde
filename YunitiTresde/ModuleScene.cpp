#include "Application.h"
#include "ModuleScene.h"
#include "ModuleWindow.h"
#include "ModuleRenderer.h"

#include "imgui-1.53\imgui.h"
#include "imgui-1.53\imgui_impl_sdl_gl3.h"

#include "Mathgeolib\include\MathGeoLib.h"


#include "GameObject.h"
#include "ComponentMesh.h"
#include "ComponentTransform.h"
#include "ComponentMaterial.h"
#include "ComponentCamera.h"
#include "ModuleCamera.h"

ModuleScene::ModuleScene()
{
}

ModuleScene::~ModuleScene()
{

}

bool ModuleScene::Init()
{
	
	/*ComponentMesh *cm = new ComponentMesh(SPHERE);
	ComponentTransform *ct = new ComponentTransform(float3(0.0f,0.0f,0.0f), float3(1.0f,1.0f,1.0f), Quat::identity);
	ComponentCamera *camera = new ComponentCamera();
	object1->AddComponent(cm);
	object1->AddComponent(ct);
	object1->AddComponent(camera);

	sceneObjects_.push_back(object1);

	GameObject *object2 = new GameObject();
	ComponentMesh *cm2 = new ComponentMesh(CUBE);
	ComponentTransform *ct2 = new ComponentTransform(float3(3.0f, 3.0f, 0.0f), float3(1.0f, 1.0f, 1.0f), Quat::identity);
	object2->AddComponent(cm2);
	object2->AddComponent(ct2);
	root->AddChild(object1);
	object1->AddChild(object2);

	
	sceneObjects_.push_back(object2);*/

    
	actualCamera = App->cam->dummyCamera;

	return true;
}

bool ModuleScene::Start()
{
	return true;
}

bool ModuleScene::CleanUp()
{
	return true;
}
void ModuleScene::Hierarchy()
{
	
}

update_status ModuleScene::PreUpdate(float dt)
{
	ShowImguiStatus();
	ImGuiMainMenu();
	return UPDATE_CONTINUE;
}

update_status ModuleScene::Update(float dt)
{
	for (int i = 0; i < sceneObjects_.size(); i++)
	{
		sceneObjects_[i]->DrawObjectAndChilds();
		ComponentCamera *camera = (ComponentCamera*)sceneObjects_[i]->GetComponent(CAMERA);
		if (camera != nullptr)
		{
			camera->Update();
		}
	}
	
	return UPDATE_CONTINUE;
}

update_status ModuleScene::PostUpdate(float dt)
{
	if (imguiFlag == SDL_SCANCODE_ESCAPE)
	{
		return UPDATE_STOP;
	}
	return UPDATE_CONTINUE;
}

void ModuleScene::ShowImguiStatus() {

	ImGui::Begin("Scene Manager");
	if (ImGui::CollapsingHeader("GameObjects"))
	{
		for (int i = 0; i < sceneObjects_.size(); i++)
		{
			ComponentTransform *ct = (ComponentTransform*)sceneObjects_[i]->GetComponent(TRANSFORMATION);
			if (ct != nullptr)
			{
				ct->OnEditor();
				ct->Update();

			}
		}
		for (int i = 0; i < sceneObjects_.size(); i++)
		{
			ComponentMesh *cm = (ComponentMesh*)sceneObjects_[i]->GetComponent(MESH);
			if (cm != nullptr)
			{
				cm->OnEditor();
			}
		}
	}
	if (ImGui::CollapsingHeader("Settings"))
	{
		App->window->WindowImGui();
		App->renderer->ConfigurationManager();
	}
	//TODO: COLOR PICKER FOR AMBIENT LIGHT
	ImGui::End();

}

void ModuleScene::ImGuiMainMenu()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::BeginMenu("New"))
			{
				if (ImGui::Button("Game Object"))
					ImGui::OpenPopup("New Game Object");
				if (ImGui::BeginPopupModal("New Game Object", NULL, ImGuiWindowFlags_AlwaysAutoResize))
				{
				

					ImGui::Text("Hey you are creating an object");
					ImGui::Separator();

					if (ImGui::Button("OK", ImVec2(120, 0)))
					{ 
						ImGui::CloseCurrentPopup();
						CreateGameObject();
					}
					ImGui::SameLine();
					if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
					ImGui::EndPopup();
				}

				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Open"))
			{
				ImGui::MenuItem("Empty");

				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Save"))
			{
				ImGui::MenuItem("Empty");

				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Load"))
			{
				ImGui::MenuItem("Empty");

				ImGui::EndMenu();
			}
			if (ImGui::MenuItem("Exit"))
			{
				imguiFlag = SDL_SCANCODE_ESCAPE;
			}

			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void ModuleScene::CreateGameObject()
{
	root = new GameObject();
	GameObject *object = new GameObject();
	ComponentMesh *cm = new ComponentMesh(SPHERE);
	ComponentTransform *ct = new ComponentTransform(float3(0.0f,0.0f,0.0f), float3(1.0f,1.0f,1.0f), Quat::identity);
	ComponentCamera *camera = new ComponentCamera();
	object->AddComponent(cm);
	object->AddComponent(ct);
	object->AddComponent(camera);
	sceneObjects_.push_back(object);
}