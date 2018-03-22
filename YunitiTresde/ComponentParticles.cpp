#include "ComponentParticles.h"
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
#include "ModuleFX.h"


ComponentParticles::ComponentParticles()
{
}

ComponentParticles::~ComponentParticles()
{
}

void ComponentParticles::Init(unsigned max_particles, const aiVector2D & _emit_size, unsigned _falling_time, float falling_height, const char * texture_file, const aiVector2D & psize)
{
}

void ComponentParticles::Clear()
{
}

void ComponentParticles::Draw()
{
}



bool ComponentParticles::PreUpdate()
{
	return true;
}

bool ComponentParticles::Update(GameObject* obj)
{

	return true;
}

//void ComponentParticles::UpdateParticle(unsigned elapsed, const ComponentCamera & camera)
//{
//}

bool ComponentParticles::PostUpdate()
{
	return true;
}

bool ComponentParticles::Destroy()
{
	return true;
}

bool ComponentParticles::DisplayImgUINode()
{
	return true;
}

void ComponentParticles::OnEditor(GameObject * obj)
{
}



