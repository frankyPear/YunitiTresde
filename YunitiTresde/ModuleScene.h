#ifndef __ModuleScene_H__
#define __ModuleScene_H__

#include "Module.h"
#include "ComponentCamera.h"
#include <vector>

class GameObject;
class Mesh;
class Quadtree;

class ModuleScene : public Module
{
public:
	ModuleScene();
	~ModuleScene();



	bool Init();
	bool Start();
	bool CleanUp();

	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	//Create
	void CreateGameObject(GameObject* obj, bool boolcm = false, bool boolcam=false);

	//Imgui
	void ShowImguiStatus();
	void ImGuiMainMenu();
	void Hierarchy();
	GameObject* GetRoot();
	

	
	
public:
	bool recalcTree = false;
	ComponentCamera *actualCamera = nullptr;
	uint imguiFlag = 0;
	uint imguiCollisionTest = 0;
	uint imguiCollisionTestQuadtree = 0;
private:
	GameObject* root;
	GameObject* selected = nullptr;
	Quadtree* tree = nullptr;

	bool wantToSave = false;
	bool wantToLoad = false;
	std::string loadPath;

	Timer saveLoadTimer;
	std::vector<GameObject*> sceneObjects_;
	
};

#endif
