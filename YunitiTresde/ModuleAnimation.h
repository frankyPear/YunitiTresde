#pragma once
#include "Module.h"
#include "assimp\assimp\cimport.h"
#include "assimp\assimp\postprocess.h"
#include "assimp\assimp\scene.h"
#include "assimp\assimp\Importer.hpp"
#include <map>
#include <vector>

typedef uint AnimInstanceID;

struct LessString {
	bool operator() (const aiString& a, aiString& b) const {
		return a.C_Str() < b.C_Str();
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
	uint time = 0;
	bool loop = false;

	AnimInstance *nextAnim = nullptr;
	uint blend_duration = 0;
	uint blend_time = 0;
};


class ModuleAnimation :
	public Module
{
	typedef std::map<aiString, Anim*, LessString> AnimMap;
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
	
public:
	uint AnimId;
	const aiScene* scene = nullptr;
	Assimp::Importer importer;
	//std::vector<GameObject*> objectToDraw_;
};

