#ifndef __ModuleScene_H__
#define __ModuleScene_H__

#include "Module.h"
#include "ComponentCamera.h"
#include "Model.h"
#include "CustomQuadTree.h"
#include <vector>

class GameObject;
class Mesh;
class Quadtree;
class MeshImporter;

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
	
	void ToggleFrustumAcceleration();
	void CreateRay(float2 screenPoint);
	
	void OnSceneObjectIsDestroyed(GameObject *t);

public:
	ComponentCamera *actualCamera = nullptr;
	uint imguiFlag = 0;
	bool recreateQuadTree = false;
	bool drawQuadTree = false;
	uint imguiCollisionTest = 0;
	uint imguiCollisionTestQuadtree = 0;
	bool wantToDelete = false;
private:
	GameObject* root;
	GameObject* selected = nullptr;
	CustomQuadTree* quadtree = nullptr;
	AABB limits;

	bool wantToSave = false;
	bool wantToLoad = false;

	bool accelerateFrustumCulling = true;

	std::string loadPath;

	Timer saveLoadTimer;
	std::vector<GameObject*> sceneObjects_;
	std::vector<GameObject*> objectToDraw_;

	MeshImporter* mesh1;
};

#endif
