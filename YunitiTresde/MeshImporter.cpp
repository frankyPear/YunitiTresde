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
#include "DevIL\include\IL\il.h"
#include "DevIL\include\IL\ilu.h"
#include "DevIL\include\IL\ilut.h"
#include "Application.h"
//EVALUATE INCLUDES
#pragma comment (lib, "assimp/libraries/assimp-vc140-mt.lib")
#pragma comment (lib, "DevIL/lib/x86/Release/DevIL.lib")
#pragma comment (lib, "DevIL/lib/x86/Release/ILU.lib")
#pragma comment (lib, "DevIL/lib/x86/Release/ILUT.lib")

MeshImporter::MeshEntry::MeshEntry(aiMesh* mesh, aiMaterial* material)
{
	vbo[VERTEX_BUFFER] = NULL;
	vbo[TEXCOORD_BUFFER] = NULL;
	vbo[NORMAL_BUFFER] = NULL;
	vbo[INDEX_BUFFER] = NULL;

	glGenVertexArrays(1, (GLuint*)&vao);
	glBindVertexArray(vao);

	elementCount = mesh->mNumFaces * 3;

	if (mesh->HasPositions())
	{

		glVertexPointer(0, GL_FLOAT,0, mesh->mVertices);
	}


	if (mesh->HasTextureCoords(0))
	{
		glTexCoordPointer(3,GL_FLOAT, 3 * sizeof(mesh->mVertices), mesh->mVertices);
	}



	 id = ilutGLLoadImage("../Resources/Baker_house.png");

	
}


MeshImporter::MeshEntry::~MeshEntry()
{
	if (vbo[VERTEX_BUFFER]) {
		glDeleteBuffers(1, &vbo[VERTEX_BUFFER]);
	}

	if (vbo[TEXCOORD_BUFFER]) {
		glDeleteBuffers(1, &vbo[TEXCOORD_BUFFER]);
	}

	if (vbo[NORMAL_BUFFER]) {
		glDeleteBuffers(1, &vbo[NORMAL_BUFFER]);
	}

	if (vbo[INDEX_BUFFER]) {
		glDeleteBuffers(1, &vbo[INDEX_BUFFER]);
	}

	glDeleteVertexArrays(1, &vao);
}

void MeshImporter::MeshEntry::Draw() 
{
	
	glBindTexture(GL_TEXTURE_2D, id);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

MeshImporter::MeshImporter(const char *filePath)
{

	ilInit();
	iluInit();
	ilutInit();

	Assimp::Importer importer;
	 //empty
	const aiScene *scene = importer.ReadFile(filePath, NULL);
	if (!scene) {
		printf("Unable to laod mesh: %s\n", importer.GetErrorString());
	}

	for (int i = 0; i < scene->mNumMaterials; i++)
	{
		materials.push_back(scene->mMaterials[i]);
	}
	for (int i = 0; i < scene->mNumMeshes; ++i)
	{
		meshEntries.push_back(new MeshImporter::MeshEntry(scene->mMeshes[i],materials[scene->mMeshes[i]->mMaterialIndex]));
	}
	

}

MeshImporter::~MeshImporter()
{
	for (int i = 0; i < meshEntries.size(); ++i) {
		delete meshEntries.at(i);
	}
	meshEntries.clear();
}

void MeshImporter::Draw() {
	for (int i = 0; i < meshEntries.size(); ++i) {
		meshEntries.at(i)->Draw();
	}
}




/*
if (material->GetTexture(aiTextureType_DIFFUSE, 0, path) == AI_SUCCESS)
{
ILstring filename = (ILstring)path;
int numTextures = 1;
ILboolean success;
GLuint* textureIds = new GLuint[numTextures];
ilGenImages(numTextures, &mesh->mMaterialIndex);
glGenTextures(1, &(ILuint)mesh->mMaterialIndex);
glBindTexture(GL_TEXTURE_2D, (ILuint)mesh->mMaterialIndex);
ilBindImage(mesh->mMaterialIndex);
ilEnable(IL_ORIGIN_SET);
ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
success = ilLoadImage(filename);//(ILstring)filename.c_str());

if (success)
{
ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
glBindTexture(GL_TEXTURE_2D, *textureIds);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ilGetInteger(IL_IMAGE_WIDTH),
ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGBA, GL_UNSIGNED_BYTE,
ilGetData());
}
else
{
LOG("PROBLEMS WITH THE IMAGE");
}
ilDeleteImages(numTextures, &mesh->mMaterialIndex);
ilBindImage(0);
delete[] textureIds;
}



*/