#include "Application.h"
#include "ModuleImGui.h"
#include "ModuleTextures.h"
#include "ModuleRenderer.h"
#include "DevIL\include\IL\il.h"
#include "DevIL\include\IL\ilu.h"
#include "DevIL\include\IL\ilut.h"
#include <iostream>
using namespace std;

#pragma comment (lib, "DevIL/lib/x86/Release/DevIL.lib")
#pragma comment (lib, "DevIL/lib/x86/Release/ILU.lib")
#pragma comment (lib, "DevIL/lib/x86/Release/ILUT.lib")

ModuleTextures::ModuleTextures()
{
}

ModuleTextures::~ModuleTextures()
{
}

bool ModuleTextures::Init()
{
	ilInit();
	ilutInit();
	bool ret = true;
	return ret;
}

bool ModuleTextures::Start()
{
	bool ret = true;
	return ret;
}

update_status ModuleTextures::Update()
{
	return UPDATE_CONTINUE;
}

bool ModuleTextures::CleanUp()
{
	bool ret = true;
	return ret;
}

void ModuleTextures::DrawCheckers()
{

	for (int i = 0; i < 128; i++) {
		for (int j = 0; j < 128; j++) {
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
			checkImage[i][j][0] = (GLubyte)c;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)c;
			checkImage[i][j][3] = (GLubyte)255;
		}
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 128, 128, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
	glBindTexture(GL_TEXTURE_2D, 0);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindTexture(GL_TEXTURE_2D, texId);
	glTexCoordPointer(2, GL_TEXTURE_COORD_ARRAY, 0, indices);



	glBindTexture(GL_TEXTURE_2D, 0);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

}


GLuint ModuleTextures::loadImage(char* fileName)
{
	return ilutGLLoadImage(fileName);
}

void  ModuleTextures::DeleteImage(uint imageID) {
	ilDeleteImages(1, &imageID);
}

void ModuleTextures::setWrapMode(int mode)
{
	switch (mode)
	{
	case 0:
		actualWrapMode = GL_REPEAT;
		break;
	case 1:
		actualWrapMode = GL_MIRRORED_REPEAT;
		break;
	case 2:
		actualWrapMode = GL_CLAMP_TO_EDGE;
		break;
	case 3:
		actualWrapMode = GL_CLAMP_TO_BORDER;
		break;
	}
}

void ModuleTextures::setFilterMode(int filter) {
	switch (filter)
	{
	case 0:
		actualFilterMode = GL_NEAREST;
		break;
	case 1:
		actualFilterMode = GL_LINEAR;
		break;
	case 2:
		actualFilterMode = GL_NEAREST_MIPMAP_NEAREST;
		break;
	case 3:
		actualFilterMode = GL_LINEAR_MIPMAP_NEAREST;
		break;
	case 4:
		actualFilterMode = GL_NEAREST_MIPMAP_LINEAR;
		break;
	case 5:
		actualFilterMode = GL_LINEAR_MIPMAP_LINEAR;
		break;
	}
}



GLuint ModuleTextures::GetTexture(char* path)
{
	map<string, loadedTex>::iterator it = loadedTextures.begin();
	it = loadedTextures.find(path);
	GLuint res = -1;
	if (it != loadedTextures.end())
	{
		++(*it).second.numberOfReferences;
		res = (*it).second.texId;
	}
	else
	{
		GLuint id = loadImage(path);
		if (id != -1) {
			loadedTextures[path] = loadedTex(id);
			res = id;
		}
	}
	return res;
}

void ModuleTextures::RemoveTexture(const char* path)
{
	map<string, loadedTex>::iterator it = loadedTextures.begin();
	it = loadedTextures.find(path);
	if (it != loadedTextures.end()) {
		--(*it).second.numberOfReferences;
		if ((*it).second.numberOfReferences <= 0)
		{
			loadedTextures.erase(it);
		}
	}
}

int ModuleTextures::GetNumberOfTextures()
{
	return loadedTextures.size();
}

int  ModuleTextures::GetNumberOfReferences(const char* path)
{
	map<string, loadedTex>::iterator it = loadedTextures.begin();
	it = loadedTextures.find(path);
	if (it != loadedTextures.end()) {
		return (*it).second.numberOfReferences;
	}
	else return -1;
}

//--------------------------------------- loadedTex methods ----------------------------

loadedTex::loadedTex()
{
	texId = -1;
	numberOfReferences = 0;
}

loadedTex::loadedTex(GLuint id)
{
	texId = id;
	numberOfReferences = 1;
}


loadedTex::~loadedTex()
{
}