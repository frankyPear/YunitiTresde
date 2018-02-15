#include "ComponentTransform.h"
#include "GameObject.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleScene.h"
#include "ModuleCamera.h"
#include "imgui-1.53\imgui.h"
#include "imgui-1.53\imgui_impl_sdl_gl3.h"
#include "imgui-1.53\ImGuizmo.h"
#include "imgui-1.53\ImSequencer.h"
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
static const char* SequencerItemTypeNames[] = { "Camera","Music", "ScreenEffect", "FadeIn", "Animation" };
struct MySequence : public ImSequencer::SequenceInterface
{
	// interface with sequencer

	virtual int GetFrameCount() const { return mFrameCount; }
	virtual int GetItemCount() const { return (int)myItems.size(); }

	virtual int GetItemTypeCount() const { return sizeof(SequencerItemTypeNames) / sizeof(char*); }
	virtual const char *GetItemTypeName(int typeIndex) const { return SequencerItemTypeNames[typeIndex]; }
	virtual const char *GetItemLabel(int index) const
	{
		static char tmps[512];
		sprintf_s(tmps, "[%02d] %s", index, SequencerItemTypeNames[myItems[index].mType]);
		return tmps;
	}

	virtual void Get(int index, int** start, int** end, int *type, unsigned int *color)
	{
		MySequenceItem &item = myItems[index];
		if (color)
			*color = 0xFFAA8080; // same color for everyone, return color based on type
		if (start)
			*start = &item.mFrameStart;
		if (end)
			*end = &item.mFrameEnd;
		if (type)
			*type = item.mType;
	}
	virtual void Add(int type) { myItems.push_back(MySequenceItem{ type, 0, 10 }); };
	virtual void Del(int index) { myItems.erase(myItems.begin() + index); }
	virtual void Duplicate(int index) { myItems.push_back(myItems[index]); }

	// my datas
	MySequence() : mFrameCount(0) {}
	int mFrameCount;
	struct MySequenceItem
	{
		int mType;
		int mFrameStart, mFrameEnd;
	};
	std::vector<MySequenceItem> myItems;
};
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
		float* TransposedMatrix = ct->GetLocalTransform().Transposed().ptr();
		float* Position = ct->GetPosition().ptr();
		float* Rotation = ct->GetQuatRotation().ptr();
		float* Scale = ct->GetQuatRotation().ptr();

		EditTransform(TransposedMatrix, Position, Rotation, Scale);

		
		ImGui::TreePop();
	}

}
void ComponentTransform::EditTransform(float * TransposedMatrix, float * Position, float * Rotation, float * Scale)
{

	ImGuizmo::BeginFrame();

	// debug
	ImGuizmo::DrawCube(App->scene->actualCamera->GetViewMatrix(), App->scene->actualCamera->GetProjectionMatrix(), TransposedMatrix);
	static ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::ROTATE);
	static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::WORLD);
	static bool useSnap = false;
	static float snap[3] = { 1.f, 1.f, 1.f };

	if (ImGui::IsKeyPressed(90) || App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_T) == KEY_REPEAT)
		mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
	if (ImGui::IsKeyPressed(69) || App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_R) == KEY_REPEAT)
		mCurrentGizmoOperation = ImGuizmo::ROTATE;
	if (ImGui::IsKeyPressed(82) || App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) // r Key
		mCurrentGizmoOperation = ImGuizmo::SCALE;
	if (ImGui::RadioButton("Translate", mCurrentGizmoOperation == ImGuizmo::TRANSLATE))
		mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
	ImGui::SameLine();
	if (ImGui::RadioButton("Rotate", mCurrentGizmoOperation == ImGuizmo::ROTATE))
		mCurrentGizmoOperation = ImGuizmo::ROTATE;
	ImGui::SameLine();
	if (ImGui::RadioButton("Scale", mCurrentGizmoOperation == ImGuizmo::SCALE))
		mCurrentGizmoOperation = ImGuizmo::SCALE;
	float matrixTranslation[3], matrixRotation[3], matrixScale[3];
	ImGuizmo::DecomposeMatrixToComponents(TransposedMatrix, matrixTranslation, matrixRotation, matrixScale);
	ImGui::InputFloat3("Tr", matrixTranslation, 3);
	ImGui::InputFloat3("Rt", matrixRotation, 3);
	ImGui::InputFloat3("Sc", matrixScale, 3);
	ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, TransposedMatrix);

	if (mCurrentGizmoOperation != ImGuizmo::SCALE)
	{
		if (ImGui::RadioButton("Local", mCurrentGizmoMode == ImGuizmo::LOCAL))
			mCurrentGizmoMode = ImGuizmo::LOCAL;
		ImGui::SameLine();
		if (ImGui::RadioButton("World", mCurrentGizmoMode == ImGuizmo::WORLD))
			mCurrentGizmoMode = ImGuizmo::WORLD;
	}
	if (ImGui::IsKeyPressed(83))
		useSnap = !useSnap;
	ImGui::Checkbox("", &useSnap);
	ImGui::SameLine();

	switch (mCurrentGizmoOperation)
	{
	case ImGuizmo::TRANSLATE:
		ImGui::InputFloat3("Snap", &snap[0]);
		break;
	case ImGuizmo::ROTATE:
		ImGui::InputFloat("Angle Snap", &snap[0]);
		break;
	case ImGuizmo::SCALE:
		ImGui::InputFloat("Scale Snap", &snap[0]);
		break;
	}
	ImGuiIO& io = ImGui::GetIO();
	ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
	ImGuizmo::Manipulate(App->scene->actualCamera->GetViewMatrix(), App->scene->actualCamera->GetProjectionMatrix(), mCurrentGizmoOperation, mCurrentGizmoMode, TransposedMatrix, NULL, useSnap ? &snap[0] : NULL);

	// let's create the sequencer
//	static int selectedEntry = -1;
//	static int firstFrame = 0;
//	static bool expanded = true;
//	ImGui::SetNextWindowPos(ImVec2(10, 260));
//	ImGui::SetNextWindowSize(ImVec2(740, 380));
//	ImGui::Begin("Sequencer");
//	ImGui::InputInt("Frame count", &mySequence.mFrameCount);
	//Sequencer(&mySequence, NULL, &expanded, &selectedEntry, &firstFrame, ImSequencer::SEQUENCER_EDIT_STARTEND | ImSequencer::SEQUENCER_ADD | ImSequencer::SEQUENCER_DEL | ImSequencer::SEQUENCER_COPYPASTE);
	// add a UI to edit that particular item
//	if (selectedEntry != -1)
//	{
//		MySequence::MySequenceItem &item = mySequence.myItems[selectedEntry];
//		ImGui::Text("I am a %s, please edit me", SequencerItemTypeNames[item.mType]);
//		// switch (type) ....
//	}
//	ImGui::End();

	// render everything
//	glClearColor(0.45f, 0.4f, 0.4f, 1.f);
//	glClear(GL_COLOR_BUFFER_BIT);
//	ImGui::Render();
}

