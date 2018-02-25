#pragma once
#include "Component.h"
#include "Mathgeolib\include\MathGeoLib.h"

class ComponentTransform :
	public Component
{
public:
	///Constructor
	ComponentTransform();
	
	ComponentTransform(float3 position, float3 scale, Quat rotation);
	///Destructor
	~ComponentTransform();

	bool PreUpdate();

	bool Update(GameObject* obj);

	bool PostUpdate();

	bool Destroy();

	bool DisplayImgUINode();

	void OnEditor(GameObject* obj);

	void EditTransform(float* TransposedMatrix, float* Position, float* Rotation, float* Scale);

	void SetGlobalTransform(float4x4 newTransform);

#pragma region Getters

	float3 GetPosition()const;

	float3 GetScale()const;

	float3 GetEulerRotation()const;

	Quat GetQuatRotation()const;

	float3 GetGlobalPosition() const;

	float4x4 GetGlobalTransform() const;

	float4x4 GetLocalTransform() const;

#pragma endregion


#pragma region Setters
	void SetPosition(float3 position);

	void SetScale(float3 scale);

	void SetRotation(Quat rotation);

	void UpdateTransform();

	void ForceUpdate();

#pragma endregion

private:
	float3 _position;

	float3 _scale;

	float3 _rotationEulerAngles;

	Quat _quatRotation;
	
	float4x4 _globalTransMatrix;

	float4x4 _localTransMatrix;

	bool updateTrans;

};

