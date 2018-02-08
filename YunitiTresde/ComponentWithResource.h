#pragma once
#include "Globals.h"
class Resource;

class ComponentWithResource
{
public:
	ComponentWithResource();
	virtual ~ComponentWithResource();

	virtual bool SetResource(uid id)=0;

	virtual uint GetResourceId()const;

	virtual const Resource * GetResource()const;

protected:
	uid _resourceId = 0;
};
