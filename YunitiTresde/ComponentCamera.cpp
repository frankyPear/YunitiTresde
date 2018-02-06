#include "ComponentCamera.h"



ComponentCamera::ComponentCamera()
{
	frustum_ = Frustum();
	frustum_.type = PerspectiveFrustum;
	aspectRatio_ = 16.0f / 9.0f;
	frustum_.pos = float3(0.0f, 1.0f, 0.0f);
	frustum_.front = (float3(0.0f, 0.0f, -1.0f));
	frustum_.up = float3(0.0f, 1.0f, 0.0f);
	frustum_.nearPlaneDistance = 0.5f;
	frustum_.farPlaneDistance = 1000.0f;
	frustum_.verticalFov = DegToRad(60.0f);
	frustum_.horizontalFov = DegToRad(36.0f);
}


ComponentCamera::~ComponentCamera()
{
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