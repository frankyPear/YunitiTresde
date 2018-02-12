#include "Quad.h"

Cube::Cube()
{
}

Cube::~Cube()
{
}

void Cube::DrawImmediateQuad()
{
	glPushMatrix();
	//draw stuff

	glBegin(GL_TRIANGLES);
	// front faces
	glNormal3f(0, 0, 1);
	// face v0-v1-v2
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);
	glColor3f(1, 1, 0);
	glVertex3f(-1, 1, 1);
	glColor3f(1, 0, 0);
	glVertex3f(-1, -1, 1);
	// face v2-v3-v0
	glColor3f(1, 0, 0);
	glVertex3f(-1, -1, 1);
	glColor3f(1, 0, 1);
	glVertex3f(1, -1, 1);
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);

	// right faces
	glNormal3f(1, 0, 0);
	// face v0-v3-v4
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);
	glColor3f(1, 0, 1);
	glVertex3f(1, -1, 1);
	glColor3f(0, 0, 1);
	glVertex3f(1, -1, -1);
	// face v4-v5-v0
	glColor3f(0, 0, 1);
	glVertex3f(1, -1, -1);
	glColor3f(0, 1, 1);
	glVertex3f(1, 1, -1);
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);

	// top faces
	glNormal3f(0, 1, 0);
	// face v0-v5-v6
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);
	glColor3f(0, 1, 1);
	glVertex3f(1, 1, -1);
	glColor3f(0, 1, 0);
	glVertex3f(-1, 1, -1);
	// face v6-v1-v0
	glColor3f(0, 1, 0);
	glVertex3f(-1, 1, -1);
	glColor3f(1, 1, 0);
	glVertex3f(-1, 1, 1);
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);

	// left faces
	glNormal3f(-1, 0, 0);
	// face  v1-v6-v7
	glColor3f(1, 1, 0);
	glVertex3f(-1, 1, 1);
	glColor3f(0, 1, 0);
	glVertex3f(-1, 1, -1);
	glColor3f(0, 0, 0);
	glVertex3f(-1, -1, -1);
	// face v7-v2-v1
	glColor3f(0, 0, 0);
	glVertex3f(-1, -1, -1);
	glColor3f(1, 0, 0);
	glVertex3f(-1, -1, 1);
	glColor3f(1, 1, 0);
	glVertex3f(-1, 1, 1);

	// bottom faces
	glNormal3f(0, -1, 0);
	// face v7-v4-v3
	glColor3f(0, 0, 0);
	glVertex3f(-1, -1, -1);
	glColor3f(0, 0, 1);
	glVertex3f(1, -1, -1);
	glColor3f(1, 0, 1);
	glVertex3f(1, -1, 1);
	// face v3-v2-v7
	glColor3f(1, 0, 1);
	glVertex3f(1, -1, 1);
	glColor3f(1, 0, 0);
	glVertex3f(-1, -1, 1);
	glColor3f(0, 0, 0);
	glVertex3f(-1, -1, -1);

	// back faces
	glNormal3f(0, 0, -1);
	// face v4-v7-v6
	glColor3f(0, 0, 1);
	glVertex3f(1, -1, -1);
	glColor3f(0, 0, 0);
	glVertex3f(-1, -1, -1);
	glColor3f(0, 1, 0);
	glVertex3f(-1, 1, -1);
	// face v6-v5-v4
	glColor3f(0, 1, 0);
	glVertex3f(-1, 1, -1);
	glColor3f(0, 1, 1);
	glVertex3f(1, 1, -1);
	glColor3f(0, 0, 1);
	glVertex3f(1, -1, -1);
	glPopMatrix();
	glEnd();
}


void Cube::DrawArrayQuad()
{
	// enble and specify pointers to vertex arrays
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normals1);
	glColorPointer(3, GL_FLOAT, 0, colors1);
	glVertexPointer(3, GL_FLOAT, 0, vertices1);
	glRotatef(0.75f, 1, 1, 0);

	glPushMatrix();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void Cube::DrawElementQuad()
{
	// enable and specify pointers to vertex arrays
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normals2);
	glColorPointer(3, GL_FLOAT, 0, colors2);
	glVertexPointer(3, GL_FLOAT, 0, vertices2);
	//glRotatef(0.75f, 1, 1, 0);
	glPushMatrix();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);
	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void Cube::InitCube() {

	glGenBuffers(1, &vertexID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	glGenBuffers(1, &texID);
	glBindBuffer(GL_ARRAY_BUFFER, texID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
}

void Cube::DrawElementQuadTexturized(GLuint textureID)
{
	// enable and specify pointers to vertex arrays

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, vertexID);
	glVertexPointer(3, GL_FLOAT, 0, vertices2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glEnable(GL_TEXTURE_2D);
	glBindBuffer(GL_ARRAY_BUFFER, texID);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glPushMatrix();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);
	glPopMatrix();

	glDisableClientState(GL_TEXTURE_2D_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void DrawElementPlane()
{
	float size =100.0f;
	float step = 1.5f; // Space between squares
	

	glBegin(GL_LINES);

	glColor3f(1.5f, 1.5f, 1.5f);
	for (float i = step; i <= size; i += step)
	{
		//Parallel lines to Z
		glVertex3f(i, 0, -size);
		glVertex3f(i, 0, size);
		glVertex3f(-i, 0, -size);
		glVertex3f(-i, 0, size);
		//Parallel lines to X
		glVertex3f(-size, 0, i);
		glVertex3f(size, 0, i);
		glVertex3f(-size, 0, -i);
		glVertex3f(size, 0, -i);
	}

	//// x-axis
	glColor3f(1, 0, 0);
	glVertex3f(-size, 0, 0);
	glVertex3f(size, 0, 0);

	// z-axis
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, -size);
	glVertex3f(0, 0, size);

	glEnd();

	glColor3f(1, 1, 1);
}

std::vector<GLfloat> Cube::GetVertices()
{
	for (int i = 0; i < 72; ++i) vertices.push_back(vertices2[i]);
	return vertices;
}

std::vector<GLfloat>  Cube::GetNormals()
{
	for (int i = 0; i < 72; ++i) normals.push_back(normals2[i]);
	return normals;
}

std::vector<GLfloat>  Cube::GetColors()
{
	for (int i = 0; i < 72; ++i) colors.push_back(colors2[i]);
	return colors;
}

std::vector<GLfloat>  Cube::GetTexcoords()
{
	for (int i = 0; i < 48; ++i) texcoords.push_back(texCoords[i]);
	return texcoords;
}

std::vector<GLubyte>  Cube::GetIndices()
{
	for (int i = 0; i < 36; ++i) indicesVector.push_back(indices[i]);

	return indicesVector;
}

AABB& Cube::GetCubeBB()
{
	cubeBoundingBox.SetFrom((float3*)vertices2, 8);
	return cubeBoundingBox;
}

float* Cube::GetQuadVertex()
{
	return vertices2;
}