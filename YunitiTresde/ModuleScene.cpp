#include "Application.h"
#include "ModuleScene.h"

#include "imgui-1.53\imgui.h"
#include "imgui-1.53\imgui_impl_sdl_gl3.h"

//include "GameObject.h"
//#include "MeshComponent.h"
//#include "TransformComponent.h"
//#include "CameraComponent.h"


ModuleScene::ModuleScene()
{
}

ModuleScene::~ModuleScene()
{

}

bool ModuleScene::Init()
{
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
	return UPDATE_CONTINUE;
}

update_status ModuleScene::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

void ModuleScene::ShowImguiStatus() {
	ImGui::Begin("Render Manager");

	if (ImGui::CollapsingHeader("GameObjects"))
	{

	}

	//TODO: COLOR PICKER FOR AMBIENT LIGHT
	ImGui::End();
}