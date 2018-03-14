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

	aiString path;

	//newMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &path);
	//GLuint iglId =ilutGLLoadImage((char*)filepath);
	for (unsigned int m = 0; m<scene->mNumMaterials; ++m)
	{
		int texIndex = 0;
		aiString path = (aiString)filepath;  // filename
											 //texFound = scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path
											 //	, &textmap, &uvInd, &blend, &op, mode);
		aiReturn texFound = scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
		while (texFound == AI_SUCCESS) {
			//GLuint iglId = ilutGLLoadImage((char*)filepath);
			textureIdMap[path.data] = 0;
			texIndex++;
			texFound = scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
		}
	}
	int numTextures = textureIdMap.size();

	ILuint* imageIds = new ILuint[numTextures];
	ilGenImages(numTextures, imageIds);

	GLuint* textureIds = new GLuint[numTextures];
	glGenTextures(numTextures, textureIds);

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
			LOG("PROBLEMS WITH THE IMAGE");
		}
	}

	ilDeleteImages(numTextures, imageIds);
	ilBindImage(0);
	//Cleanup
	delete[] imageIds;
	delete[] textureIds;

}

void Model::loadBones( aiMesh *mesh)
{
	for (int i = 0; i < mesh->mNumBones; ++i)
	{
		Bone *bone = new Bone();
		aiBone *aibone = mesh->mBones[i];
		bone->name = aibone->mName.C_Str();
		bone->bind = aibone->mOffsetMatrix;
		bone->num_weights = aibone->mNumWeights;
		Weight* newweights = new Weight[aibone->mNumWeights];
		for (int j = 0; j < aibone->mNumWeights; ++j)
		{
			newweights[j].vertex = aibone->mWeights[j].mVertexId;
			newweights[j].weight = aibone->mWeights[j].mWeight;
		}
		bone->weights = newweights;
	}
	
}


uint Model::loadTextureDirect(const char* filepath)
{
	uint id = -1;
	ilInit();
	iluInit();
	ilutInit();


	id = ilutGLLoadImage((char*)filepath);

	return id;
}

void Model::Clear()
{

}


void Model::Draw(uint id, aiMesh* mesh) // vector de textures + vector de meshes
{
	if (mesh != nullptr)
	{
		for (unsigned i = 0; i < mesh->mNumFaces; ++i)
		{
			glBindTexture(GL_TEXTURE_2D, id);

			glBegin(GL_TRIANGLES);
			for (unsigned j = 0; j < mesh->mFaces[i].mNumIndices; ++j)
			{
				int index = mesh->mFaces[i].mIndices[j];

				if (mesh->HasTextureCoords(0))
				{
					glTexCoord2f(mesh->mTextureCoords[0][index].x, mesh->mTextureCoords[0][index].y);
				}
				glVertex3fv(&mesh->mVertices[index].x);
			}
			glEnd();
			glBindTexture(GL_TEXTURE_2D, 0);

		}
	}
}