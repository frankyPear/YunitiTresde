#include "ModuleCamera.h"
#include "Application.h"
#include "ModuleInput.h"

#include "Glew\include\glew.h"
#include "Mathgeolib\include\Math\MathAll.h"


ModuleCamera::ModuleCamera()
{
	frustum_ = Frustum();	
	/*
	type, projectiveSpace, handedness, pos, front, up,
	nearPlaneDistance, farPlaneDistance, horizontalFov/orthographicWidth
	and verticalFov/orthographicHeight are all NaN.
	*/
	frustum_.type = PerspectiveFrustum;
	aspectRatio = 16.0f / 9.0f;
	frustum_.pos = float3(0.0f,1.0f,0.0f);
	frustum_.front = (float3(0.0f, 0.0f, -1.0f));
	frustum_.up = float3(0.0f, 1.0f, 0.0f);
	frustum_.nearPlaneDistance = 0.5f;
	frustum_.farPlaneDistance = 1000.0f;
	frustum_.verticalFov = DegToRad(60.0f);
	frustum_.horizontalFov = DegToRad(36.0f);
		//2.0f * atanf((tanf(frustum_.verticalFov / 2.0f)) * (aspectRatio)); //frustum_.verticalFov * (aspectRatio);
	camSpeed = 0.05f;
}

ModuleCamera::~ModuleCamera()
{

}

bool ModuleCamera::Init()
{
	bool ret = true;

	return ret;
}

bool ModuleCamera::CleanUp()
{
	bool ret = true;


	return ret;
}
update_status ModuleCamera::PreUpdate()
{

	return UPDATE_CONTINUE;
}

update_status ModuleCamera::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN) frustum_.pos = frustum_.pos.Add(float3(0.0f,camSpeed,0.0f));

	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN) frustum_.pos = frustum_.pos.Add(float3(0.0f, -camSpeed, 0.0f));
	
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN) frustum_.front = frustum_.front.Add(float3(0.0f, 0.0f,camSpeed));

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN) frustum_.front = frustum_.front.Add(float3(0.0f, 0.0f ,-camSpeed));
	
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN) frustum_.pos = frustum_.pos.Add(float3(-camSpeed, 0.0f, 0.0f));
	
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN) frustum_.pos = frustum_.pos.Add(float3(camSpeed, 0.0f, 0.0f));
	
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) 
	{
		Quat q = Quat::RotateAxisAngle(frustum_.WorldRight(), camSpeed);
		frustum_.Transform(q);
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) 
	{
		Quat q = Quat::RotateAxisAngle(frustum_.WorldRight(), -camSpeed);
		frustum_.Transform(q);
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		Quat q = Quat::RotateAxisAngle(float3(0.0f, 1.0f, 0.0f), -camSpeed);
		frustum_.Transform(q);
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		Quat q = Quat::RotateAxisAngle(float3(0.0f, 1.0f, 0.0f), camSpeed);
		frustum_.Transform(q);
	}

	return UPDATE_CONTINUE;
}

float* ModuleCamera::GetProjectionMatrix()
{
	return frustum_.ProjectionMatrix().Transposed().ptr();
}

float* ModuleCamera::GetViewMatrix()
{
	return  ((float4x4)frustum_.ViewMatrix()).Transposed().ptr();
}

void ModuleCamera::SetFOV(float degrees)
{
	frustum_.verticalFov = DegToRad(degrees);
	frustum_.horizontalFov = 2.0f * atanf((tanf(frustum_.verticalFov / 2.0f)) * (aspectRatio));
}

void ModuleCamera::SetAspectRatio()
{
	aspectRatio = frustum_.horizontalFov / frustum_.verticalFov;
}

void ModuleCamera::SetPlaneDistances(float zNear, float zFar)
{
	frustum_.nearPlaneDistance = zNear;
	frustum_.farPlaneDistance = zFar;
}

void ModuleCamera::SetPosition(float3 newPos)
{
	frustum_.pos = newPos;
}