#pragma once
#define _USE_MATH_DEFINES
#include "OpenGL.h"
#include <vector>
#include <cmath>

#define M_PI_2 M_PI/2.0f

// your framework of choice here

class SolidSphere
{

public:

	SolidSphere();
	SolidSphere(float radius, unsigned int rings, unsigned int sectors);
	~SolidSphere();
	void Draw(GLfloat x, GLfloat y, GLfloat z);

public:
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> texcoords;
	std::vector<GLushort> indices;
};



