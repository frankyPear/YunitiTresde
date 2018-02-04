#include "ComponentTransform.h"



ComponentTransform::ComponentTransform()
{
}


ComponentTransform::~ComponentTransform()
{
}

math::float3 ComponentTransform::GetPosition() const
{
	return _position;
}

math::float3 ComponentTransform::GetScale() const
{
	return _scale;
}

math::float3 ComponentTransform::GetEulerRotation() const
{
	return _rotationEulerAngles;
}

void ComponentTransform::SetPosition(math::float3 position)
{
	_position = position;
}

void ComponentTransform::SetScale(math::float3 scale)
{
	_scale = scale;
}

void ComponentTransform::SetEulerRotation(math::float3 rotation)
{
	_rotationEulerAngles = rotation;
}
