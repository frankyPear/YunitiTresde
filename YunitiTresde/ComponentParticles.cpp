#include "ComponentParticles.h"
#include "GameObject.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleScene.h"
#include "ModuleCamera.h"
#include "ModuleTextures.h"
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

void ComponentParticles::Init(unsigned _max_particles, const aiVector2D & _emit_size, unsigned _falling_time, float _falling_height,  char * texture_file, const aiVector2D & psize)
{
	max_num_particles = _max_particles;
	falling_time = _falling_time;
	falling_height = _falling_height;
	emit_area = _emit_size;
	particle_size = psize;
	texture = App->textures->GetTexture(texture_file);
	particles_frame = _max_particles / _falling_time;
	ComponentTransform* t = (ComponentTransform*)linked_to->GetComponent(TRANSFORMATION);
	if (t != nullptr) {
		aiVector3D pos = aiVector3D(t->GetGlobalPosition().x, t->GetGlobalPosition().y, t->GetGlobalPosition().z);
		for (int i = 0; i < max_num_particles; ++i)
		{
			particle p;
			p.position = pos;
			p.velocity = aiVector3D(0.0f, falling_height / falling_time ,0.0f);
			p.lifeTime = falling_time;
			particles.push_back(p);
		}
	}
}

void ComponentParticles::Clear()
{
}

void ComponentParticles::Draw()
{
	particleList::iterator it;
	for (it = alive.begin(); it != alive.end(); ++it) {
		particles.at(*it);

	}
}



bool ComponentParticles::PreUpdate()
{
	return true;
}


void ComponentParticles::UpdateParticle(unsigned elapsed,  ComponentCamera & camera)
{

}

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



