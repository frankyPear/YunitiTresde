#pragma once
#include "Component.h"
#include "SolidSphere.h"
#include "Quad.h"
#include "OpenGL.h"
#include <vector>
#include "Mathgeolib\include\Geometry\AABB.h"

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
	bool OnEditor();

	Shape GetShape() const;
	//Why not to put void?
	std::vector<GLfloat> GetMeshVertices() const;
	std::vector<GLfloat> GetMeshNormals() const;
	std::vector<GLfloat> GetMeshTexcoords() const;
	std::vector<GLubyte> GetMeshIndices() const;
	std::vector<GLfloat> GetMeshColors() const;
	AABB* GetBoundingBox() const;
	bool CheckRayIntersectsMesh(Ray r, float& distance);

public:
	Shape meshShape;
	Cube *cube = nullptr;
	SolidSphere *sphere = nullptr;
	AABB* meshBoundingBox = nullptr;

	std::vector<GLfloat> meshvertices;
	std::vector<GLfloat> meshnormals;
	std::vector<GLfloat> meshtexcoords;
	std::vector<GLubyte> meshindices;
	std::vector<GLfloat> meshcolors;
};

