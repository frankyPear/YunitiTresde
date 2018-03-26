#include "Billboard.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "Mathgeolib\include\Geometry\Frustum.h"


Billboard::Billboard()
{
}


Billboard::~Billboard()
{
}

void Billboard::CreateBillboard( char* imagepath, const char* name, float3 centerpos, float width, float height)
{
	billboard *b = new billboard();
	b->vertices = new float[12];
	b->vertices[0] = (width / 2) - centerpos.x;
	b->vertices[1] = (height / 2) + centerpos.y;
	b->vertices[2] = centerpos.z;
	b->vertices[3] = (width / 2) + centerpos.x;
	b->vertices[4] = (height / 2) + centerpos.y;
	b->vertices[5] = centerpos.z;
	b->vertices[6] = (width / 2) - centerpos.x;
	b->vertices[7] = (height / 2) - centerpos.y;
	b->vertices[8] = centerpos.z;
	b->vertices[9] = (width / 2) + centerpos.x;
	b->vertices[10] = (height / 2) - centerpos.y;
	b->vertices[11] = centerpos.z;
	
	b->texID = App->textures->GetTexture(imagepath);
	scene_billboards.push_back(b);
}

void Billboard::Draw(billboard *b)
{
	GLuint vertexID = 0;
	GLuint texID = 0;
	float verticesBackground[12] = {
		0.850f, 0.650f,0.f, -0.850f, 0.650f,0.f, -0.850f,-0.650f,0.f, 0.850f,-0.650f,0.f };
	GLfloat texCoordsBackground[8] = {
		1,1,    0,1,    0,0,    1,0 };    // front
	GLubyte indices[6] = {
		0, 1, 2,   2, 3, 0 };      // front

	glEnable(GL_BLEND);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, vertexID);
	glVertexPointer(3, GL_FLOAT, 0, verticesBackground);//b->vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glEnable(GL_TEXTURE_2D);
	glBindBuffer(GL_ARRAY_BUFFER, texID);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoordsBackground);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1f);

	glBindTexture(GL_TEXTURE_2D, b->texID);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);
	glPopMatrix();

	glDisableClientState(GL_TEXTURE_2D_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glBindTexture(GL_TEXTURE_2D, 0);
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//
	//glBindBuffer(GL_ARRAY_BUFFER, vertexID);
	//glVertexPointer(3, GL_FLOAT, 0, b->vertices);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//
	//
	//glEnable(GL_TEXTURE_2D);
	//glBindBuffer(GL_ARRAY_BUFFER, texID);
	//glTexCoordPointer(2, GL_FLOAT, 0, texCoordsBackground);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//
	//glBindTexture(GL_TEXTURE_2D, b->texID);
	//
	//glPushMatrix();
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);
	//glPopMatrix();
	//
	//glDisableClientState(GL_TEXTURE_2D_ARRAY);
	//glDisableClientState(GL_VERTEX_ARRAY);
	//glBindTexture(GL_TEXTURE_2D, 0);
}

void Billboard::DrawBillboards()
{
	for (int i = 0; i < scene_billboards.size(); ++i) Draw(scene_billboards[i]);
}



void Billboard::ComputeQuad(billboard b, std::vector<GLfloat>& vertex, Frustum& f)
{
	float3 vectorUp = float3(0.0f, 1.0f, 0.0f);
	float3 vectorRight = (b.centerPoint - f.pos).Cross(vectorUp).Normalized();
	float3 normalVector = vectorRight.Cross(vectorUp).Normalized();
	float3 rightUpVertex = b.centerPoint + (vectorRight*(b.width / 2)) + (vectorUp*(b.height / 2));
	float3 leftUpVertex = b.centerPoint - (vectorRight*(b.width / 2)) + (vectorUp*(b.height / 2));
	float3 leftDownVertex = b.centerPoint - (vectorRight*(b.width / 2)) - (vectorUp*(b.height / 2));
	float3 rightDownVertex = b.centerPoint + (vectorRight*(b.width / 2)) - (vectorUp*(b.height / 2));
	vertex.push_back(rightUpVertex.x);
	vertex.push_back(rightUpVertex.y);
	vertex.push_back(rightUpVertex.z);
	vertex.push_back(leftUpVertex.x);
	vertex.push_back(leftUpVertex.y);
	vertex.push_back(leftUpVertex.z);
	vertex.push_back(leftDownVertex.x);
	vertex.push_back(leftDownVertex.y);
	vertex.push_back(leftDownVertex.z);
	vertex.push_back(rightDownVertex.x);
	vertex.push_back(rightDownVertex.y);
	vertex.push_back(rightDownVertex.z);
}
