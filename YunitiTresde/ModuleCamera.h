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


	update_status PreUpdate(float dt);
	update_status Update(float dt);

	void SetFOV(float degrees);
	void SetAspectRatio();
	void SetPlaneDistances(float zNear, float zFar);
	void SetPosition(float3 newPos);

//	void DrawMatrix(Frustum fr_);


	//void LookAt(int x, int y, int z);
	float *GetProjectionMatrix();
	float *GetViewMatrix();

	bool CleanUp();

public:



private:

	Frustum frustum_;
	float camSpeed_;
	float aspectRatio_;
};



#endif // !_MODULECAMERA_

