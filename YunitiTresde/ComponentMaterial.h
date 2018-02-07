#pragma once
#include "Component.h"
#include <vector>
class MaterialResource;

class ComponentMaterial :
	public Component
{
public:

	//Constructor
	ComponentMaterial();


	//Destructor
	~ComponentMaterial();

#pragma region Setters
	void SetMaterialResource(std::vector<MaterialResource*> materialResource);


#pragma endregion


#pragma Component methods
	void AddTexture(MaterialResource &materialResource);

	void ClearMaterialResource();
#pragma endregion
private:
	std::vector<MaterialResource*> _materialResources;



};

