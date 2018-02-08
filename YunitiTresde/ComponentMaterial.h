#pragma once
#include "Component.h"
#include <vector>
#include "ComponentWithResource.h"

class ComponentMaterial :
	public Component,public ComponentWithResource
{
public:

	//Constructor
	ComponentMaterial(GameObject *gameObject);


	//Destructor
	~ComponentMaterial();

#pragma region Setters

	bool SetResource(uid resourceId)override;

#pragma endregion


#pragma Component methods
	void AddMaterialResource(unsigned int uid);

#pragma endregion

#pragma region Editor methods
	void OnEditor();

#pragma endregion
	
private:
	



};

