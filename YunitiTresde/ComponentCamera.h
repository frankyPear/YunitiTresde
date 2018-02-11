#pragma once
#include "Component.h"
#include "Mathgeolib\include\Geometry\Frustum.h"
#include "Mathgeolib\include\MathGeoLib.h"


class ComponentCamera :
	public Component
{
	friend class ModuleCamera;
public:
	ComponentCamera();
	~ComponentCamera();

	bool PreUpdate();
	bool Update();
	bool PostUpdate();
	bool Destroy();
	bool OnEditor();

	void SetFOV(float degrees);
	void SetAspectRatio();
	void SetPlaneDistances(float zNear, float zFar);
	void SetPosition(float3 newPos);
	void SetFront(float3 newFront);
	void SetUp(float3 newUp);

	//void LookAt(int x, int y, int z);
	float *GetProjectionMatrix();
	float *GetViewMatrix();
	Frustum *GetFrustum();

	float3 GetPosition() const;
	float3 GetFront() const;
	float3 GetWorldRight() const;
	float3 GetUp() const;

	void DrawFrustum();
	void NormalizeUp();
	void NormalizeFront();
	bool CheckAABBIntersection(AABB box);

private:
	Frustum frustum_;
	float aspectRatio_;
	bool drawFrustumEnabled_;
	bool frustrumCulling_;
};

