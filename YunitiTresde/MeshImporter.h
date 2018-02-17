#ifndef _MESHIMPORTER_H_
#define _MESHIMPORTER_H_

#include "Importer.h"

static enum BUFFERS
{
	VERTEX_BUFFER,
	TEXCOORD_BUFFER,
	NORMAL_BUFFER,
	INDEX_BUFFER
};


class MeshImporter : public Importer
{



	MeshImporter();
	~MeshImporter();
};

#endif // !_MESHIMPORTER_H_

