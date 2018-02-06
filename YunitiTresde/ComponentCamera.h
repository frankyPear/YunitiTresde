#pragma once
#include "Component.h"
#include "Mathgeolib\include\Geometry\Frustum.h"
#include "Mathgeolib\include\MathGeoLib.h"


class ComponentCamera :
	public Component
{
public:
	ComponentCamera();
	~ComponentCamera();

	void SetFOV(float degrees);
	void SetAspectRatio();
	void SetPlaneDistances(float zNear, float zFar);
	void SetPosition(float3 newPos);
	//void LookAt(int x, int y, int z);
	float *GetProjectionMatrix();
	float *GetViewMatrix();
	Frustum *GetFrustum();

	float3 GetPosition() const;
	float3 GetFront() const;
	float3 GetWorldRight() const;

private:
	Frustum frustum_;
	float aspectRatio_;
};

