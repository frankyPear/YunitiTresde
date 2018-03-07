#include "ModuleAnimation.h"



ModuleAnimation::ModuleAnimation()
{
}


ModuleAnimation::~ModuleAnimation()
{
}

bool ModuleAnimation::Init()
{
	aiString animNodeName = aiString("FirstAnimation");
	Load(animNodeName,"../Resources/Animations/ArmyPilot/ArmyPilot_Idle.fbx");
	return true;
}

bool ModuleAnimation::Start()
{
	if (scene->mAnimations != 0)
	{

	}
	else
	{
		LOG("No Animations to Load");
	}
	return true;
}

bool ModuleAnimation::CleanUp()
{
	return true;
}

update_status ModuleAnimation::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleAnimation::Update(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleAnimation::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

void ModuleAnimation::Load(aiString name, const char* filepath)
{
	scene = importer.ReadFile(filepath,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);
	if (!scene)
	{
		LOG("ERROR LOADING SCENE");
	}
	else {
		LOG("SCENE LOADED");
	}
	for (int i = 0; i < scene->mNumAnimations; i++) {
		AnimInstance *instance = new AnimInstance;
		if (i > 0) {
			AnimInstance *previous = instances[instances.size() - 1];
			previous->nextAnim = instance;
		}
		Anim* animation = new Anim;
		aiAnimation *sceneAnim = scene->mAnimations[i];
		animation->animDuration = sceneAnim->mDuration;
		animation->numChannels = sceneAnim->mNumChannels;
		for (int j = 0; j < sceneAnim->mNumChannels; j++) {
			aiNodeAnim* ainodeanim = sceneAnim->mChannels[j];
			NodeAnim* node = new NodeAnim;
			node->animNodeName = ainodeanim->mNodeName;
			node->numPositions = ainodeanim->mNumPositionKeys;
			node->numRotations = ainodeanim->mNumRotationKeys;
			node->positionArray = &ainodeanim->mPositionKeys->mValue;
			node->rotationArray = &ainodeanim->mRotationKeys->mValue;
			animation->channelArray.push_back(node);
		}
		instance->animation = animation;
		instance->loop = false;
		instances.push_back(instance);
	}
}

