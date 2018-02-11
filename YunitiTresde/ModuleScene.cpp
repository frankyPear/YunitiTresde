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

using namespace std;

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
	object1->AddComponent(cm1);
	object1->AddComponent(ct1);

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
	limits = AABB();
	limits.maxPoint = float3(BOX_SIZE, BOX_SIZE, BOX_SIZE);
	limits.minPoint = float3(-BOX_SIZE, -BOX_SIZE, -BOX_SIZE);
	quadtree = new CustomQuadTree();
	quadtree->Create(limits);
	for (int i = 0; i < sceneObjects_.size(); ++i) quadtree->Insert(sceneObjects_[i]);
	quadtree->Intersect(objectToDraw_, *(actualCamera->GetFrustum()));

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
	if (accelerateFrustumCulling) {
		if (recreateQuadTree) {
			quadtree->Clear();
			limits.maxPoint = float3(BOX_SIZE, BOX_SIZE, BOX_SIZE);
			limits.minPoint = float3(-BOX_SIZE, -BOX_SIZE, -BOX_SIZE);
			quadtree->Create(limits);
			for (int i = 0; i < sceneObjects_.size(); ++i) quadtree->Insert(sceneObjects_[i]);
		}
		quadtree->Intersect(objectToDraw_, *(actualCamera->GetFrustum()));
		for (int i = 0; i < objectToDraw_.size(); i++)
		{
			objectToDraw_[i]->DrawObjectAndChilds();
		}
		objectToDraw_.clear();
	}
	else {
		for (int i = 0; i < sceneObjects_.size(); i++)
		{
			ComponentMesh* cm = (ComponentMesh*)sceneObjects_[i]->GetComponent(MESH);
			ComponentTransform* ct = (ComponentTransform*)sceneObjects_[i]->GetComponent(TRANSFORMATION);
			if (cm != nullptr && ct != nullptr) {
				AABB newBox = *(cm->GetBoundingBox());
				newBox.TransformAsAABB(ct->GetGlobalTransform());
				if (actualCamera->GetFrustum()->Intersects(newBox)) sceneObjects_[i]->DrawObjectAndChilds();
			}
		}
	}
	return UPDATE_CONTINUE;
}

update_status ModuleScene::PostUpdate(float dt)
{

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
	bool text = false;
	ImGui::BeginMainMenuBar();
	if (ImGui::MenuItem("New"))
	{
		ImGui::Text("Game Object");

	}
	ImGui::EndMainMenuBar();
}

void ModuleScene::ToggleFrustumAcceleration()
{
	accelerateFrustumCulling != accelerateFrustumCulling;
}
