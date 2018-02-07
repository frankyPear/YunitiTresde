#ifndef _MODULECAMERA_
#define _MODULECAMERA_

#include "Module.h"
#include "ComponentCamera.h"


class ModuleCamera :
	public Module
{

public:
	ModuleCamera();
	~ModuleCamera();

	bool Init();

	update_status PreUpdate(float dt);
	update_status Update(float dt);

	bool CleanUp();

public:
	ComponentCamera *dummyCamera;

private:

	float camSpeed_;
	float aspectRatio_;
};



#endif // !_MODULECAMERA_

