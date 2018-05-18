#include "Model.h"
#include "DevIL\include\IL\il.h"
#include "DevIL\include\IL\ilu.h"
#include "DevIL\include\IL\ilut.h"


#pragma comment (lib, "assimp/libraries/assimp-vc140-mt.lib")
#pragma comment (lib, "DevIL/lib/x86/Release/DevIL.lib")
#pragma comment (lib, "DevIL/lib/x86/Release/ILU.lib")
#pragma comment (lib, "DevIL/lib/x86/Release/ILUT.lib")

using namespace std;

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
	//ilInit();
	//iluInit();
	//ilutInit();

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

void Model::loadMeshData( aiMesh *mesh)
{	
	for (int x = 0; x < mesh->mNumVertices; ++x)
	{
		aiVector3D vert = mesh->mVertices[x];

		meshvertices.push_back(float3(vert.x,vert.y,vert.z));
		if (mesh->HasNormals()) meshnormals.push_back(float3(mesh->mNormals[x].x, mesh->mNormals[x].y, mesh->mNormals[x].z));
		if (mesh->HasTextureCoords(x)) 
		{
			for (int z = 0; z < 8; ++z) {
				for (int w = 0; w < 3; ++w) meshtexcoords.push_back(mesh->mTextureCoords[x][z][w]);
			}
		}
	}
	if (mesh->HasFaces()) {
		for (int l = 0; l < mesh->mNumFaces; ++l)
		{
			aiFace face = mesh->mFaces[l];
			for (int m = 0; m < face.mNumIndices; ++m) meshindices.push_back(face.mIndices[m]);
		}
	}
	if (mesh->mMaterialIndex > -1) 
	{

	}
	if (mesh->HasBones())
	{
		for (int i = 0; i < mesh->mNumBones; ++i)
		{
			Bone *bone = new Bone();
			aiBone *aibone = mesh->mBones[i];
			bone->name = aibone->mName.C_Str();
			bone->num_weights = aibone->mNumWeights;
			bone->bind = float4x4(); 
			for (int x = 0; x < 4; ++x) 
			{
				for (int y = 0; y < 4; ++y) bone->bind[x][y] = aibone->mOffsetMatrix[x][y];
			}
			Weight* newweight = new Weight();
			for (int j = 0; j < aibone->mNumWeights; ++j)
			{
				newweight[j].vertex = aibone->mWeights[j].mVertexId;
				newweight[j].weight = aibone->mWeights[j].mWeight;
			}
			bone->weights.push_back(newweight);
			bones.push_back(bone);
		}
	}
}

void Model::loadVaos(aiMesh * mesh)
{
	/*Texture *text = new Texture();
	text->vbo[VERTEX_BUFFER] = NULL;
	text->vbo[TEXCOORD_BUFFER] = NULL;
	text->vbo[NORMAL_BUFFER] = NULL;
	text->vbo[INDEX_BUFFER] = NULL;
	glGenVertexArrays(1, &text->vao);
	glBindVertexArray(text->vao);
	text->element = mesh->mNumFaces * 3;
	glBindVertexArray(text->vao);
	glDrawElements(GL_TRIANGLES, text->element, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
	textBind.push_back(text);*/
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

//	for each vertex in vertex vector:
//		for each bone associated:
//			get bone_weight
//			get bone_matrix_in_bind (inverse but the pilot model already gives it inverted)
//			get the gameobject's transform from transform component

void Model::Draw(uint id, aiMesh* mesh, float4x4 obj_transform) // vector de textures + vector de meshes
{
	if (mesh != nullptr)
	{
		vector<float3>newvertices(meshvertices.size(), float3(0.0f,0.0f,0.0f));
		vector<float3>newnormals(meshnormals.size(), float3(0.0f, 0.0f, 0.0f));

		for (int x = 0; x < bones.size(); ++x)
		{
			for (int y = 0; y < bones[x]->weights.size(); ++y)
			{
				Weight w = *bones[x]->weights[y];
				float4x4 transform_bind = bones[x]->bind;
				// add gameobject as a parameter to get the transform matrix and invert it.
				float4 calculatedPos = w.weight *(obj_transform * transform_bind*float4(meshvertices[w.vertex].x, meshvertices[w.vertex].y, meshvertices[w.vertex].z, 1.0f));
				newvertices[w.vertex] +=  float3(calculatedPos.x,calculatedPos.y, calculatedPos.z);

				float4x4 normalTrans = float4x4(obj_transform.Col(0), obj_transform.Col(1), obj_transform.Col(2), float4(0.0f, 0.0f, 0.0f, 1.0f));
				float4x4 normalBind = float4x4(transform_bind.Col(0), transform_bind.Col(1), transform_bind.Col(2), float4(0.0f, 0.0f, 0.0f, 1.0f));
				float4 finalNorm = w.weight*(normalTrans*normalBind*float4(meshnormals[x].x, meshnormals[x].y, meshnormals[x].z, 1.0f));
				newnormals[w.vertex] += float3(finalNorm.x, finalNorm.y, finalNorm.z);
			}
		}
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

/*
if (mesh != nullptr && mesh->bones.size() > 0)
{
	std::fill(mesh->verticesVBO.begin(), mesh->verticesVBO.end(), float3(0.f,0.f,0.f));
	for (vector<Bone>::iterator it = mesh->bones.begin(); it != mesh->bones.end(); ++it)
	{
		for (vector<Weight>::iterator itW = (it)->weights.begin(); itW != (it)->weights.end(); ++itW)
		{
			float4x4 transform = anim->joints.find((it)->name)->second->idBone;
			float4 finalPos = (itW)->weight * (transform * (*it)->bind * float4(mesh->originalVertices[(itW)->vertex], 1.f));
			mesh->verticesVBO[(itW)->vertex] += float3(finalPos.x,finalPos.y,finalPos.z);

			float4x4 transformNorm = float4x4(transform.Col(0), transform.Col(1), transform.Col(2), float4(0.f, 0.f, 0.f, 1.f));
			float4x4 bindNorm = float4x4((it)->bind.Col(0), (it)->bind.Col(1), (it)->bind.Col(2), float4(0.f, 0.f, 0.f, 1.f));
			float4 finalNorm = (itW)->weight * (transformNorm * bindNorm * float4(mesh->originalNormals[(itW)->vertex], 1.f));
			mesh->normalsVBO[(itW)->vertex] += float3(finalNorm.x, finalNorm.y, finalNorm.z);
		}
	}
	for (unsigned int i = 0; i < mesh->normalsVBO.size(); ++i)
	{
		mesh->normalsVBO[i].Normalize();
	}
	mesh->updateVerticesBuffer();
	//At the end, update buffer of vertices on gpu
}
*/