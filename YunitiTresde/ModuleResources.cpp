#include "ModuleResources.h"
#include "Resource.h"
#include "ResourceAudio.h"
#include "ResourceMesh.h"

ModuleResources::ModuleResources()
{
}


ModuleResources::~ModuleResources()
{
	for (std::map<uid, Resource*>::iterator it = _resources.begin(); it != _resources.end(); ++it)
		RELEASE(it->second);
	_resources.clear();

}

Resource * ModuleResources::Get(uid resourceId)
{
	std::map<uid, Resource*>::iterator it = _resources.find(resourceId);

	return it != _resources.end() ? it->second : nullptr;
}

void ModuleResources::AddResource(const char* audioType)
{
	if ("audio") {
		ResourceAudio *ar = new ResourceAudio(ResourceCounter, Resource::audio);
		_resources[ResourceCounter] = ar;
		++ResourceCounter;
	}
}

//void ModuleResources::OnSaveResource(Config & config) const
//{
//	//config.
//}

//void ModuleResources::OnLoadResource(Config * config)
//{
//}
