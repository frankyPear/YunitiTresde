#include "ComponentTransform.h"
#include "GameObject.h"


ComponentTransform::ComponentTransform()
{
}

ComponentTransform::ComponentTransform(float3 position, float3 scale, Quat rotation) : _position(position), _scale(scale), _quatRotation(rotation)
{
	_rotationEulerAngles = rotation.ToEulerXYZ();
	_rotationEulerAngles = float3(RadToDeg(_rotationEulerAngles.x), RadToDeg(_rotationEulerAngles.y), RadToDeg(_rotationEulerAngles.z));
	_globalTransMatrix = float4x4::FromTRS( _position, _quatRotation, _scale);
	type = TRANSFORMATION;
	updateTrans = false;
}

ComponentTransform::~ComponentTransform()
{
}

math::float3 ComponentTransform::GetPosition() const
{
	return _position;
}

float3 ComponentTransform::GetScale() const
{
	return _scale;
}

float3 ComponentTransform::GetEulerRotation() const
{
	return _rotationEulerAngles;
}

Quat ComponentTransform::GetQuatRotation()const
{
	return _quatRotation;
}


void ComponentTransform::SetPosition(math::float3 position)
{
	_position = position;
}

void ComponentTransform::SetScale(math::float3 scale)
{
	_scale = scale;
}

void ComponentTransform::SetRotation(Quat rotation)
{
	_quatRotation = rotation;
	_rotationEulerAngles = rotation.ToEulerXYZ();
	_rotationEulerAngles = float3(RadToDeg(_rotationEulerAngles.x), RadToDeg(_rotationEulerAngles.y), RadToDeg(_rotationEulerAngles.z));

}

float3 ComponentTransform::GetGlobalPosition() const {
	float3 globalPos, globalScale;
	Quat globalRot;
	_globalTransMatrix.Decompose(globalPos, globalRot, globalScale);
	return globalPos;
}


float4x4 ComponentTransform::GetGlobalTransform() const
{	
	return _globalTransMatrix;
}

float4x4 ComponentTransform::GetLocalTransform() const
{
	return _localTransMatrix;

}

bool ComponentTransform::PreUpdate() 
{
	return true;
}

bool ComponentTransform::Update()
{
	if (updateTrans) {
		UpdateTransform();
		updateTrans = false;
	}
	return true;
}

bool ComponentTransform::PostUpdate()
{
	return true;
}

bool ComponentTransform::Destroy()
{
	return true;
}

bool ComponentTransform::DisplayImgUINode()
{
	return true;
}

void ComponentTransform::UpdateTransform()
{
	_rotationEulerAngles = float3(DegToRad(_rotationEulerAngles.x), DegToRad(_rotationEulerAngles.y), DegToRad(_rotationEulerAngles.z));
	_quatRotation = Quat::FromEulerXYZ(_rotationEulerAngles.x, _rotationEulerAngles.y, _rotationEulerAngles.z);
	
	_globalTransMatrix = float4x4::FromTRS(_position, _quatRotation, _scale);
	
	_rotationEulerAngles = float3(RadToDeg(_rotationEulerAngles.x), RadToDeg(_rotationEulerAngles.y), RadToDeg(_rotationEulerAngles.z));
	_localTransMatrix = _globalTransMatrix;

	if (linked_to != nullptr && linked_to->GetParent() != nullptr)
	{
		ComponentTransform *parentTransform = (ComponentTransform *)linked_to->GetParent()->GetComponent(type);
		if (parentTransform != nullptr)
		{
			_globalTransMatrix = parentTransform->GetGlobalTransform() * _globalTransMatrix;
		}
	}
	updateTrans = false;
	linked_to->ChildrenTransformUpdate();
}

void ComponentTransform::ForceUpdate()
{
	updateTrans = true;
}
