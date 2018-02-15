#pragma once

#include "OpenGL.h"
#include <vector>

class Model
{
public:
	Model();
	~Model();
	
	// const aiscene* scene = 0;
	void Load(const char* filepath);
	void Clear();
	void Draw();

public:

	std::vector<GLfloat> meshvertices;
	std::vector<GLfloat> meshnormals;
	std::vector<GLfloat> meshtexcoords;
	std::vector<GLubyte> meshindices;
	std::vector<GLfloat> meshcolors;
};

