#include "ModuleUI.h"
#include "OpenGL.h"
#include "ComponentButton.h"
#include "ComponentLabel.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
//#include "ComponentInputText.h"
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb\include\stb_truetype.h"
#include "SDL\include\SDL.h"
#include "SDL\include\SDL_image.h"
#include "SDL\include\SDL_ttf.h"
#pragma comment (lib, "SDL/libx86/SDL2.lib")
#pragma comment (lib, "SDL/libx86/SDL2main.lib")

using namespace std;
using namespace experimental::filesystem;


ModuleUI::ModuleUI()
{
	/*ComponentButton* cb = new ComponentButton(250,250,0,0);*/
}

ModuleUI::~ModuleUI()
{
}

bool ModuleUI::Init()
{
	return true;
}

bool ModuleUI::Start()
{
	//TTF_Font* gFont = NULL;
	////Open the font
	//gFont = TTF_OpenFont("../Resources/wow/Fonts/SKURRI.ttf", 28);
	//if (gFont == NULL)
	//{
	//	printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
	//	return false;
	//}
	//else
	//{
	//	//Render text
	//	SDL_Color textColor = { 0, 0, 0 };
	//	//if (!gTextTexture.loadFromRenderedText("The quick brown fox jumps over the lazy dog", textColor))
	//	//{
	//	//	printf("Failed to render text texture!\n");
	//	//	return false;
	//	//}
	//}


	//Load("../Resources/wow/Fonts/SKURRI.ttf");
	//const std::string& fontBuffer = Get("../Resources/wow/Fonts/SKURRI.ttf");

	//stbtt_fontinfo info;
	//stbtt_InitFont(&info, (const unsigned char*)fontBuffer.c_str(), 0);

	//int b_w = 512; /* bitmap width */
	//int b_h = 128; /* bitmap height */
	//float l_h = 64.0f; /* line height */

	//				   /* create a bitmap for the phrase */
	//unsigned char* bitmap = (unsigned char*)malloc(b_w * b_h);

	///* calculate font scaling */
	//float scale = stbtt_ScaleForPixelHeight(&info, l_h);

	//char* word = "Login";

	//int x = 0;

	//int ascent, descent, lineGap;
	//stbtt_GetFontVMetrics(&info, &ascent, &descent, &lineGap);

	//ascent *= (int)scale;
	//descent *= (int)scale;

	//for (size_t i = 0; i < strlen(word); ++i)
	//{
	//	/* get bounding box for character (may be offset to account for chars that dip above or below the line */
	//	int c_x1, c_y1, c_x2, c_y2;
	//	stbtt_GetCodepointBitmapBox(&info, word[i], scale, scale, &c_x1, &c_y1, &c_x2, &c_y2);

	//	/* compute y (different characters have different heights */
	//	int y = ascent + c_y1;

	//	/* render character (stride and offset is important here) */
	//	int byteOffset = x + (y  * b_w);
	//	stbtt_MakeCodepointBitmap(&info, bitmap + byteOffset, c_x2 - c_x1, c_y2 - c_y1, b_w, scale, scale, word[i]);

	//	/* how wide is this character */
	//	int ax;
	//	stbtt_GetCodepointHMetrics(&info, word[i], &ax, 0);
	//	x += ax * (int)scale;

	//	/* add kerning */
	//	int kern;
	//	kern = stbtt_GetCodepointKernAdvance(&info, word[i], word[i + 1]);
	//	x += kern * (int)scale;
	//}

	// RELEASE(fontBuffer);
	// free(fontBuffer);
	// free(bitmap);

	return true;
}

update_status ModuleUI::PreUpdate(float dt)
{
	WowFirstPage();
	return UPDATE_CONTINUE;
}

update_status ModuleUI::Update(float dt)
{
	//adding screenUI
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, 640, 480, 0.0f, 1.0f, -1.0f);

	return UPDATE_CONTINUE;
}

bool ModuleUI::CleanUp()
{
	return true;
}
void ModuleUI::WowFirstPage() {

	/*glBegin(GL_POLYGON);
	glVertex2f(0, y1);
	glVertex2f(0, y1);
	glVertex2f(0, y2);
	glVertex2f(0, y2);
	glEnd();*/
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(0.50, 0.50);
	glVertex2f(-0.50, 0.50);
	glVertex2f(-0.50, -0.50);
	glVertex2f(0.50, -0.50);
	//glVertex2f(50, 90);
	//glVertex2f(100,90);
	//glVertex2f(100, 150);
	//glVertex2f(50, 150);
	glEnd();

}

void ModuleUI::Load(const path& path)
{
	ifstream fontBuffer(path);

	string buffer;

	while (!fontBuffer.eof())
	{
		string tmpBuffer;
		fontBuffer >> tmpBuffer;

		buffer += tmpBuffer;
	}

	buffers[path] = buffer;

	fontBuffer.close();
}

const string& ModuleUI::Get(const path& path) const
{
	return buffers.at(path);
}