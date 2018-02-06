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
	void SetFOV(float degrees);
	void SetAspectRatio();
	void SetPlaneDistances(float zNear, float zFar);
	void SetPosition(float3 newPos);
	float *GetProjectionMatrix();
	float *GetViewMatrix();

	bool CleanUp();

public:
	ComponentCamera *dummyCamera;

private:

	Frustum frustum_;
	float camSpeed_;
	float aspectRatio_;
};



#endif // !_MODULECAMERA_

