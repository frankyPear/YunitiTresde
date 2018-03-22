#pragma once
#include "Component.h"
#include "ComponentCamera.h"

#include "Mathgeolib\include\MathGeoLib.h"
#include "assimp\assimp\cimport.h"
#include "assimp\assimp\postprocess.h"
#include "assimp\assimp\scene.h"
#include "assimp\assimp\Importer.hpp"
#include "ModuleFX.h"
#include "Billboard.h"

class ComponentParticles :
	public Component
{
public:
	struct particle
	{
		aiVector3D position;
		aiVector3D velocity;
		unsigned int lifeTime;
	};
	///Constructor
	ComponentParticles();

	~ComponentParticles();

	void Init(unsigned max_particles, const aiVector2D& _emit_size, unsigned _falling_time,
		float falling_height,  char* texture_file, const aiVector2D& psize);

	void Clear();

	void Draw();

	bool PreUpdate();


	void UpdateParticle(unsigned elapsed, ComponentCamera& camera);

	bool PostUpdate();
	
	bool Destroy();

	bool DisplayImgUINode();

	void OnEditor(GameObject* obj);

public:
	typedef std::vector<Billboard::billboard> BillboardList;
	typedef std::vector<particle> particlePool;
	typedef std::vector<unsigned> particleList;

	particlePool particles;
	particleList alive;
	particleList dead;
	BillboardList billboards;

	aiVector2D emit_area;
	aiVector2D particle_size;
	unsigned max_num_particles = 0;
	unsigned falling_time = 0;
	unsigned accum_elapsed = 0;
	float falling_height = 0.0f;
	unsigned texture = 0;
	uint particles_frame = 0;

	aiVector3D* vertices = nullptr;
	aiVector2D* text_coords = nullptr;
	aiColor4D* colors = nullptr;
	unsigned* indices;


#pragma region Getters

#pragma endregion


#pragma region Setters


#pragma endregion

private:


};

