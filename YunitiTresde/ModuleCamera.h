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

#pragma region Movement methods
public:
	void Look(const float3& position);
private:
	void Orbit(float motionX, float motionY);
	void Zoom(float zoom);
	void LookAt(float motionX, float motionY);
	void CenterOn(const float3 &position, float distance);
	GameObject *Pick(float3* hitPoint=nullptr)const;
#pragma endregion
private:
	float _isLooking = true;

	float3 _lookingAt;
	float camSpeed_;
	float _rotationSpeed = 1;
	float _zoomSpeed=15;
	float aspectRatio_;
};



#endif // !_MODULECAMERA_

