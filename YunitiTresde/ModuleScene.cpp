#include "Application.h"
#include "ModuleScene.h"
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
	return false;
}

bool ModuleScene::Start()
{
	return false;
}

bool ModuleScene::CleanUp()
{
	return false;
}


update_status ModuleScene::PreUpdate(float dt)
{
	return update_status();
}

update_status ModuleScene::Update(float dt)
{
	return update_status();
}

update_status ModuleScene::PostUpdate(float dt)
{
	return update_status();
}
