#include "ComponentMesh.h"

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
			break;
		case CUBE:
			break;
	}
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
