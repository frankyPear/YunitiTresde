#include "ComponentTransform.h"
//NOTICE:

//Added includes
#include "imgui-1.53\imgui.h"
#include "imgui-1.53\imgui_impl_sdl_gl3.h"

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

math::Quat ComponentTransform::GetRotationQuat() const
{
	return _rotationQuaternion;
}

math::float4x4 ComponentTransform::GetTransform() const
{
	return _matrixTransform;
}

math::float4x4 ComponentTransform::GetInheritedTransform() const
{
	return _inheritedTransform;
}

void ComponentTransform::UpdateTransform()
{


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

void ComponentTransform::SetTransform(math::float4x4 trans)
{

}
