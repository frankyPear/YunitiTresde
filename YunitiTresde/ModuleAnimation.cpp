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
		//
		//(*scene->mAnimations)->mDuration
		//(*(*scene->mAnimations)->mChannels)->mNodeName
		//(*(*scene->mAnimations)->mChannels)->mPositionKeys
		//(*(*scene->mAnimations)->mChannels)->mRotationKeys
		
	}
	for (int i = 0; i < scene->mNumAnimations; i++) {
		AnimArrayChannel* anim = new AnimArrayChannel();
		anim->animDuration = (*scene->mAnimations)->mDuration;
		anim->nodeName = (*(*scene->mAnimations)->mChannels)->mNodeName;
		anim->arrayAnimationPos = (*(*scene->mAnimations)->mChannels)->mPositionKeys;
		anim->arrayAnimationRot = (*(*scene->mAnimations)->mChannels)->mRotationKeys;
		animNodes_.push_back(anim);
	}
}

