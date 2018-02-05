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

#pragma endregion


#pragma region Setters
	void SetPosition(math::float3 position);

	void SetScale(math::float3 scale);

	void SetEulerRotation(math::float3 rotation);



#pragma endregion

private:
	math::float3 _position = { 0,0,0 };

	math::float3 _scale = {1,1,1};

	math::float3 _rotationEulerAngles = { 0,0,0 };
};

