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
		GLuint id;

		unsigned int elementCount;

		MeshEntry(aiMesh* mesh, aiMaterial* material);
		~MeshEntry();
		
		void Load(aiMesh *mesh);
		void Draw();
	};

	std::vector<MeshEntry*> meshEntries;
	std::vector<aiMaterial*> materials;

public:
  	MeshImporter(const char* filePath);
	~MeshImporter();

	void Draw();
};

#endif // !_MESHIMPORTER_H_


