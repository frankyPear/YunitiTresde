#ifndef _QUAD_
#define _QUAD_

#include "OpenGL.h"
#include "ModuleTextures.h"
#include <vector>
#include "Math.h"

void DrawElementPlane();


class Cube
{

public:

	Cube();
	~Cube();
	void DrawImmediateQuad();
	void DrawArrayQuad();
	void DrawElementQuad();
	void InitCube();
	void DrawElementQuadTexturized(GLuint textureID);
	AABB& GetCubeBB();
	float* GetQuadVertex();

	std::vector<GLfloat>  GetVertices();
	std::vector<GLfloat>  GetNormals();
	std::vector<GLfloat>  GetColors();
	std::vector<GLfloat>  GetTexcoords();
	std::vector<GLubyte>  GetIndices();


public:
	GLuint indexID;
	GLuint vertexID;
	GLuint normalID;
	GLuint colorID;
	GLuint texID;

	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> colors;
	std::vector<GLfloat> texcoords;
	std::vector<GLubyte> indicesVector;

	AABB cubeBoundingBox;

	GLfloat vertices1[108] =
	{
		1, 1, 1,  -1, 1, 1,  -1,-1, 1,      // v0-v1-v2 (front)
		-1,-1, 1,   1,-1, 1,   1, 1, 1,      // v2-v3-v0

		1, 1, 1,   1,-1, 1,   1,-1,-1,      // v0-v3-v4 (right)
		1,-1,-1,   1, 1,-1,   1, 1, 1,      // v4-v5-v0

		1, 1, 1,   1, 1,-1,  -1, 1,-1,      // v0-v5-v6 (top)
		-1, 1,-1,  -1, 1, 1,   1, 1, 1,      // v6-v1-v0

		-1, 1, 1,  -1, 1,-1,  -1,-1,-1,      // v1-v6-v7 (left)
		-1,-1,-1,  -1,-1, 1,  -1, 1, 1,      // v7-v2-v1

		-1,-1,-1,   1,-1,-1,   1,-1, 1,      // v7-v4-v3 (bottom)
		1,-1, 1,  -1,-1, 1,  -1,-1,-1,      // v3-v2-v7

		1,-1,-1,  -1,-1,-1,  -1, 1,-1,      // v4-v7-v6 (back)
		-1, 1,-1,   1, 1,-1,   1,-1,-1        // v6-v5-v4
	};

	// normal array
	GLfloat normals1[108] =
	{
		0, 0, 1,   0, 0, 1,   0, 0, 1,      // v0-v1-v2 (front)
		0, 0, 1,   0, 0, 1,   0, 0, 1,      // v2-v3-v0

		1, 0, 0,   1, 0, 0,   1, 0, 0,      // v0-v3-v4 (right)
		1, 0, 0,   1, 0, 0,   1, 0, 0,      // v4-v5-v0

		0, 1, 0,   0, 1, 0,   0, 1, 0,      // v0-v5-v6 (top)
		0, 1, 0,   0, 1, 0,   0, 1, 0,      // v6-v1-v0

		-1, 0, 0,  -1, 0, 0,  -1, 0, 0,      // v1-v6-v7 (left)
		-1, 0, 0,  -1, 0, 0,  -1, 0, 0,      // v7-v2-v1

		0,-1, 0,   0,-1, 0,   0,-1, 0,      // v7-v4-v3 (bottom)
		0,-1, 0,   0,-1, 0,   0,-1, 0,      // v3-v2-v7

		0, 0,-1,   0, 0,-1,   0, 0,-1,      // v4-v7-v6 (back)
		0, 0,-1,   0, 0,-1,   0, 0,-1     // v6-v5-v4
	};

