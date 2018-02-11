#include "ModuleCamera.h"
#include "Application.h"
#include "ModuleInput.h"
#include "Glew\include\glew.h"
#include "Mathgeolib\include\Math\MathAll.h"


ModuleCamera::ModuleCamera()
{
	dummyCamera = new ComponentCamera();
	dummyCamera->SetPlaneDistances(0.5f, 100.0f);
}

ModuleCamera::~ModuleCamera()
{
	RELEASE(dummyCamera);
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

void ModuleCamera::Look(const float3 & position)
{
	//dummyCamera->
}

void ModuleCamera::Orbit(float motionX, float motionY)
{
	float3 point = _lookingAt;

	// fake point should be a ray colliding with something
	if (!_isLooking)
	{
		LineSegment picking = dummyCamera->frustum_.UnProjectLineSegment(0.f, 0.f);
		float distance;
		//GameObject* hit = App->level->CastRay(picking, distance);

		//if (hit != nullptr)
		//	point = picking.GetPoint(distance);
		//else
		//	point = dummyCamera->frustum_.pos + dummyCamera->frustum_.front * 50.0f;

		_isLooking = true;
		_lookingAt = point;
	}

	float3 focus = dummyCamera->frustum_.pos - point;

	Quat qy(dummyCamera->frustum_.up, motionX);
	Quat qx(dummyCamera->frustum_.WorldRight(), motionY);

	focus = qx.Transform(focus);
	focus = qy.Transform(focus);

	dummyCamera->frustum_.pos = focus + point;

	Look(point);
}

void ModuleCamera::Zoom(float zoom)
{
	if (_isLooking) {

		float dist = _lookingAt.Distance(dummyCamera->frustum_.pos);

		// Slower on closer distances
		if (dist < 15.0f)
			zoom *= 0.5f;
		if (dist < 7.5f)
			zoom *= 0.25f;
		if (dist < 1.0f && zoom > 0)
			zoom = 0;

	}
	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		zoom *= 5.0f;

	float3 p = dummyCamera->frustum_.front * zoom;
	dummyCamera->frustum_.pos += p;

}

void ModuleCamera::LookAt(float motionX, float motionY)
{

	_isLooking = false;
	if (motionX != 0.f)
	{
		Quat q = Quat::RotateY(motionX);
		dummyCamera->frustum_.front = q.Mul(dummyCamera->frustum_.front).Normalized();
		// would not need this is we were rotating in the local Y, but that is too disorienting
		dummyCamera->frustum_.up = q.Mul(dummyCamera->frustum_.up).Normalized();
	}

	if (motionY != 0.f)
	{
		Quat q = Quat::RotateAxisAngle(dummyCamera->frustum_.WorldRight(), motionY);

		float3 new_up = q.Mul(dummyCamera->frustum_.up).Normalized();

		if (new_up.y > 0.0f)
		{
			dummyCamera->frustum_.up = new_up;
			dummyCamera->frustum_.front = q.Mul(dummyCamera->frustum_.front).Normalized();
		}
	}
}

void ModuleCamera::CenterOn(const float3 & position, float distance)
{
	float3 v = dummyCamera->frustum_.front.Neg();
	dummyCamera->frustum_.pos = position + (v * distance);
	_lookingAt = position;
	_isLooking = true;
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
		quatOffset = quatOffset.Mul(Quat::RotateY(camSpeed_));
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		quatOffset = quatOffset.Mul(Quat::RotateY(-camSpeed_));
	}

	const iPoint &mouseMotion = App->input->GetMouseMotion();
	float dx = (float)-mouseMotion.x * _rotationSpeed * dt;
	float dy = (float)-mouseMotion.y * _rotationSpeed * dt;
	if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_REPEAT && (mouseMotion.x != 0 || mouseMotion.y != 0)) {

		LookAt(dx, dy);

	}





	int mouseWheel = App->input->GetMouseWheel();

	if (mouseWheel != 0)
		Zoom(mouseWheel*_zoomSpeed*dt);


	dummyCamera->SetUp(quatOffset.Mul(dummyCamera->GetUp()));
	dummyCamera->NormalizeUp();
	dummyCamera->SetFront(quatOffset.Mul(dummyCamera->GetFront()));
	dummyCamera->NormalizeFront();
	return UPDATE_CONTINUE;
}

