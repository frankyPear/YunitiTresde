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
	billboards[name] = b;
}

void Billboard::Draw(billboard *b)
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
	glVertexPointer(3, GL_FLOAT, 0, b->vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glEnable(GL_TEXTURE_2D);
	glBindBuffer(GL_ARRAY_BUFFER, texID);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoordsBackground);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindTexture(GL_TEXTURE_2D, b->texID);

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

Billboard::billboard* Billboard::GetBillboard(const char* name)
{
	std::map<const char*, billboard*>::iterator it = billboards.begin();
	it = billboards.find("grass");
	if (it != billboards.end())
	{
		return it->second;
	}
	return nullptr;
}