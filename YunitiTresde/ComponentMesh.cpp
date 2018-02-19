#include "ComponentMesh.h"
#include "imgui-1.53\imgui.h"
#include "imgui-1.53\imgui_impl_sdl_gl3.h"
#include "GameObject.h"
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
			sphere = new SolidSphere(1.0f,15.0f,15.0f);
			meshvertices = sphere->GetVertices();
			meshnormals = sphere->GetNormals();
			meshtexcoords = sphere->GetTexcoords();
			meshindices = sphere->GetIndices();
			meshcolors = sphere->GetColors();
			meshBoundingBox = new AABB();
			meshBoundingBox->SetNegativeInfinity();
			(*meshBoundingBox).Enclose(sphere->GetSphereBB());
			break;
		case CUBE:
			cube = new Cube();
			meshvertices = cube->GetVertices();
			meshnormals = cube->GetNormals();
			meshtexcoords = cube->GetTexcoords();
			meshindices = cube->GetIndices();
			meshcolors = cube->GetColors();
			meshBoundingBox = new AABB();
			meshBoundingBox->SetNegativeInfinity();
			(*meshBoundingBox).Enclose(cube->GetCubeBB());
			break;
	}
	type = MESH;
	meshShape = shape;
}


bool ComponentMesh::PreUpdate()
{
	OnEditor();
	return true;
}

bool ComponentMesh::Update() 
{
	return true;
}

bool ComponentMesh::PostUpdate() 
{
	return true;
}

bool ComponentMesh::Destroy() 
{
	switch (meshShape) {
	case CUBE:
		delete cube;
		cube = nullptr;
		break;
	case SPHERE:
		delete sphere;
		sphere = nullptr;
		break;
	}
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

bool ComponentMesh::OnEditor() {
	if (ImGui::TreeNodeEx(meshShape == CUBE ? "CUBE Mesh":"SPHERE Mesh"))
	{
		if (cube != nullptr || sphere != nullptr)
		{
			ImGui::Text("Num Vertices: %i", GetMeshVertices().size());
			ImGui::Text("Num Indexes: %i", GetMeshIndices().size());
			ImGui::Text("Num Normals: %i",GetMeshNormals().size());
			ImGui::Text("Texture Coords: %i", GetMeshTexcoords().size());
		}
		else
		{
			ImGui::Text("Missing resource mesh!");
		}
		if (ImGui::Button("Delete Component"))
		{
			to_be_destroyed = true;
		}
		ImGui::TreePop();
	}
	return true;
}

AABB* ComponentMesh::GetBoundingBox() const {
	return meshBoundingBox;
}

bool ComponentMesh::CheckRayIntersectsMesh(Ray r, float &distance)
{
	// Iterate through vector, make TRIANGLE (class in mathgeolib), check each triangle with ray
	// (coordinates already transformed) return true if intersects and modify distance parameter with the distance.
	float actualDistance, minimalDistance;
	actualDistance = distance;
	minimalDistance = distance;
	bool found = false;
	for (int i = 0; i < meshindices.size(); i=i+3) {
		Triangle t = Triangle();
		t.a = float3 (meshvertices[meshindices[i] * 3], meshvertices[meshindices[i] * 3 + 1], meshvertices[meshindices[i] * 3 + 2]);
		t.b = float3 (meshvertices[meshindices[i+1] * 3], meshvertices[meshindices[i+1] * 3 + 1], meshvertices[meshindices[i+1] * 3 + 2]);
		t.c = float3 (meshvertices[meshindices[i+2] * 3], meshvertices[meshindices[i+2] * 3 + 1], meshvertices[meshindices[i+2] * 3 + 2]);
		float3 *point = nullptr;
		r.Intersects(t,&actualDistance,point);
		if (actualDistance < minimalDistance) {
			minimalDistance = actualDistance;
			found = true;
		}
	}
	if (found) return true;
	return false;
}
