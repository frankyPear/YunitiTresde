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
	billboards[name] = b;
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

void Billboard::ComputeQuad(billboard* b, float *vertex, Frustum& f)
{
	float3 vectorUp = float3(0.0f, 1.0f, 0.0f);
	float3 normalVector = f.pos - b->centerPoint;
	float3 vectorRight = normalVector.Cross(vectorUp);
	vertex[0] = b->centerPoint.x + vectorRight.x * (b->width / 2.0f);
	vertex[1] = b->centerPoint.y + vectorRight.y * (b->height / 2.0f);
	vertex[2] = b->centerPoint.z + vectorRight.z;
	vertex[3] = b->centerPoint.x - vectorRight.x * (b->width / 2.0f);
	vertex[4] = b->centerPoint.y + vectorRight.y * (b->height / 2.0f);
	vertex[5] = b->centerPoint.z + vectorRight.z;
	vertex[6] = b->centerPoint.x - vectorRight.x * (b->width / 2.0f);
	vertex[7] = b->centerPoint.y - vectorRight.y * (b->height / 2.0f);
	vertex[8] = b->centerPoint.z + vectorRight.z;
	vertex[9] = b->centerPoint.x + vectorRight.x * (b->width / 2.0f);
	vertex[10] = b->centerPoint.y - vectorRight.y * (b->height / 2.0f);
	vertex[11] = b->centerPoint.z + vectorRight.z;
}
