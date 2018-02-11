#include "ModuleResources.h"


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

void ModuleResources::OnSaveResource(Config & config) const
{
	//config.
}

void ModuleResources::OnLoadResource(Config * config)
{
}
