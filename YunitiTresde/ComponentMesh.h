#pragma once
#include "Component.h"
#include "OpenGL.h"
#include "SDL\include\SDL.h"
#include "Sphere.h"


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
	SolidSphere *sphere = nullptr;
};

