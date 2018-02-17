#include "ComponentTransform.h"
#include "GameObject.h"
#include "imgui-1.53\imgui.h"
#include "imgui-1.53\imgui_impl_sdl_gl3.h"
#include "Brofiler\include\Brofiler.h"

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

bool ComponentTransform::Update(GameObject* obj)
{
	BROFILER_CATEGORY("ComponentTransform Update", Profiler::Color::Azure);
	ComponentTransform* ct = (ComponentTransform*)obj->GetComponent(TRANSFORMATION);
	if (updateTrans && ct!=nullptr) {
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

void ComponentTransform::OnEditor(GameObject* obj)
{
	if (ImGui::TreeNode("Transform"))
	{
	
		ImGui::Text("Position:");
		if (ImGui::DragFloat3("X", &_position.x, 0.05f, NULL, NULL, "%.2f"))
		{
			updateTrans = true;
		}
		ImGui::Text("Scale:");
		if (ImGui::DragFloat3("X##1", &_scale.x, 0.05f, 1.0f, NULL, "%.2f"))
		{
			updateTrans = true;
		}
		ImGui::Text("Rotation:");
		if (ImGui::DragFloat3("X##2", &_rotationEulerAngles.x, 0.05f, -180, 180, "%.2f"))
		{
			updateTrans = true;
		}
		ImGui::Separator();

		if (ImGui::Button("Reset"))
		{
			_position = float3::zero;
			_scale = float3::one;
			_rotationEulerAngles = float3::zero;
			updateTrans = true;
		}
		//---
		uint i = 0;
		ImGui::SameLine();
		ImGui::PushID(i = 0);
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(i / 7.0f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(i / 7.0f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(i / 7.0f, 0.8f, 0.8f));
		if (ImGui::Button("Delete"))
		{
			obj->OnDestroy();
			//Not working
			delete obj;
			obj = nullptr;
		}
		ImGui::PopStyleColor(3);
		ImGui::PopID();

		ImGui::TreePop();
	}

}