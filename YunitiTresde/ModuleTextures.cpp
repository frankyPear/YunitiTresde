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
	ilInit();
	iluInit();
	ilutInit();
	
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


GLuint ModuleTextures::loadImage(const char* fileName)
{
	GLuint textureID;
	ILuint ImageName; // The image name to return.
	ilGenImages(1, &ImageName); // Grab a new image name.
	ilBindImage(ImageName);

	ILboolean operationSuccess = ilLoadImage(fileName);
	if (operationSuccess) {
		ILinfo ImageInfo;
		iluGetImageInfo(&ImageInfo);
		if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
		{
			iluFlipImage();
		}
		operationSuccess = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
		if (!operationSuccess)
		{
			ILenum error = ilGetError();
			cout << "error converting: " << error << endl;
			return -1;
		}

		// Generate texture ID
		glGenTextures(1, &textureID);
		// Bind id to texture.
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, actualWrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, actualWrapMode);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, actualFilterMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, actualFilterMode);

		glGenerateMipmap(GL_TEXTURE_2D);

		glTexImage2D(GL_TEXTURE_2D, 0,
			ilGetInteger(IL_IMAGE_FORMAT),
			ilGetInteger(IL_IMAGE_WIDTH),
			ilGetInteger(IL_IMAGE_HEIGHT),
			0,
			ilGetInteger(IL_IMAGE_FORMAT),
			GL_UNSIGNED_BYTE, ilGetData()
		);
		App->renderer->width_ = ilGetInteger(IL_IMAGE_WIDTH);
		App->renderer->heigth_ = ilGetInteger(IL_IMAGE_HEIGHT);
		App->renderer->fileNameImage = (char*)fileName;
		App->renderer->bytes_ = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
	}
	else {
		ILenum error = ilGetError();
		cout << "error loading: " << error << endl;
		return -1;
	}
	ilDeleteImages(1, &ImageName);
	return textureID;
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