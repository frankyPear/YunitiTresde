#include "ComponentMesh.h"
using namespace std;

#pragma comment (lib, "Glew/libx86/glew32.lib")
#pragma comment (lib, "SDL/libx86/SDL2.lib")
#pragma comment (lib, "SDL/libx86/SDL2main.lib")
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")


ComponentMesh::ComponentMesh()
{

}

ComponentMesh::~ComponentMesh()
{

}

ComponentMesh::ComponentMesh(Shape shape) {
	switch (shape) {
		case SPHERE:
			sphere = new SolidSphere(1.0f,20.0f,20.0f);
			meshvertices = sphere->GetVertices();
			meshnormals = sphere->GetNormals();
			meshtexcoords = sphere->GetTexcoords();
			meshindices = sphere->GetIndices();
			meshcolors = sphere->GetColors();
			break;
		case CUBE:
			cube = new Cube();
			meshvertices = cube->GetVertices();
			meshnormals = cube->GetNormals();
			meshtexcoords = cube->GetTexcoords();
			meshindices = cube->GetIndices();
			meshcolors = cube->GetColors();
			break;
	}
	meshShape = shape;
}


bool ComponentMesh::PreUpdate()
{
	return true;
}

bool ComponentMesh::Update() 
{
	switch (meshShape) {
		case SPHERE:
			sphere->Draw(0.0f,0.0f,0.0f);
			break;
		case CUBE:
			cube->DrawElementQuad();
			break;
	}
	return true;
}

bool ComponentMesh::PostUpdate() 
{
	return true;
}

bool ComponentMesh::Destroy() 
{
	delete sphere;
	sphere = nullptr;
	return true;
}

Shape ComponentMesh::GetShape() const 
{
	return meshShape;
}

std::vector<GLfloat> ComponentMesh::GetMeshVertices() const
{
	return meshvertices;
}

std::vector<GLfloat> ComponentMesh::GetMeshNormals() const
{
	return meshnormals;
}

std::vector<GLfloat> ComponentMesh::GetMeshTexcoords() const
{
	return meshtexcoords;
}

std::vector<GLubyte> ComponentMesh::GetMeshIndices() const
{
	return meshindices;
}

std::vector<GLfloat> ComponentMesh::GetMeshColors() const
{
	return meshcolors;
}