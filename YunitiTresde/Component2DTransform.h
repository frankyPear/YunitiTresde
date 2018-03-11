#pragma once
#include "Component.h"
#include "Mathgeolib\include\Geometry\Frustum.h"
#include "Mathgeolib\include\MathGeoLib.h"
#include "ModuleUI.h"
#include "Component2D.h"
//Crear un componente individual para cada uno.



class Component2DTransform :
	public Component
{
	friend class ModuleUI;
public:
	Component2DTransform();
	~Component2DTransform();

	bool PreUpdate();
	bool Update();
	bool PostUpdate();
	bool Destroy();
	bool OnEditor();	
	void getFormat(CElement2D Comp2D, GameObject* obj, int x, int y, int h, int w);
	static Component2DTransform* getInstance();
	void SetFOV(float degrees);
	void SetAspectRatio();
	void SetPlaneDistances(float zNear, float zFar);
	void SetPosition(float3 newPos);
	void SetFront(float3 newFront);
	void SetUp(float3 newUp);

	



private:
	Frustum frustum_;

	float aspectRatio_;
	bool drawFrustumEnabled_;
	bool frustrumCulling_;
};

