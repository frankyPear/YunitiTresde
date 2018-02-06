#include "Application.h"
#include "ModuleScene.h"
#include "ModuleRenderer.h"

#include "imgui-1.53\imgui.h"
#include "imgui-1.53\imgui_impl_sdl_gl3.h"

#include "GameObject.h"
#include "ComponentMesh.h"
#include "ComponentTransform.h"
#include "ComponentMaterial.h"

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
	ComponentMesh *cm = new ComponentMesh(CUBE);
	ComponentTransform *ct = new ComponentTransform(float3(0.0f,0.0f,0.0f), float3(1.0f,1.0f,1.0f), Quat::identity);
	object1->AddComponent(cm);
	object1->AddComponent(ct);
	root->AddChild(object1);
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
	return UPDATE_CONTINUE;
}

update_status ModuleScene::Update(float dt)
{
	ShowImguiStatus();
	std::vector<GameObject*> rootchilds = root->GetChilds();
	for (int i = 0; i < rootchilds.size(); ++i) {
		App->renderer->Draw( rootchilds[i]);
	}
	return UPDATE_CONTINUE;
}

update_status ModuleScene::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

void ModuleScene::ShowImguiStatus() {
	/*ImGui::Begin("Scene Manager");

	if (ImGui::CollapsingHeader("GameObjects"))
	{

	}

	//TODO: COLOR PICKER FOR AMBIENT LIGHT
	ImGui::End();*/
}