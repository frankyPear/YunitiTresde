#include "Model.h"
#include "DevIL\include\IL\il.h"
#include "DevIL\include\IL\ilu.h"
#include "DevIL\include\IL\ilut.h"

#pragma comment (lib, "assimp/libraries/assimp-vc140-mt.lib")
#pragma comment (lib, "DevIL/lib/x86/Release/DevIL.lib")
#pragma comment (lib, "DevIL/lib/x86/Release/ILU.lib")
#pragma comment (lib, "DevIL/lib/x86/Release/ILUT.lib")

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

void Model::LoadTexture(const char* filepath)
{

	ILboolean success;
	//char* filesp = "../Resources/BakerHouse.fbx";
	/* initialization of DevIL */
	ilInit();
	iluInit();
	ilutInit();
	//GLuint iglId =ilutGLLoadImage((char*)filepath);
	for (unsigned int m = 0; m<scene->mNumMaterials; ++m)
	{
		int texIndex = 0;
		aiString path = (aiString)filepath;  // filename
		//texFound = scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path
		//	, &textmap, &uvInd, &blend, &op, mode);
		aiReturn texFound = scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
		while (texFound == AI_SUCCESS) {
			GLuint iglId = ilutGLLoadImage((char*)filepath);
			textureIdMap[path.data] = 0;
			texIndex++;
			texFound = scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
		}
	}
	int numTextures = textureIdMap.size();
	
	ILuint* imageIds = new ILuint[numTextures];
	ilGenImages(numTextures, imageIds);

	GLuint* textureIds = new GLuint[numTextures];
	glGenTextures(numTextures, textureIds); /* Texture name generation */
	
	std::map<std::string, GLuint>::iterator itr = textureIdMap.begin();
	int i = 0;
	for (; itr != textureIdMap.end(); ++i, ++itr)
	{
	//save IL image ID
		std::string filename = (*itr).first;  
		(*itr).second = textureIds[i];    
	
		ilBindImage(imageIds[i]); 
		ilEnable(IL_ORIGIN_SET);
		ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
		success = ilLoadImage(filepath);//(ILstring)filename.c_str());
	
		if (success) {

			ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	
			glBindTexture(GL_TEXTURE_2D, textureIds[i]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ilGetInteger(IL_IMAGE_WIDTH),
				ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGBA, GL_UNSIGNED_BYTE,
				ilGetData());
		}
		else
		{
			printf("Problems to load an Image: %s\n", filename.c_str());
		}
	}

	ilDeleteImages(numTextures, imageIds);
	
	//Cleanup
	delete[] imageIds;
	delete[] textureIds;

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