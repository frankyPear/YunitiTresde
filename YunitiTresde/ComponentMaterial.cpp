#include "ComponentMaterial.h"



ComponentMaterial::ComponentMaterial()
{
}


ComponentMaterial::~ComponentMaterial()
{
}

void ComponentMaterial::SetMaterialResource(std::vector<MaterialResource*> materialResource)
{
	_materialResources = materialResource;
}

void ComponentMaterial::AddTexture(MaterialResource & materialResource)
{
	_materialResources.push_back(&materialResource);
}

void ComponentMaterial::ClearMaterialResource()
{
	unsigned int materialResourcesSize = _materialResources.size();
	for (unsigned int i = 0; i < materialResourcesSize; i++) {

	}
	_materialResources.clear();

}
