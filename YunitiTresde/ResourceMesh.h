/*
NOT IN USE, IN FUTURE USE INSTEAD OF aiMesh*
*/

#ifndef _RESOURCEMESH_H_
#define _RESOURCEMESH_H_


#include "Globals.h"
#include "Resource.h"


class ResourceMesh : public Resource
{
public:

	ResourceMesh(uid uid, Type type);
	~ResourceMesh();

public:
	
	uint vao; //vertex array object
	uint vbo[4]; //vertex buffer object

	uint numVertices = 0;
	float* vertices = nullptr;

	uint numIndices = 0;
	uint* indices = nullptr;

};
#endif // !_RESOURCEMESH_H_

