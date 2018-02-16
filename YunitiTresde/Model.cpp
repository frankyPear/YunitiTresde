#include "Model.h"


#pragma comment (lib, "assimp/libraries/assimp-vc140-mt.lib")


Model::Model()
{
}


Model::~Model()
{
}

void Model::Load(const char* filepath)
{
	scene = importer.ReadFile(filepath,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);
	if (!scene)
	{
		LOG("ERROR LOADING SCENE");
	}
	else {
		LOG("SCENE LOADED");
	}
}

void Model::Clear()
{

}

void Model::Draw()
{
	if (scene != nullptr)
	{
		const int iVertexTotalSize = sizeof(aiVector3D) * 2 + sizeof(aiVector2D);
		int iTotalVertices = 0;
		for (int i = 0; i < scene->mNumMeshes; ++i)
		{
			aiMesh* mesh = scene->mMeshes[i];
			int iMeshFaces = mesh->mNumFaces;
			meshmaterialsindices.push_back(mesh->mMaterialIndex);
			glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 1.0f, 1.0f);
			for (int j = 0; j < iMeshFaces; ++j)
			{
				const aiFace& face = mesh->mFaces[j];
				for (int k = 0; k < 3; ++k) {
					GLfloat x = mesh->mVertices[face.mIndices[k]].x;
					GLfloat y = mesh->mVertices[face.mIndices[k]].y;
					GLfloat z = mesh->mVertices[face.mIndices[k]].z;
					glVertex3f(x, y, z);
				}
			}
			glEnd();
		}
	}
}