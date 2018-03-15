#include "Billboard.h"
#include "Application.h"
#include "ModuleTextures.h"



Billboard::Billboard()
{
}


Billboard::~Billboard()
{
}

void Billboard::CreateBillboard(const char* imagepath, const char* name, float3 centerpos, float width, float height)
{
	billboard b = billboard();
	float3 *billboardVertices = new float3[4];
	float3 upperLeft = float3 ((width/2) - centerpos.x, (height / 2) + centerpos.y, centerpos.z);
	float3 upperRight = float3((width / 2) + centerpos.x, (height / 2) + centerpos.y, centerpos.z);
	float3 lowerLeft = float3((width / 2) - centerpos.x, (height / 2) - centerpos.y, centerpos.z);
	float3 lowerRight = float3((width / 2) + centerpos.x, (height / 2) - centerpos.y, centerpos.z);
	b.vertices = billboardVertices;
	b.texID = App->textures->GetTexture(imagepath);
	
}

void Billboard::Draw(billboard b)
{
	GLuint vertexID = 0;
	GLuint texID = 0;
	GLfloat texCoordsBackground[8] = {
		1,1,    0,1,    0,0,    1,0 };    // front
	GLubyte indices[6] = {
		0, 1, 2,   2, 3, 0 };      // front


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, vertexID);
	glVertexPointer(3, GL_FLOAT, 0, b.vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glEnable(GL_TEXTURE_2D);
	glBindBuffer(GL_ARRAY_BUFFER, texID);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoordsBackground);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindTexture(GL_TEXTURE_2D, b.texID);

	glPushMatrix();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);
	glPopMatrix();

	glDisableClientState(GL_TEXTURE_2D_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Billboard::DrawBillboards()
{
	for (int i = 0; i < scene_billboards.size(); ++i) Draw(scene_billboards[i]);
}