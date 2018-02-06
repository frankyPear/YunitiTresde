#pragma once
#include "Component.h"
#include "Math.h"
class ComponentTransform :
	public Component
{
public:
	///Constructor
	ComponentTransform();

	///Destructor
	~ComponentTransform();


#pragma region Getters

	math::float3 GetPosition()const;

	math::float3 GetScale()const;

	math::float3 GetEulerRotation()const;

	math::Quat GetRotationQuat()const;

	math::float4x4 GetTransform()const;

	math::float4x4 GetInheritedTransform()const;

#pragma endregion


	void UpdateTransform();

#pragma region Setters
	void SetPosition(math::float3 position);

	void SetScale(math::float3 scale);

	void SetEulerRotation(math::float3 rotation);

	void SetTransform(math::float4x4 matrix);


#pragma endregion

private:
	math::float4x4 _matrixTransform = math::float4x4::identity;

	math::float3 _position = { 0,0,0 };

	math::float4x4 _inheritedTransform = math::float4x4::identity;

	math::float3 _scale = {1,1,1};

	math::float3 _rotationEulerAngles = { 0,0,0 };

	math::Quat _rotationQuaternion = math::Quat::identity;
};

