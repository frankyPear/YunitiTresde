#include "ModulePhysics.h"

ModulePhysics::ModulePhysics()
{
}

ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Init()
{
	return true;
}

bool ModulePhysics::Start()
{
	return true;
}

update_status ModulePhysics::PreUpdate(float dt)
{
	return update_status();
}

update_status ModulePhysics::Update(float dt)
{
	return update_status();
}

bool ModulePhysics::CleanUp()
{
	return false;
}
bool ModulePhysics::AddBody(float box_size) {
	float mass = 1.0f; // 0.0f would create a static or inmutable body
	//btCollisionShape* colShape = new btBoxShape(box_size); // regular box shapes.push_back(colShape);
	//btVector3 localInertia(0.f, 0.f, 0.f); if (mass != 0.f) colShape->calculateLocalInertia(mass, localInertia);
	//btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, component, colShape, localInertia);
	//btRigidBody* body = new btRigidBody(rbInfo); world->addRigidBody(body); return body;
	return true;
}