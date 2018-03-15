#ifndef _MESHIMPORTER_H_
#define _MESHIMPORTER_H_


#include "Importer.h"
#include "OpenGL.h"

#include "assimp\assimp\cimport.h"
#include "assimp\assimp\postprocess.h"
#include "assimp\assimp\scene.h"
#include "assimp\assimp\Importer.hpp"
#include "assimp\assimp\postprocess.h"

#include <vector>


class MeshImporter : public Importer
{
public:
	struct MeshEntry {
		static enum BUFFERS {
			VERTEX_BUFFER, TEXCOORD_BUFFER, NORMAL_BUFFER, INDEX_BUFFER
		};
		GLuint vao;
		GLuint vbo[4];

		unsigned int elementCount;

		MeshEntry(aiMesh* mesh);
		~MeshEntry();

		void Load(aiMesh *mesh);
		void Draw();
	};
	struct Weight
	{
		uint vertex = 0;
		float weight = 0.0f;
	};

	struct Bone
	{
		const char* name;
		Weight* weights = nullptr;
		uint num_weights = 0;
		aiMatrix4x4 bind;
	};

	std::vector<MeshEntry*> meshEntries;
	std::vector<Bone*> bones;
public:
  	MeshImporter(const char* filePath);
	~MeshImporter();

	void Draw();
	//SceneGraph - Release 25/02
	void meshEntryArrays(aiMesh * mesh);
	void DrawMeshHierarchy();
};

#endif // !_MESHIMPORTER_H_


