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

void ModuleFX::CreateBillboard(char* imagepath, float3 centerpos, float width, float height)
{
	billboard b = billboard();
	b.centerPoint = centerpos;
	b.texID = App->textures->GetTexture(imagepath);
	b.width = width;
	b.height = height;
	scene_billboards.push_back(b);
}

void ModuleFX::Draw(billboard b, Frustum& f)
{
	GLuint vertexID = 0;
	GLuint texID = 0;
	GLfloat texCoordsBackground[8] = {
		1,1,    0,1,    0,0,    1,0 };    // front

	//float verticesBackground[12] = {0.850f, 0.650f,0.f, -0.850f, 0.650f,0.f, -0.850f,-0.650f,0.f, 0.850f,-0.650f,0.f };
	//GLubyte indices[6] = {0, 1, 2,   2, 3, 0 };      // front

	//float verticesBackground[12] = {0.850f, 0.650f,0.f, -0.850f, 0.650f,0.f, -0.850f,-0.650f,0.f, 0.850f,-0.650f,0.f };
	//float *verticesBackground = new float[12];
	std::vector<GLfloat> verticesBackground;
	ComputeQuad(b, verticesBackground, f);

	GLubyte indices[6] = {
		0, 1, 2, 3 };      // front
	glEnable(GL_BLEND);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, vertexID);
	glVertexPointer(3, GL_FLOAT, 0, &verticesBackground[0]);//b->vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glEnable(GL_TEXTURE_2D);
	glBindBuffer(GL_ARRAY_BUFFER, texID);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoordsBackground);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1f);

	glBindTexture(GL_TEXTURE_2D, b.texID);
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


void ModuleFX::ComputeQuad(billboard b, std::vector<GLfloat>& vertex, Frustum& f)
{
	float3 vectorUp = float3(0.0f, 1.0f, 0.0f);
	float3 vectorRight = (b.centerPoint- f.pos).Cross(vectorUp).Normalized();
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

void ModuleFX::CreateGrid(char* imagepath, float3 initialcenterpos, float width, float height, int rows, int columns)
{
	float3 initpos = initialcenterpos;
	for (int i = 0; i < rows; ++i) 
	{
		for (int j = 0; j < columns; ++j)
		{
			billboard b = billboard();
			b.centerPoint = initpos+  float3((offsetX)*j, 0.0f,(offsetY)*i);
			b.texID = App->textures->GetTexture(imagepath);
			b.width = width;
			b.height = height;
			scene_billboards.push_back(b);
		}
	}
	
}

void ModuleFX::DrawParticle(aiVector3D position, aiVector2D size, int texID, Frustum& f)
{
	GLuint vertexID = 0;
	GLfloat texCoordsBackground[8] = {1,1,    0,1,    0,0,    1,0 };  
	std::vector<GLfloat> verticesBackground;
	ComputeParticleQuad(float3(position.x, position.y, position.z), size ,verticesBackground, f);
	GLubyte indices[6] = {
		0, 1, 2, 3 };      // front
	glEnable(GL_BLEND);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, vertexID);
	glVertexPointer(3, GL_FLOAT, 0, &verticesBackground[0]);//b->vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glEnable(GL_TEXTURE_2D);
	glBindBuffer(GL_ARRAY_BUFFER, texID);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoordsBackground);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1f);

	glBindTexture(GL_TEXTURE_2D, texID);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices);
	glPopMatrix();

	glDisableClientState(GL_TEXTURE_2D_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glBindTexture(GL_TEXTURE_2D, 0);
}


void ModuleFX::ComputeParticleQuad(float3 centerPoint, aiVector2D size, std::vector<GLfloat>& vertex, Frustum& f)
{
	float3 vectorUp = float3(0.0f, 1.0f, 0.0f);
	float3 vectorRight = (centerPoint - f.pos).Cross(vectorUp).Normalized();
	float3 normalVector = vectorRight.Cross(vectorUp).Normalized();
	float3 rightUpVertex = centerPoint + (vectorRight*(size.x / 2)) + (vectorUp*(size.y / 2));
	float3 leftUpVertex = centerPoint - (vectorRight*(size.x / 2)) + (vectorUp*(size.y / 2));
	float3 leftDownVertex = centerPoint - (vectorRight*(size.x / 2)) - (vectorUp*(size.y / 2));
	float3 rightDownVertex = centerPoint + (vectorRight*(size.x / 2)) - (vectorUp*(size.y / 2));
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
