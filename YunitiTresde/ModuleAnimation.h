#pragma once
#include "Module.h"
#include "assimp\assimp\cimport.h"
#include "assimp\assimp\postprocess.h"
#include "assimp\assimp\scene.h"
#include "assimp\assimp\Importer.hpp"
#include "GameObject.h"
#include <map>
#include <vector>


typedef uint AnimInstanceID;

struct LessString {
	bool operator() (const char* a, const char* b) const {
		return strcmp(a,b);
	}
};

struct NodeAnim
{
	aiString animNodeName = aiString("default-name");
	aiVector3D* positionArray = nullptr;
	uint numPositions = 0;
	aiQuaternion* rotationArray = nullptr;
	uint numRotations = 0;
};

struct Anim
{
	std::vector<NodeAnim *>channelArray;
	uint numChannels = 0;
	uint animDuration = 0;
};

struct AnimInstance 
{
	Anim *animation = nullptr;
	float time = 0.0f;
	bool loop = true;

	AnimInstance *nextAnim = nullptr;
	uint blend_duration = 0;
	uint blend_time = 0;
};


class ModuleAnimation :
	public Module
{
	typedef std::map<const char*, Anim*, LessString> AnimMap;
	typedef std::vector<AnimInstance*> InstanceList;
	typedef std::vector<AnimInstanceID> HoleList;

	AnimMap animations;
	InstanceList instances;

public:
	ModuleAnimation();
	~ModuleAnimation();

	bool Init();
	bool Start();
	bool CleanUp();

	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);

	void Load(aiString name, const char* filepath);
	uint Play(const char* name);
	void Stop(uint id);
	void BlendTo(uint id, const char* name, uint blend_time);
	bool GetTransform(uint animId, const char* channel, aiVector3D& position, aiQuaternion& rotation);
	void UpdateInstanceTime(float time);
	void RecursiveAnimAssociation(GameObject* root);

	aiVector3D Vector3DInterpolation(const aiVector3D & firstQuat, const aiVector3D & secondQuat, float lambda) const;
	aiQuaternion InteropQuaternion(const aiQuaternion & firstQuat, const aiQuaternion & secondQuat, float lambda) const;


public:
	int AnimId = -1;
	const aiScene* scene = nullptr;
	Assimp::Importer importer;
	//std::vector<GameObject*> objectToDraw_;
};

