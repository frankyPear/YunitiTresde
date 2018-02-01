#pragma once

#include "OpenGL.h"
#include "Glew\include\glew.h"

GLuint VBO, VAO;
GLfloat vertices[] =
{
	1, 1, 1,    .0f,1.0f,1.0f,
	-1, 1, 1,   1.0f,1.0f,1.0f,
	-1,-1, 1,   1.0f,1.0f,1.0f,   // v0-v1-v2 (front)
	-1,-1, 1,   .0f,1.0f,1.0f,
	1,-1, 1,    1.0f,1.0f,1.0f,
	1, 1, 1,    1.0f,1.0f,1.0f,   // v2-v3-v0

	1, 1, 1,    .0f,1.0f,1.0f,
	1,-1, 1,    1.0f,1.0f,1.0f,
	1,-1,-1,    1.0f,1.0f,1.0f,   // v0-v3-v4 (right)
	1,-1,-1,    .0f,1.0f,1.0f,
	1, 1,-1,    1.0f,1.0f,1.0f,
	1, 1, 1,    1.0f,1.0f,1.0f,   // v4-v5-v0

	1, 1, 1,    .0f,1.0f,1.0f,
	1, 1,-1,    1.0f,1.0f,1.0f,
	-1, 1,-1,   1.0f,1.0f,1.0f,   // v0-v5-v6 (top)
	-1, 1,-1,   .0f,1.0f,1.0f,
	-1, 1, 1,   1.0f,1.0f,1.0f,
	1, 1, 1,    1.0f,1.0f,1.0f,  // v6-v1-v0

	-1, 1, 1,   .0f,1.0f,1.0f,
	-1, 1,-1,   1.0f,1.0f,1.0f,
	-1,-1,-1,   1.0f,1.0f,1.0f,   // v1-v6-v7 (left)
	-1,-1,-1,   .0f,1.0f,1.0f,
	-1,-1, 1,   1.0f,1.0f,1.0f,
	-1, 1, 1,   1.0f,1.0f,1.0f,  // v7-v2-v1

	-1,-1,-1,   .0f,1.0f,1.0f,
	1,-1,-1,    1.0f,1.0f,1.0f,
	1,-1, 1,    1.0f,1.0f,1.0f,   // v7-v4-v3 (bottom)
	1,-1, 1,    .0f,1.0f,1.0f,
	-1,-1, 1,   1.0f,1.0f,1.0f,
	-1,-1,-1,   1.0f,1.0f,1.0f,   // v3-v2-v7

	1,-1,-1,    1.0f,1.0f,1.0f,
	-1,-1,-1,   1.0f,1.0f,1.0f,
	-1, 1,-1,   .0f,1.0f,1.0f,  // v4-v7-v6 (back)
	-1, 1,-1,   1.0f,1.0f,1.0f,
	1, 1,-1,    1.0f,1.0f,1.0f,
	1,-1,-1,    .0f,1.0f,1.0f  // v6-v5-v4
};
void CreateTriangle()
{
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);


	glBindVertexArray(0); // Unbind VAO
}