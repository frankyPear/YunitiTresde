#ifndef __ModuleScene_H__
#define __ModuleScene_H__

#include "Module.h"
#include "ComponentCamera.h"
#include "CustomQuadTree.h"
#include <vector>

#define BOX_SIZE 20.0f

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

	//Imgui
	void ShowImguiStatus();
	void ImGuiMainMenu();

	GameObject* GetRoot();
	void Hierarchy();

	
	
public:
	bool recreateQuadTree = false;
	ComponentCamera *actualCamera = nullptr;

private:
	GameObject* root;
	GameObject* selected = nullptr;
	CustomQuadTree* quadtree = nullptr;
	AABB limits;

	bool wantToSave = false;
	bool wantToLoad = false;
	std::string loadPath;

	Timer saveLoadTimer;
	std::vector<GameObject*> sceneObjects_;
	std::vector<GameObject*> objectToDraw_;

};

#endif
