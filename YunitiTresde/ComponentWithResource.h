#pragma once
#include "Globals.h"
class Resource;

class ComponentWithResource
{
public:
	//Constructor
	ComponentWithResource();

	//Destructor
	virtual ~ComponentWithResource();

#pragma region Getters
	virtual const Resource * GetResource()const;
	virtual uint GetResourceId()const;

#pragma endregion

#pragma region Setters
	virtual bool SetResource(uid id)=0;
#pragma endregion


protected:
	uid _resourceId = 0;//Resource id
};
