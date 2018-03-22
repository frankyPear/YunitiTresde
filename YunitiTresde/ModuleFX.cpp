#include "ModuleFX.h"
#include "Application.h"
#include "ModuleTextures.h"


ModuleFX::ModuleFX()
{
}


ModuleFX::~ModuleFX()
{
}

bool ModuleFX::Init()
{
	return true;
}

bool ModuleFX::Start()
{
	return true;
}

update_status ModuleFX::Update()
{
	//DrawBillboards();
	return UPDATE_CONTINUE;
}

bool ModuleFX::Clear()
{
	return true;
}

void ModuleFX::CreateBillboard(char* imagepath, const char* name, float3 centerpos, float width, float height)
{
	billboard *b = new billboard();
	b->vertices = new float[12];
	b->centerPoint = centerpos;
	b->texID = App->textures->GetTexture(imagepath);
	b->width = width;
	b->height = height;
	scene_billboards.push_back(b);

}

void ModuleFX::Draw(billboard *b, Frustum& f)
{
	GLuint vertexID = 0;
	GLuint texID = 0;
	GLfloat texCoordsBackground[8] = {
		1,1,    0,1,    0,0,    1,0 };    // front

	//float verticesBackground[12] = {0.850f, 0.650f,0.f, -0.850f, 0.650f,0.f, -0.850f,-0.650f,0.f, 0.850f,-0.650f,0.f };
	//GLubyte indices[6] = {0, 1, 2,   2, 3, 0 };      // front

	//float verticesBackground[12] = {0.850f, 0.650f,0.f, -0.850f, 0.650f,0.f, -0.850f,-0.650f,0.f, 0.850f,-0.650f,0.f };
	float *verticesBackground = new float[12];
	ComputeQuad(b, verticesBackground, f);

	GLubyte indices[6] = {
		0, 1, 2, 3 };      // front
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
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices);
	glPopMatrix();

	glDisableClientState(GL_TEXTURE_2D_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glBindTexture(GL_TEXTURE_2D, 0);

}

void ModuleFX::DrawBillboards(Frustum& f)
{
	for (int i = 0; i < scene_billboards.size(); ++i) Draw(scene_billboards[i],f);
}

ModuleFX::billboard* ModuleFX::GetBillboard(const char* name)
{
	std::map<const char*, billboard*>::iterator it = billboards.begin();
	it = billboards.find("grass");
	if (it != billboards.end())
	{
		return it->second;
	}
	return nullptr;
}

void ModuleFX::ComputeQuad(billboard* b, float *vertex, Frustum& f)
{
	float3 vectorUp = float3(0.0f,1.0f,0.0f);
	float3 vectorRight = f.WorldRight().Cross(vectorUp);
	vertex[0] = b->centerPoint.x+vectorRight.x*b->width;
	vertex[1] = b->centerPoint.y+vectorRight.y*b->height;
	vertex[2] = b->centerPoint.z+vectorRight.z;
	vertex[3] = b->centerPoint.x - vectorRight.x*b->width;
	vertex[4] = b->centerPoint.y + vectorRight.y*b->height;
	vertex[5] = b->centerPoint.z + vectorRight.z;
	vertex[6] = b->centerPoint.x - vectorRight.x*b->width;
	vertex[7] = b->centerPoint.y - vectorRight.y*b->height;
	vertex[8] = b->centerPoint.z + vectorRight.z;
	vertex[9] = b->centerPoint.x + vectorRight.x*b->width;
	vertex[10] = b->centerPoint.y - vectorRight.y*b->height;
	vertex[11] = b->centerPoint.z + vectorRight.z;
}