	// color array
	GLfloat colors1[108] =
	{
		1, 1, 1,   1, 1, 0,   1, 0, 0,      // v0-v1-v2 (front)
		1, 0, 0,   1, 0, 1,   1, 1, 1,      // v2-v3-v0

		1, 1, 1,   1, 0, 1,   0, 0, 1,      // v0-v3-v4 (right)
		0, 0, 1,   0, 1, 1,   1, 1, 1,      // v4-v5-v0

		1, 1, 1,   0, 1, 1,   0, 1, 0,      // v0-v5-v6 (top)
		0, 1, 0,   1, 1, 0,   1, 1, 1,      // v6-v1-v0

		1, 1, 0,   0, 1, 0,   0, 0, 0,      // v1-v6-v7 (left)
		0, 0, 0,   1, 0, 0,   1, 1, 0,      // v7-v2-v1

		0, 0, 0,   0, 0, 1,   1, 0, 1,      // v7-v4-v3 (bottom)
		1, 0, 1,   1, 0, 0,   0, 0, 0,      // v3-v2-v7

		0, 0, 1,   0, 0, 0,   0, 1, 0,      // v4-v7-v6 (back)
		0, 1, 0,   0, 1, 1,   0, 0, 1
	};    // v6-v5-v4

	float vertices2[72] = {
		1, 1, 1,  -1, 1, 1,  -1,-1, 1,   1,-1, 1,   // v0,v1,v2,v3 (front)
		1, 1, 1,   1,-1, 1,   1,-1,-1,   1, 1,-1,   // v0,v3,v4,v5 (right)
		1, 1, 1,   1, 1,-1,  -1, 1,-1,  -1, 1, 1,   // v0,v5,v6,v1 (top)
		-1, 1, 1,  -1, 1,-1,  -1,-1,-1,  -1,-1, 1,   // v1,v6,v7,v2 (left)
		-1,-1,-1,   1,-1,-1,   1,-1, 1,  -1,-1, 1,   // v7,v4,v3,v2 (bottom)
		1,-1,-1,  -1,-1,-1,  -1, 1,-1,   1, 1,-1 }; // v4,v7,v6,v5 (back)

													// normal array
	GLfloat normals2[72] = {
		0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1,   // v0,v1,v2,v3 (front)
		1, 0, 0,   1, 0, 0,   1, 0, 0,   1, 0, 0,   // v0,v3,v4,v5 (right)
		0, 1, 0,   0, 1, 0,   0, 1, 0,   0, 1, 0,   // v0,v5,v6,v1 (top)
		-1, 0, 0,  -1, 0, 0,  -1, 0, 0,  -1, 0, 0,   // v1,v6,v7,v2 (left)
		0,-1, 0,   0,-1, 0,   0,-1, 0,   0,-1, 0,   // v7,v4,v3,v2 (bottom)
		0, 0,-1,   0, 0,-1,   0, 0,-1,   0, 0,-1 }; // v4,v7,v6,v5 (back)

													// color array
	GLfloat colors2[72] = {
		1, 1, 1,   1, 1, 0,   1, 0, 0,   1, 0, 1,   // v0,v1,v2,v3 (front)
		1, 1, 1,   1, 0, 1,   0, 0, 1,   0, 1, 1,   // v0,v3,v4,v5 (right)
		1, 1, 1,   0, 1, 1,   0, 1, 0,   1, 1, 0,   // v0,v5,v6,v1 (top)
		1, 1, 0,   0, 1, 0,   0, 0, 0,   1, 0, 0,   // v1,v6,v7,v2 (left)
		0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,   // v7,v4,v3,v2 (bottom)
		0, 0, 1,   0, 0, 0,   0, 1, 0,   0, 1, 1 }; // v4,v7,v6,v5 (back)

													// index array of vertex array for glDrawElements() & glDrawRangeElement()
	GLubyte indices[36] = {
		0, 1, 2,   2, 3, 0,      // front
		4, 5, 6,   6, 7, 4,      // right
		8, 9,10,  10,11, 8,      // top
		12,13,14,  14,15,12,      // left
		16,17,18,  18,19,16,      // bottom
		20,21,22,  22,23,20 };    // back

	GLfloat texCoords[48] = {
		1,1,    0,1,    0,0,    1,0,    // front
		0,1,    0,0,    1,0,    1,1,    // right
		1,0,    1,1,    0,1,    0,0,    // top
		1,1,    0,1,    0,0,    1,0,    // left
		0,1,    1,1,    1,0,    0,0,    // bottom
		1,0,    0,0,    0,1,    1,1        // back
	};

	GLshort texIndex[36] = {
		3,1,0,   0,2,3,
		1,0,2,     2,3,0,
		2,3,1,   1,0,2,
		3,1,0,   0,2,3,
		1,3,2,   2,0,1,
		0,2,3,   3,1,0
	};



};

#endif // !_QUAD_