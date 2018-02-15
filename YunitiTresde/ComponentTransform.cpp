#include "ComponentTransform.h"
#include "GameObject.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleScene.h"
#include "ModuleCamera.h"
#include "imgui-1.53\imgui.h"
#include "imgui-1.53\imgui_impl_sdl_gl3.h"
#include "imgui-1.53\ImGuizmo.h"
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

bool ComponentTransform::Update()
{
	BROFILER_CATEGORY("ComponentTransform Update", Profiler::Color::Azure);
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

void ComponentTransform::OnEditor(ComponentTransform* ct)
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

		if (ImGui::Button("Reset"))
		{
			_position = float3::zero;
			_scale = float3::one;
			_rotationEulerAngles = float3::zero;
			updateTrans = true;
		}
		static ImGuizmo::OPERATION GizmoType(ImGuizmo::TRANSLATE);
		static ImGuizmo::MODE GizmoMode(ImGuizmo::LOCAL);

		if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
		{
			GizmoType = ImGuizmo::TRANSLATE;
			GizmoMode = ImGuizmo::LOCAL;
		}

		if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
		{
			GizmoType = ImGuizmo::ROTATE;
			GizmoMode = ImGuizmo::LOCAL;
		}

		if (App->input->GetKey(SDL_SCANCODE_Y) == KEY_DOWN)
		{
			GizmoType = ImGuizmo::SCALE;
			GizmoMode = ImGuizmo::LOCAL;

		}
		ImGuizmo::Enable(true);
		ImGuizmo::BeginFrame();

		ImGuiIO& io = ImGui::GetIO();
		ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);

		float* TransposedMatrix = ct->GetLocalTransform().Transposed().ptr();
		float* Position = ct->GetPosition().ptr();
		float* Rotation = ct->GetQuatRotation().ptr();
		float* Scale = ct->GetQuatRotation().ptr();
		ImGuizmo::Manipulate(App->scene->actualCamera->GetViewMatrix(), App->scene->actualCamera->GetProjectionMatrix(), GizmoType, GizmoMode, TransposedMatrix);
		if (ImGuizmo::IsUsing())
		{
			ImGuizmo::DecomposeMatrixToComponents(TransposedMatrix, Position, Rotation, Scale);

			//
			//						((TransformComponent*)(App->sceneMain->currentObject->components[0]))->updateTranslate();
			//						((TransformComponent*)(App->sceneMain->currentObject->components[0]))->updateScale();
			//						((utyTransformComponent*)(App->sceneMain->currentObject->components[0]))->updateRotate();
		}



		//ImGuizmo::DrawCube(App->scene->actualCamera->GetViewMatrix(), App->scene->actualCamera->GetProjectionMatrix(), _localTransMatrix);
		ImGui::TreePop();
	}

}