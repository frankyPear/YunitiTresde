#ifndef _MODULECAMERA_
#define _MODULECAMERA_

#include "Module.h"
#include "Mathgeolib\include\Geometry\Frustum.h"


class ModuleCamera :
	public Module
{

public:
	ModuleCamera();
	~ModuleCamera();

	bool Init();

	update_status PreUpdate();
	update_status Update();

	bool CleanUp();

public:



private:

	Frustum frustum_;

};



#endif // !_MODULECAMERA_

