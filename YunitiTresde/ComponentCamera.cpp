#include "ComponentCamera.h"
#include "OpenGL.h"
#include "GameObject.h"

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
	drawFrustumEnabled_ = true;
	frustrumCulling_ = false;
	type = CAMERA;
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
	// 0: (-,-,-) 1:(-,-,+) 2:(-,+,-) 3:(-,+,+)
	// 4: (+,-,-) 5:(+,-,+) 6:(+,+,-) 7:(+,+,+)

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

