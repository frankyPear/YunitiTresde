#include "ModuleTextures.h"
#include "DevIL\include\IL\il.h"
#include "DevIL\include\IL\ilu.h"
#include "DevIL\include\IL\ilut.h"

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


void ModuleTextures::loadImage()
{
	GLuint success = ilLoadImage("");
	ILuint ImageName; // The image name to return.
	ilGenImages(1, &ImageName); // Grab a new image name.
}
