#include "ModuleAnimation.h"
#include "ComponentAnim.h"
#include <assert.h>


ModuleAnimation::ModuleAnimation()
{
}


ModuleAnimation::~ModuleAnimation()
{
}

bool ModuleAnimation::Init()
{
	return true;
}

bool ModuleAnimation::Start()
{
	if (scene != nullptr) {
		if (scene->mAnimations != 0)
		{

		}
		else
		{
			LOG("No Animations to Load");
		}
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
	UpdateInstanceTime(dt);
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
			NodeAnim* node = new NodeAnim();
			node->animNodeName = ainodeanim->mNodeName;
			node->numPositions = ainodeanim->mNumPositionKeys;
			node->numRotations = ainodeanim->mNumRotationKeys;
			node->positionArray = new aiVector3D[node->numPositions];
			node->rotationArray = new aiQuaternion[node->numRotations];
			for (int k = 0; k < node->numPositions; ++k) {
				node->positionArray[k].x = ainodeanim->mPositionKeys[k].mValue.x ;
				node->positionArray[k].y = ainodeanim->mPositionKeys[k].mValue.y;
				node->positionArray[k].z = ainodeanim->mPositionKeys[k].mValue.z;

				node->rotationArray[k].x = ainodeanim->mRotationKeys[k].mValue.x;
				node->rotationArray[k].y = ainodeanim->mRotationKeys[k].mValue.y;
				node->rotationArray[k].z = ainodeanim->mRotationKeys[k].mValue.z;
				node->rotationArray[k].w = ainodeanim->mRotationKeys[k].mValue.w;

			}
			animation->channelArray.push_back(node);

		}
		const char*  name = sceneAnim->mName.C_Str();
		animations[name] = animation;
	}
}

bool ModuleAnimation::GetTransform(uint animId, const char* channel, aiVector3D& position, aiQuaternion& rotation)
{
	if (!instances.empty()) {
		
		bool ret = false;
		AnimInstance *instance = instances[animId];
		Anim* animation = instance->animation;
		NodeAnim * node = nullptr;
		for (int i = 0; i < animation->numChannels && !ret; ++i)
		{
			node = animation->channelArray[i];
			if (strcmp( node->animNodeName.C_Str(), channel) == 0)
			{
				ret = true;
			}
		}
		if (!ret) LOG("Error channel not found")
		else
		{
			//position = node->positionArray[252];
			//rotation = node->rotationArray[252];
			//return true;
			uint animationDuration = animation->animDuration;
			uint instanceTime = instance->time;
			uint posCount = node->numPositions;
			uint rotCount = node->numRotations;
			if (instanceTime > animationDuration)
			{
				if (instance->loop)
				{
					instance->time -= animation->animDuration;
					instanceTime = instance->time;
				}
				else {
					instanceTime = animationDuration;
				}
			}

			assert(instanceTime <= animationDuration);

			float posKey = float( instanceTime * (posCount - 1) ) / animationDuration;
			float rotKey = float( instanceTime * (rotCount - 1) ) / animationDuration;
			uint actualPos = uint(posKey);
			uint actualRot = uint(rotKey);
			assert(actualPos >= 0 && actualPos < posCount);
			assert(actualRot >= 0 && actualRot < posCount);
			float posKeyNext = float(actualPos + 1) / posCount;
			float rotKeyNext = float(actualRot + 1) / rotCount;

			uint targetPos = uint(posKeyNext);
			uint targetRot = uint(rotKeyNext);
			assert(targetPos >= 0 && targetPos < posCount);
			assert(targetRot >= 0 && targetRot < posCount);
			float posLambda = posKey - actualPos;
			float rotLambda = rotKey - actualRot;    
			position = node->positionArray[actualPos];
			rotation = node->rotationArray[actualPos];
			//aiVector3D& interpPos = Vector3DInterpolation(node->positionArray[actualPos], node->positionArray[targetPos], posLambda);
			//aiQuaternion& interpRot = InteropQuaternion(node->rotationArray[actualRot], node->rotationArray[targetRot], rotLambda);

		}
		return ret;
	}
}

uint ModuleAnimation::Play(const char* name)
{
	AnimInstance *instance = new AnimInstance;
	aiString channelname = aiString(name);
	std::map<const char*, Anim*, LessString>::iterator it = animations.begin();
	it = animations.find(name);
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
		instances[i]->time += (time)*32;
	}
}


void ModuleAnimation::RecursiveAnimAssociation(GameObject* root)
{
	std::vector<GameObject*> childs = root->GetChilds();
	if (childs.size() > 0) 
	{
		ComponentAnim *ca = new ComponentAnim();
		ca->SetAnimIdAndName(-1 , root->GetName().c_str());
		for (int i = 0; i < childs.size(); ++i)
		{
			RecursiveAnimAssociation(childs[i]);
		}
	}
}

void RecursiveAnimationIDSetting(GameObject* start, int id)
{
	ComponentAnim *ca = (ComponentAnim *) start->GetComponent(ANIMATION);
	if (ca != nullptr)
	{
		std::vector<GameObject*> childs = start->GetChilds();
		ca->SetAnimId(id);
		for (int i = 0; i < childs.size(); ++i)
		{
			RecursiveAnimationIDSetting(childs[i],id);
		}
	}
}

