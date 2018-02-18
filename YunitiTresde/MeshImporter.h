#ifndef _MESHIMPORTER_H_
#define _MESHIMPORTER_H_

#include "Importer.h"

#include "assimp\assimp\cimport.h"
#include "assimp\assimp\postprocess.h"
#include "assimp\assimp\scene.h"
#include "assimp\assimp\Importer.hpp"
#include "assimp\assimp\postprocess.h"


class MeshImporter : public Importer
{
  	MeshImporter();
	~MeshImporter();

	void Load(const char* filePath, ResourceMesh* mesh);

public:
	const aiScene *scene;
	Assimp::Importer importer;
};

#endif // !_MESHIMPORTER_H_

