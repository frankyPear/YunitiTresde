#pragma once

#include "OpenGL.h"
#include <vector>
#include <map>
#include "assimp\assimp\cimport.h"
#include "assimp\assimp\postprocess.h"
#include "assimp\assimp\scene.h"
#include "assimp\assimp\Importer.hpp"
#include "assimp\assimp\postprocess.h"
#include "Globals.h"

class Model
{
public:

	struct Weight
	{
		uint vertex = 0;
		float weight = 0.0f;
	};
	static enum BUFFERS {
		VERTEX_BUFFER, TEXCOORD_BUFFER, NORMAL_BUFFER, INDEX_BUFFER
	};

	struct Bone
	{
		const char* name;
		Weight* weights = nullptr;
		uint num_weights = 0;
		aiMatrix4x4 bind;
	};
	struct Texture
	{
		const char* name;
		static enum BUFFERS {
			VERTEX_BUFFER, TEXCOORD_BUFFER, NORMAL_BUFFER, INDEX_BUFFER
		};
		GLuint vao =0;
		GLuint vbo[4];
		GLuint element = 0;
	};

	Model();
	~Model();

	// const aiscene* scene = 0;
	void Load(const char* filepath);
	GLuint DevilImage(const char * theFileName);
	void LoadTexture(const char * filepath);
	void Clear();
	void Draw(uint id, aiMesh * mesh);
	uint loadTextureDirect(const char* filepath);
	void loadMeshData( aiMesh *mesh);
	void loadVaos(aiMesh* mesh);

public:

	const aiScene *scene;
	Assimp::Importer importer;
	std::vector<GLfloat> meshvertices;
	std::vector<GLfloat> meshnormals;
	std::vector<GLfloat> meshtexcoords;
	std::vector<GLubyte> meshindices;
	std::vector<GLubyte> meshmaterialsindices;
	std::vector<GLfloat> meshcolors;
	std::vector<Bone*> bones;
	std::vector<Texture*> textBind;
	GLuint numTextureBufferIds = 0;
	GLuint* textureBufferIds = nullptr;
	std::map<std::string, GLuint> textureIdMap;
};





