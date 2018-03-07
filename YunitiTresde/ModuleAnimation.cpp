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
		aiString  name = sceneAnim->mName;
		animations[name] = animation;
	}
}

bool ModuleAnimation::GetTransform(uint animId, const char* channel, aiVector3D& position, aiQuaternion& rotation)
{
	if (!instances.empty()) {
		bool ret = false;
		AnimInstance *instance = instances[animId];
		Anim* animation = instance->animation;
		for (int i = 0; i < animation->numChannels; ++i)
		{
			NodeAnim * node = animation->channelArray[i];
			if (node->animNodeName.C_Str() == channel)
			{
				Vector3DInterpolation(position, node->positionArray[0], 0.5f);
				InteropQuaternion(rotation, node->rotationArray[0], 0.5f);
				ret = true;
			}
		}
		if (!ret) LOG("Error canal no encontrado")
		else LOG("Canal encontrado")
			return ret;
	}
}

uint ModuleAnimation::Play(const char* name)
{
	AnimInstance *instance = new AnimInstance;
	aiString channelname = aiString(name);
	std::map<aiString, Anim*, LessString>::iterator it = animations.begin();
	it = animations.find(channelname);
	if (it != animations.end()) {
		Anim* anim = it->second;
		instance->animation = anim;
		instance->loop = false;
		instances.push_back(instance);
		AnimId = (instances.size() - 1);
		return (uint)(instances.size() - 1);
	}
	else return -1;
}


aiVector3D ModuleAnimation::Vector3DInterpolation(const aiVector3D & first, const aiVector3D & second, float lambda) const
{
	return first*(1.0f - lambda) + second*lambda;
}

aiQuaternion ModuleAnimation::InteropQuaternion(const aiQuaternion & firstQuat, const aiQuaternion & secondQuat, float lambda) const
{
	aiQuaternion quatInterpolated;
	float dot = (firstQuat.x*secondQuat.x) + (firstQuat.y*secondQuat.y) +
		(firstQuat.z*secondQuat.z) + (firstQuat.w*secondQuat.w);
	if (dot >= 0.0f) {
		quatInterpolated.x = firstQuat.x*(1.0f - lambda) + secondQuat.x*lambda;
		quatInterpolated.y = firstQuat.y*(1.0f - lambda) + secondQuat.y*lambda;
		quatInterpolated.z = firstQuat.z*(1.0f - lambda) + secondQuat.z*lambda;
		quatInterpolated.w = firstQuat.w*(1.0f - lambda) + secondQuat.w*lambda;
	}
	else
	{
		quatInterpolated.x = firstQuat.x*(1.0f - lambda) + secondQuat.x*-lambda;
		quatInterpolated.y = firstQuat.y*(1.0f - lambda) + secondQuat.y*-lambda;
		quatInterpolated.z = firstQuat.z*(1.0f - lambda) + secondQuat.z*-lambda;
		quatInterpolated.w = firstQuat.w*(1.0f - lambda) + secondQuat.w*-lambda;

	}

	quatInterpolated.Normalize();


	return quatInterpolated;
}

void ModuleAnimation::UpdateInstanceTime(float time)
{
	for (int i = 0; i < instances.size(); ++i)
	{
		instances[i]->time += time;
	}
}
