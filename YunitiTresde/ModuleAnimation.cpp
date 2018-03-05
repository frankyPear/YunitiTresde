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
		AnimArrayChannel* anim = new AnimArrayChannel();
		aiAnimation *sceneAnim = scene->mAnimations[i];
		anim->animDuration = (scene->mAnimations[i])->mDuration;
		for (int j = 0; j < (scene->mAnimations[i])->mNumChannels; j++) {
			anim->nodeName = (scene->mAnimations[i])->mChannels[j]->mNodeName;
			anim->arrayAnimationPos = scene->mAnimations[i]->mChannels[j]->mPositionKeys;
			anim->arrayAnimationRot = scene->mAnimations[i]->mChannels[j]->mRotationKeys;
			animNodes_.push_back(anim);
			//for (int k = 0; k < ((scene->mAnimations[i])->mChannels[j])->mNumPositionKeys;k++) {
			//	for (int l = 0; l < ((scene->mAnimations[i])->mChannels[j])->mNumRotationKeys; l++) {
			//		anim->arrayAnimationPos = scene->mAnimations[i]->mChannels[j]->mPositionKeys[k];// mPositionKeys;
			//		anim->arrayAnimationRot = scene->mAnimations[i]->mChannels[j]->mRotationKeys[l];
			//		animNodes_.push_back(anim);
			//	}
			//}
		}
	}
}

