#ifndef __ModuleScene_H__
#define __ModuleScene_H__

#include "Module.h"
#include "ComponentCamera.h"
#include "Model.h"
#include "CustomQuadTree.h"
#include "assimp\assimp\cimport.h"
#include "assimp\assimp\postprocess.h"
#include "assimp\assimp\scene.h"
#include "assimp\assimp\Importer.hpp"
#include "MeshImporter.h"
#include <vector>

class GameObject;
class Mesh;
class Quadtree;
class MeshImporter;

class ModuleScene : public Module
{
public:

	static enum BUFFERS {
		VERTEX_BUFFER, TEXCOORD_BUFFER, NORMAL_BUFFER, INDEX_BUFFER
	};

	ModuleScene();
	~ModuleScene();



	bool Init();
	bool Start();
	bool CleanUp();

	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	//Create
	void CreateGameObject(GameObject* obj, bool boolcm = false, bool boolcam = false);

	//Imgui
	void ShowImguiStatus();
	void ImGuiMainMenu();
	void Hierarchy();
	GameObject* GetRoot();

	void ToggleFrustumAcceleration();
	void CreateRay(float2 screenPoint);

	void LoadScene(const char* filepath);

	GameObject*  RecursiveSceneGeneration(aiNode*toVisit, GameObject* parent ,const aiMatrix4x4 &transformation, int modelID );

	void DrawHierarchy();

	void meshEntry(aiMesh * mesh);

	void Draw();

public:
	ComponentCamera *actualCamera = nullptr;
	uint imguiFlag = 0;
	bool recreateQuadTree = false;
	bool drawQuadTree = false;
	uint imguiCollisionTest = 0;
	uint imguiCollisionTestQuadtree = 0;
	bool wantToDelete = false;
	GLuint vbo[4];
	GLuint vao;
	unsigned int elementCount;
	std::vector<aiMesh*> meshes;
	std::vector<GLuint> vaos;
	std::map<int,Model*> models;
	GameObject *modelObjRoot;

private:
	GameObject* root;
	GameObject* selected = nullptr;
	CustomQuadTree* quadtree = nullptr;
	AABB limits;
	const aiScene* scene = nullptr;
	Assimp::Importer importer;


	bool wantToSave = false;
	bool wantToLoad = false;

	bool accelerateFrustumCulling = false;

	std::string loadPath;

	Timer saveLoadTimer;
	std::vector<GameObject*> sceneObjects_;
	std::vector<GameObject*> objectToDraw_;
	std::vector<aiMaterial*> materials;



	MeshImporter* mesh1;
	Model* model;
	std::vector<uint> id;

};

#endif
