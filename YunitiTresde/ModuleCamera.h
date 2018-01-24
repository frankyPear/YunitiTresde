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
	//int SetFOV();
	//int SetAspectRatio();
	//int SetPlaneDistances();
	//int SetPosition();
	//void LookAt(int x, int y, int z);
	//void GetProjectionMatrix();
	//void GetViewMatrix();

	bool CleanUp();

public:



private:

	Frustum frustum_;

};



#endif // !_MODULECAMERA_

