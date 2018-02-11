#include "Application.h"
#include "ModuleScene.h"
#include "ModuleWindow.h"
#include "ModuleRenderer.h"

#include "imgui-1.53\imgui.h"
#include "imgui-1.53\imgui_impl_sdl_gl3.h"
#include "ModuleImGui.h"
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

	root = new GameObject();
	GameObject *object1 = new GameObject();
	ComponentMesh *cm1 = new ComponentMesh(SPHERE);
	ComponentTransform *ct1 = new ComponentTransform(float3(0.0f,0.0f,0.0f), float3(1.0f,1.0f,1.0f), Quat::identity);

	ComponentCamera *camera = new ComponentCamera();
	object1->AddComponent(cm1);
	object1->AddComponent(ct1);
	object1->AddComponent(camera);

	GameObject *object2 = new GameObject();
	ComponentMesh *cm2 = new ComponentMesh(CUBE);
	ComponentTransform *ct2 = new ComponentTransform(float3(10.0f, 0.0f, 10.0f), float3(1.0f, 1.0f, 1.0f), Quat::identity);
	object2->AddComponent(cm2);
	object2->AddComponent(ct2);

	GameObject *object3 = new GameObject();
	ComponentMesh *cm3 = new ComponentMesh(CUBE);
	ComponentTransform *ct3 = new ComponentTransform(float3(-10.0f, 0.0f, 10.0f), float3(1.0f, 1.0f, 1.0f), Quat::identity);
	object3->AddComponent(cm3);
	object3->AddComponent(ct3);
	
	GameObject *object4 = new GameObject();
	ComponentMesh *cm4 = new ComponentMesh(CUBE);
	ComponentTransform *ct4 = new ComponentTransform(float3(10.0f, 0.0f, -10.0f), float3(1.0f, 1.0f, 1.0f), Quat::identity);
	object4->AddComponent(cm4);
	object4->AddComponent(ct4); 

	GameObject *object5 = new GameObject();
	ComponentMesh *cm5 = new ComponentMesh(CUBE);
	ComponentTransform *ct5 = new ComponentTransform(float3(-10.0f, 0.0f, -10.0f), float3(1.0f, 1.0f, 1.0f), Quat::identity);
	object5->AddComponent(cm5);
	object5->AddComponent(ct5);


	root->AddChild(object1);
	root->AddChild(object2);
	root->AddChild(object3);
	root->AddChild(object4);
	root->AddChild(object5);

	sceneObjects_.push_back(object1);
	sceneObjects_.push_back(object2);
	sceneObjects_.push_back(object3);
	sceneObjects_.push_back(object4);
	sceneObjects_.push_back(object5);


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

update_status ModuleScene::PreUpdate(float dt)
{
	ShowImguiStatus();
	ImGuiMainMenu();
	return UPDATE_CONTINUE;
}

update_status ModuleScene::Update(float dt)
{
	ComponentCamera *thecamera = (ComponentCamera*)sceneObjects_[0]->GetComponent(CAMERA);
	if (thecamera != nullptr) thecamera->Update();
	ComponentMesh * cmorig = (ComponentMesh*)sceneObjects_[0]->GetComponent(MESH);
	for (int i = 0; i < sceneObjects_.size(); i++)
	{
		ComponentMesh * cm = (ComponentMesh*)sceneObjects_[i]->GetComponent(MESH);

		if (cmorig == cm) {
			sceneObjects_[i]->DrawObjectAndChilds();
		}

		else {
			AABB box = *cm->GetBoundingBox();
			ComponentTransform *ct = (ComponentTransform*) cm->LinkedTo()->GetComponent(TRANSFORMATION);
			box.Translate(ct->GetPosition());
			bool inter = thecamera->GetFrustum()->Intersects(box);
			if (inter) 	sceneObjects_[i]->DrawObjectAndChilds();			
		}
	}	

	//IMGUI
Hierarchy();
	

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

void ModuleScene::Hierarchy()
{
	ImGui::SetNextWindowPos(ImVec2(0, 20));
	ImGui::SetNextWindowSize(ImVec2(300, 680));
	ImGui::Begin("Hierarchy", 0, App->imgui->GetImGuiWindowFlags());
	static bool selected = false;
	for (int i = 0; i < sceneObjects_.size(); i++)
	{
	//	std::vector<static bool> selected;
		std::string  c = "Game Object " + std::to_string(i + 1);
		
		if (ImGui::Selectable((c.c_str()), &selected))
		{
			for (int j = 0; j < sceneObjects_.size(); j++)
			{
				sceneObjects_[j]->isSelected = false;
			}
			sceneObjects_[i]->isSelected = true;
		}
		//temporal, NEED FIXING		
		selected = false;
	}

	ImGui::End();
}

void ModuleScene::ShowImguiStatus() {
	ImGui::SetNextWindowPos(ImVec2(App->window->GetWidth()-300, 20));
	ImGui::SetNextWindowSize(ImVec2(300, 500));
	ImGui::Begin("Scene Manager");
	if (ImGui::CollapsingHeader("GameObjects"))
	{
		for (int i = 0; i < sceneObjects_.size(); i++)
		{
			if (sceneObjects_[i]->isSelected)
			{
				ComponentTransform *ct = (ComponentTransform*)sceneObjects_[i]->GetComponent(TRANSFORMATION);
				if (ct != nullptr)
				{
					ct->OnEditor();
					ct->Update();

				}
				ComponentMesh *cm = (ComponentMesh*)sceneObjects_[i]->GetComponent(MESH);
				if (cm != nullptr)
				{
					cm->OnEditor();
				}
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
				
					GameObject *object = new GameObject();
					static bool cm;
					static bool cam;
					float pos[3] = {0,0,0};
					ImGui::Text("Hey there, you are creating an object");
					ImGui::Separator();
					ImGui::Text("What components do you want to add to your game object?");
					if (ImGui::Checkbox("Component mesh", &cm));
					if (ImGui::Checkbox("Component camera", &cam));
					if (ImGui::InputFloat3("Position (Comming soon...)", (float*)pos, 2));
					if (ImGui::Button("Create", ImVec2(120, 0)))
					{ 
						ImGui::CloseCurrentPopup();
						CreateGameObject(object, cm, cam);
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
		if (ImGui::MenuItem("Options"))
		{

		}
		ImGui::EndMainMenuBar();
	}
}

void ModuleScene::CreateGameObject(GameObject* obj, bool boolcm, bool boolcam)
{
	if (boolcm)
	{
		ComponentMesh* CM = new ComponentMesh(CUBE);
		obj->AddComponent(CM);
	}
	if (boolcam)
	{
		ComponentCamera* CAM = new ComponentCamera();
		obj->AddComponent(CAM);
	}
	
	ComponentTransform *ct = new ComponentTransform(float3(0.0f, 0.0f, 0.0f), float3(1.0f, 1.0f, 1.0f), Quat::identity);
	obj->AddComponent(ct);
	
	sceneObjects_.push_back(obj);
}

/*	if (ImGui::TreeNode((void*)(intptr_t)i, "Game Object %d", i + 1))
{
for (int i = 0; i < sceneObjects_[i]->GetChilds().size(); i++)
{
if (ImGui::TreeNode((void*)(intptr_t)i, "Child %d", i + 1));
}
ImGui::TreePop();
}*/