#pragma once
#define _USE_MATH_DEFINES
#include "OpenGL.h"
#include <vector>
#include <cmath>

#define MY_PI_2 M_PI/2.0f

// your framework of choice here

class SolidSphere
{

public:

	SolidSphere();
	SolidSphere(float radius, unsigned int rings, unsigned int sectors);
	~SolidSphere();
	void Draw(GLfloat x, GLfloat y, GLfloat z);
	std::vector<GLfloat> GetVertices() const;
	std::vector<GLfloat> GetNormals() const;
	std::vector<GLfloat> GetTexcoords() const;
	std::vector<GLubyte> GetIndices() const;
	std::vector<GLfloat> GetColors() const;

public:
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> texcoords;
	std::vector<GLfloat> colors;
	std::vector<GLubyte> indices;
};



