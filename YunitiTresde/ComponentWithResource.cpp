#include "ComponentWithResource.h"
#include "Application.h"
#include "ModuleResources.h"

ComponentWithResource::ComponentWithResource()
{
}


ComponentWithResource::~ComponentWithResource()
{
}



uint  ComponentWithResource::GetResourceId() const
{
	return _resourceId;
}

const Resource * ComponentWithResource::GetResource() const
{
	return App->resources->Get(_resourceId);
}


