#include "Globals.h"
#include "MeshImporter.h"
//https://badvertex.com/2014/04/13/loading-meshes-using-assimp-in-opengl.html
#include "ResourceMesh.h"
/*
#include "Application.h"
#include "ComponentMesh.h"

#include "ModuleFileSystem.h"
*/

#include "Glew\include\glew.h"
//EVALUATE INCLUDES


#pragma comment (lib, "assimp/libraries/assimp-vc140-mt.lib")

MeshImporter::MeshImporter()
{
}

MeshImporter::~MeshImporter()
{
}

void MeshImporter::Load(const char* filePath, ResourceMesh* mesh)
{
	scene = importer.ReadFile(filePath,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);
	
	//amount of indices / vertices / colors 
	// normals / text_coords
	const char* buffer = filePath; // IMPROVE
	uint size;
	uint bytes = sizeof(mesh->vbo);
	//assimp/cimport.h includes memcpy
	memcpy(mesh->vbo, buffer, bytes); 

	//load indices
	buffer += bytes;
	bytes = sizeof(uint)* mesh->numIndices;
	mesh->indices = new uint[mesh->numIndices];
	memcpy(mesh->indices, buffer, bytes);

	glGenBuffers(1, (GLuint*) &mesh->vbo[INDEX_BUFFER]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->vbo[INDEX_BUFFER]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint)*mesh->numIndices,
		mesh->indices, GL_STATIC_DRAW);

	// Load vertices
	buffer += bytes;
	bytes = sizeof(float) * mesh->numVertices * 3;
	mesh->vertices = new float[mesh->numVertices * 3];
	memcpy(mesh->vertices, buffer, bytes);

	glGenBuffers(1, (GLuint*)&mesh->vbo[VERTEX_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo[VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh->numVertices * 3, mesh->vertices, GL_STATIC_DRAW);



	RELEASE_ARRAY(buffer);
}