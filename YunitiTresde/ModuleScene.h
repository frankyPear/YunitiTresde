#ifndef __ModuleScene_H__
#define __ModuleScene_H__

#include "Module.h"

class GameObject;
class Mesh;
class Quadtree;

class ModuleScene : public Module
{
public:
	ModuleScene();
	~ModuleScene();

};


	bool Init();
	bool Start();
	bool CleanUp();

	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);

	//Imgui
	void ShowImguiStatus();

	GameObject* GetRoot();


public:
	bool recalcTree = false;

private:
	GameObject* root;
	GameObject* selected = nullptr;
	Quadtree* tree = nullptr;

	bool wantToSave = false;
	bool wantToLoad = false;
	std::string loadPath;

	Timer saveLoadTimer;
};

#endif
