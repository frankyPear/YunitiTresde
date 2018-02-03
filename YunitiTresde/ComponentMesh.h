#pragma once
#include "Component.h"
#include "SolidSphere.h"
#include "Quad.h"
#include "OpenGL.h"

enum Shape {CUBE,SPHERE};

class ComponentMesh :
	public Component
{
public:
	ComponentMesh();
	ComponentMesh(Shape shape);
	~ComponentMesh();

	bool PreUpdate();
	bool Update();
	bool PostUpdate();
	bool Destroy();

	Shape GetShape() const;

private:
	Shape meshShape;
	Cube *cube = nullptr;
	SolidSphere *sphere = nullptr;
};

