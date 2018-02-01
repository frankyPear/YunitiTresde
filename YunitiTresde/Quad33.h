#pragma once

#include "OpenGL.h"
#include "Glew\include\glew.h"

GLuint VBO, VAO;
GLfloat vertices[] =
{
	// Positions         // Colors
	1.5f, -1.5f, 0.0f,  // 1.0f, 0.0f, 0.0f,  // Bottom Right
	-1.5f, -1.5f, 0.0f,  // 0.0f, 1.0f, 0.0f,  // Bottom Left
	0.0f,  1.5f, 0.0f,   //0.0f, 0.0f, 1.0f   // Top
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
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(1);


	glBindVertexArray(0); // Unbind VAO
}