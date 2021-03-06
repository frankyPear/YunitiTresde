#include "ComponentCamera.h"
#include "OpenGL.h"
#include "GameObject.h"
#include "Brofiler\include\Brofiler.h"
#include "imgui-1.53\imgui.h"
#include "imgui-1.53\imgui_impl_sdl_gl3.h"

ComponentCamera::ComponentCamera()
{
	frustum_ = Frustum();
	frustum_.type = PerspectiveFrustum;
	aspectRatio_ = 16.0f / 9.0f;
	frustum_.pos = float3(0.0f, 1.0f, 0.0f);
	frustum_.front = (float3(0.0f, 0.0f, -1.0f));
	frustum_.up = float3(0.0f, 1.0f, 0.0f);
	frustum_.nearPlaneDistance = 0.5f;
	frustum_.farPlaneDistance = 30.0f;
	frustum_.verticalFov = DegToRad(60.0f);
	frustum_.horizontalFov = DegToRad(80.0f);
	drawFrustumEnabled_ = false;
	frustrumCulling_ = false;
	type = CAMERA;
	component_id = App->rng->GetRandomNumber();
}


ComponentCamera::~ComponentCamera()
{
}

bool ComponentCamera::PreUpdate()
{
	return true;
}

bool ComponentCamera::Update()
{
	BROFILER_CATEGORY("ModuleCamera Update", Profiler::Color::Azure);
	ComponentTransform *ct = (ComponentTransform *) linked_to->GetComponent(TRANSFORMATION);
	if (ct != nullptr) {
		frustum_.SetWorldMatrix(ct->GetGlobalTransform().Float3x4Part());
	}
	if (drawFrustumEnabled_) DrawFrustum();
	return true;
}

bool ComponentCamera::PostUpdate()
{
	return true;
}

bool ComponentCamera::Destroy()
{
	return true;
}

bool ComponentCamera::OnEditor()
{
	float verticalFOV = RadToDeg(frustum_.verticalFov);
	float nearDist = frustum_.nearPlaneDistance;
	float farDist = frustum_.farPlaneDistance;
	if (ImGui::TreeNodeEx("Component Camera"))
	{
		ImGui::Text("FOV:");
		if (ImGui::DragFloat("Vertical", &verticalFOV, 0.05f, 30, 120, "%.2f"))
		{
			SetFOV(verticalFOV);
			SetAspectRatio();
		}
		ImGui::Separator();

		ImGui::Text("Near distance:");
		if (ImGui::DragFloat("ZNear", &nearDist, 0.05f, 0.1f, 5.0f, "%.2f"))
		{
			SetPlaneDistances(nearDist,farDist);
		}
		ImGui::Separator();

		ImGui::Text("Far distance: ");
		if (ImGui::DragFloat("ZFar", &farDist, 0.05f, 10, 1500, "%.2f"))
		{
			SetPlaneDistances(nearDist, farDist);
		}
		ImGui::Separator();

		if (ImGui::Checkbox("Draw frustum", &drawFrustumEnabled_));
		if (ImGui::Button("Delete Component"))
		{
			to_be_destroyed = true;
		}
		ImGui::TreePop();
	}
	return true;
}

void ComponentCamera::SetFOV(float degrees)
{
	frustum_.verticalFov = DegToRad(degrees);
	frustum_.horizontalFov = 2.0f * atanf((tanf(frustum_.verticalFov / 2.0f)) * (aspectRatio_));
}

void ComponentCamera::SetAspectRatio()
{
	aspectRatio_ = frustum_.horizontalFov / frustum_.verticalFov;
}

void ComponentCamera::SetPlaneDistances(float zNear, float zFar)
{
	frustum_.nearPlaneDistance = zNear;
	frustum_.farPlaneDistance = zFar;
}

void ComponentCamera::SetPosition(float3 newPos)
{
	frustum_.pos = newPos;
}

