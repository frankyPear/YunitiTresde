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
GLuint Model::DevilImage(const char* theFileName)
{
	ILuint imageID;							
	GLuint textureID;						
	ILboolean success;						
	ILenum error;							

	ilGenImages(1, &imageID); 				
	ilBindImage(imageID); 					
	success = ilLoadImage(theFileName); 	

											
	if (!success)
	{
		ilBindImage(0);
		error = ilGetError();
		return 0;
	}
	ILinfo ImageInfo;
	iluGetImageInfo(&ImageInfo);
	if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
	{
		iluFlipImage();
	}
	success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);

	if (!success)
	{
		error = ilGetError();
		ilDeleteImages(1, &imageID);
		ilBindImage(0);
		return 0;
	}

	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_3D, textureID);

	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	
	glTexImage2D(GL_TEXTURE_2D,			
		0,								
		ilGetInteger(IL_IMAGE_BPP),		
		ilGetInteger(IL_IMAGE_WIDTH),	
		ilGetInteger(IL_IMAGE_HEIGHT),	
		0,								
		ilGetInteger(IL_IMAGE_FORMAT),	
		GL_UNSIGNED_BYTE,				
		ilGetData()						
	);

	glBindTexture(GL_TEXTURE_3D, GL_NONE);

	ilDeleteImages(1, &imageID);
	ilBindImage(0);

	return textureID;	
}
void Model::LoadTexture(const char* filepath)
{
	ILboolean success;
	//char* filesp = "../Resources/BakerHouse.fbx";
	/* initialization of DevIL */
	ilInit();
	iluInit();
	ilutInit();
	int rootPathSize = strrchr(filepath, '/') - filepath + 1;
	numTextureBufferIds = scene->mNumMaterials;
	textureBufferIds = new unsigned int[numTextureBufferIds];
	for (unsigned int m = 0; m < scene->mNumMaterials; ++m)
	{
		aiString aiPath;
		scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, 0, &aiPath);
		char* fullPath = new char[rootPathSize + aiPath.length + 1];
		memcpy_s(fullPath, rootPathSize + aiPath.length + 1, filepath, rootPathSize);
		memcpy_s(fullPath + rootPathSize, aiPath.length + 1, aiPath.data, aiPath.length);
		fullPath[rootPathSize + aiPath.length] = '\0';
		textureIdMap[aiPath.data] = 0;
		textureBufferIds[m] = DevilImage(fullPath);
		delete[] fullPath;
	}


	GLuint iglId =ilutGLLoadImage((char*)filepath);

	//ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	//
	//glBindTexture(GL_TEXTURE_3D, textureBufferIds[0]);//(GLuint)textureBufferIds[i]);// textureIds[i]);
	//glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexImage2D(GL_TEXTURE_3D, 0, GL_RGBA, ilGetInteger(IL_IMAGE_WIDTH),
	//	ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());

	//int numTextures = textureIdMap.size();
	//
	//ILuint* imageIds = new ILuint[numTextures];
	//ilGenImages(numTextures, imageIds);
	//
	//GLuint* textureIds = new GLuint[numTextures];
	//glGenTextures(numTextures, textureIds); 
	
	//std::map<std::string, GLuint>::iterator itr = textureIdMap.begin();
	//int i = 0;
	//for (; itr != textureIdMap.end(); ++i, ++itr)
	//{
	////save IL image ID
	//	std::string filename = (*itr).first;  
	//	(*itr).second = textureIds[i];    
	//
	//	ilBindImage(imageIds[i]); 
	//	ilEnable(IL_ORIGIN_SET);
	//	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	//	success = ilLoadImage(filepath);//(ILstring)filename.c_str());
	//
	//	if (success) {
	//
	//		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	//
	//		glBindTexture(GL_TEXTURE_2D, iglId);//(GLuint)textureBufferIds[i]);// textureIds[i]);
	//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ilGetInteger(IL_IMAGE_WIDTH),
	//			ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGBA, GL_UNSIGNED_BYTE,
	//			ilGetData());
	//	}
	//	else
	//	{
	//		LOG("ERROR LOADING TEXTURE");
	//	}
	//}
	//
	//ilDeleteImages(numTextures, imageIds);
	
	//Cleanup
	//delete[] imageIds;
	//delete[] textureIds;

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