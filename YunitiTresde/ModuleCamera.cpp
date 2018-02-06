#include "ModuleCamera.h"

#include "Application.h"
#include "ModuleInput.h"
#include "Glew\include\glew.h"
#include "Mathgeolib\include\Math\MathAll.h"


ModuleCamera::ModuleCamera()
{
	dummyCamera = new ComponentCamera();

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
update_status ModuleCamera::PreUpdate(float dt)
{
	
	return UPDATE_CONTINUE;
}

update_status ModuleCamera::Update(float dt)
{
	Quat quatOffset = Quat::identity;
	camSpeed_ = 3.0f*dt;

	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN) dummyCamera->SetPosition(dummyCamera->GetPosition().Add(float3(0.0f, camSpeed_, 0.0f)));

	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN) dummyCamera->SetPosition(dummyCamera->GetPosition().Add(float3(0.0f, -camSpeed_, 0.0f)));
	
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN) dummyCamera->SetPosition(dummyCamera->GetPosition() + dummyCamera->GetFront().Add(float3(0.0f, 0.0f, camSpeed_)));

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN) dummyCamera->SetPosition(dummyCamera->GetPosition() - dummyCamera->GetFront().Add(float3(0.0f, 0.0f, camSpeed_)));
	
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN) dummyCamera->SetPosition(dummyCamera->GetPosition() - dummyCamera->GetWorldRight().Add(float3(camSpeed_, 0.0f, 0.0f)));
	
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN) dummyCamera->SetPosition(dummyCamera->GetPosition() + dummyCamera->GetWorldRight().Add(float3(camSpeed_, 0.0f, 0.0f)));
	
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) 
	{
		quatOffset = quatOffset.Mul(Quat::RotateAxisAngle(dummyCamera->GetWorldRight(), camSpeed_));
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) 
	{
		quatOffset = quatOffset.Mul(Quat::RotateAxisAngle(dummyCamera->GetWorldRight(), -camSpeed_));
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		quatOffset = quatOffset.Mul(Quat::RotateY(-camSpeed_));
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		quatOffset = quatOffset.Mul(Quat::RotateY(camSpeed_));
	}
	frustum_.up = quatOffset.Mul(frustum_.up);
	frustum_.up.Normalize();
	frustum_.front = quatOffset.Mul(frustum_.front);
	frustum_.front.Normalize();
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
	frustum_.horizontalFov = 2.0f * atanf((tanf(frustum_.verticalFov / 2.0f)) * (aspectRatio_));
}

void ModuleCamera::SetAspectRatio()
{
	aspectRatio_ = frustum_.horizontalFov / frustum_.verticalFov;
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