float* ComponentCamera::GetProjectionMatrix()
{
	return frustum_.ProjectionMatrix().ptr();
}

float* ComponentCamera::GetViewMatrix()
{
	return  ((float4x4)frustum_.ViewMatrix()).Transposed().ptr();

}

Frustum* ComponentCamera::GetFrustum() {
	return &frustum_;
}

float3 ComponentCamera::GetPosition() const
{
	return frustum_.pos;
}

float3 ComponentCamera::GetFront() const
{
	return frustum_.front;
}

float3 ComponentCamera::GetWorldRight() const
{
	return frustum_.WorldRight();
}

float3  ComponentCamera::GetUp() const
{
	return frustum_.up;
}

float ComponentCamera::GetFOV() const
{
	return RadToDeg(frustum_.verticalFov);
}


void ComponentCamera::SetFront(float3 newFront)
{
	frustum_.front = newFront;
}

void ComponentCamera::SetUp(float3 newUp)
{
	frustum_.up = newUp;
}


void ComponentCamera::NormalizeUp()
{
	frustum_.up.Normalize();
}

void ComponentCamera::NormalizeFront()
{
	frustum_.front.Normalize();
}

void ComponentCamera::DrawFrustum()
{


	float3 CornerVertex[8];
	frustum_.GetCornerPoints(CornerVertex);
	//glPushMatrix();
	glLineWidth((GLfloat)3.0f);
	glColor3f(0.0f,1.0f,0.0f);
	/*
						11
	(3)---------------------------------------(7)
	|   \                                  /  |
	|      \                            /     |
	|       7 \                      / 6      |
	|            \        3      /            |
	|             (2)----------(6)            |
	|              |            |             |10
12	|            4 |            |2            |
	|              |            |             |
	|             (0)-----------(4)           |
	|            /        1        \          |
	|       8 /                      \ 5      |
	|     /                            \      |
	|  /                                  \   |
	(1)--------------------------------------(5)
						9
	  */
	glBegin(GL_LINES);
		//1		
		glVertex3fv((GLfloat*)&CornerVertex[0]);
		glVertex3fv((GLfloat*)&CornerVertex[4]);
		//2	
		glVertex3fv((GLfloat*)&CornerVertex[4]);
		glVertex3fv((GLfloat*)&CornerVertex[6]);
		//3		
		glVertex3fv((GLfloat*)&CornerVertex[2]);
		glVertex3fv((GLfloat*)&CornerVertex[6]);
		//4		
		glVertex3fv((GLfloat*)&CornerVertex[0]);
		glVertex3fv((GLfloat*)&CornerVertex[2]);
		//5		
		glVertex3fv((GLfloat*)&CornerVertex[4]);
		glVertex3fv((GLfloat*)&CornerVertex[5]);
		//6		
		glVertex3fv((GLfloat*)&CornerVertex[6]);
		glVertex3fv((GLfloat*)&CornerVertex[7]);
		//7		
		glVertex3fv((GLfloat*)&CornerVertex[2]);
		glVertex3fv((GLfloat*)&CornerVertex[3]);
		//8		
		glVertex3fv((GLfloat*)&CornerVertex[0]);
		glVertex3fv((GLfloat*)&CornerVertex[1]);
		//9		
		glVertex3fv((GLfloat*)&CornerVertex[1]);
		glVertex3fv((GLfloat*)&CornerVertex[5]);
		//10		
		glVertex3fv((GLfloat*)&CornerVertex[5]);
		glVertex3fv((GLfloat*)&CornerVertex[7]);
		//11		
		glVertex3fv((GLfloat*)&CornerVertex[7]);
		glVertex3fv((GLfloat*)&CornerVertex[3]);
		//12		
		glVertex3fv((GLfloat*)&CornerVertex[1]);
		glVertex3fv((GLfloat*)&CornerVertex[3]);

	glEnd();
	//glPopMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth((GLfloat)1.0f);

}

