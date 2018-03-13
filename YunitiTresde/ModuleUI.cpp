#include "ModuleUI.h"
#include "OpenGL.h"
#include "ComponentButton.h"
#include "ComponentLabel.h"
#include "Application.h"
#include "ModuleTextures.h"
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
#include "Glew\include\glew.h"
#include "Glew\include\glfw3.h"
#include "stb\include\fontstash.h"
#include "stb\include\gl3corefontstash.h"

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
void ModuleUI::dash(float dx, float dy)
{
	glBegin(GL_LINES);
	glColor4ub(0, 0, 0, 128);
	glVertex2f(dx - 5, dy);
	glVertex2f(dx - 10, dy);
	glEnd();
}
void ModuleUI::line(float sx, float sy, float ex, float ey)
{
	glBegin(GL_LINES);
	glColor4ub(0, 0, 0, 128);
	glVertex2f(sx, sy);
	glVertex2f(ex, ey);
	glEnd();
}
//void ModuleUI::key(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
//	(void)scancode;
//	(void)mods;
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, GL_TRUE);
//	/*if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
//		debug = !debug;*/
//}
bool ModuleUI::Start()
{

	//int fontSKURRI = 0;
	//int fontMORPHEUS = 0;
	//int fontFRIZ = 0;
	//int fontARIALN = 0;
	//GLFWwindow* window;
	//const GLFWvidmode* mode;

	//FONScontext* fs = NULL;

	//if (!glfwInit())
	//	return -1;

	//mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	//window = glfwCreateWindow(mode->width - 40, mode->height - 80, "Font Stash", NULL, NULL);
	//if (!window) {
	//	glfwTerminate();
	//	return -1;
	//}

	////glfwSetKeyCallback(window, key);
	//glfwMakeContextCurrent(window);

	//fs = glfonsCreate(512, 512, FONS_ZERO_TOPLEFT);
	//if (fs == NULL) {
	//	printf("Could not create stash.\n");
	//	return -1;
	//}

	//fontSKURRI = fonsAddFont(fs, "skurri", "../Resources/wow/Fonts/SKURRI.ttf");
	//if (fontSKURRI == 0) {
	//	printf("Could not add font.\n");
	//	return -1;
	//}
	//fontMORPHEUS = fonsAddFont(fs, "morpheus", "../Resources/wow/Fonts/MORPHEUS.ttf");
	//if (fontMORPHEUS == 0) {
	//	printf("Could not add font.\n");
	//	return -1;
	//}
	//fontFRIZ = fonsAddFont(fs, "frizqt", "../Resources/wow/Fonts/FRIZQT__.ttf");
	//if (fontFRIZ == 0) {
	//	printf("Could not add font.\n");
	//	return -1;
	//}
	//fontARIALN = fonsAddFont(fs, "arial", "../Resources/wow/Fonts/ARIALN.ttf");
	//if (fontARIALN == 0) {
	//	printf("Could not add font.\n");
	//	return -1;
	//}

	//while (!glfwWindowShouldClose(window))
	//{
	//	float sx, sy, dx, dy, lh = 0;
	//	int width, height;
	//	unsigned int white, black, brown, blue;
	//	glfwGetFramebufferSize(window, &width, &height);
	//	// Update and render
	//	glViewport(0, 0, width, height);
	//	glClearColor(0.3f, 0.3f, 0.32f, 1.0f);
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	glEnable(GL_BLEND);
	//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//	glDisable(GL_TEXTURE_2D);
	//	glMatrixMode(GL_PROJECTION);
	//	glLoadIdentity();
	//	glOrtho(0, width, height, 0, -1, 1);

	//	glMatrixMode(GL_MODELVIEW);
	//	glLoadIdentity();
	//	glDisable(GL_DEPTH_TEST);
	//	glColor4ub(255, 255, 255, 255);
	//	glEnable(GL_BLEND);
	//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//	glEnable(GL_CULL_FACE);

	//	white = glfonsRGBA(255, 255, 255, 255);
	//	brown = glfonsRGBA(192, 128, 0, 128);
	//	blue = glfonsRGBA(0, 192, 255, 255);
	//	black = glfonsRGBA(0, 0, 0, 255);

	//	sx = 50; sy = 50;

	//	dx = sx; dy = sy;

	//	dash(dx, dy);

	//	fonsClearState(fs);

	//	fonsSetSize(fs, 124.0f);
	//	fonsSetFont(fs, fontSKURRI);
	//	fonsVertMetrics(fs, NULL, NULL, &lh);
	//	dx = sx;
	//	dy += lh;
	//	dash(dx, dy);

	//	fonsSetSize(fs, 124.0f);
	//	fonsSetFont(fs, fontARIALN);
	//	fonsSetColor(fs, white);
	//	dx = fonsDrawText(fs, dx, dy, "The quick ", NULL);

	//	fonsSetSize(fs, 48.0f);
	//	fonsSetFont(fs, fontFRIZ);
	//	fonsSetColor(fs, brown);
	//	dx = fonsDrawText(fs, dx, dy, "brown ", NULL);

	//	fonsSetSize(fs, 24.0f);
	//	fonsSetFont(fs, fontMORPHEUS);
	//	fonsSetColor(fs, white);
	//	dx = fonsDrawText(fs, dx, dy, "fox ", NULL);

	//	fonsVertMetrics(fs, NULL, NULL, &lh);
	//	dx = sx;
	//	dy += lh*1.2f;
	//	dash(dx, dy);
	//	fonsSetFont(fs, fontMORPHEUS);
	//	dx = fonsDrawText(fs, dx, dy, "Manage Account ", NULL);
	//	fonsSetFont(fs, fontFRIZ);
	//	dx = fonsDrawText(fs, dx, dy, "Login ", NULL);
	//	fonsSetFont(fs, fontARIALN);
	//	dx = fonsDrawText(fs, dx, dy, "Cinematics.", NULL);

	//	dx = sx;
	//	dy += lh*1.2f;
	//	dash(dx, dy);
	//	fonsSetSize(fs, 12.0f);
	//	fonsSetFont(fs, fontMORPHEUS);
	//	fonsSetColor(fs, blue);
	//	fonsDrawText(fs, dx, dy, "Login.", NULL);

	//	fonsVertMetrics(fs, NULL, NULL, &lh);
	//	dx = sx;
	//	dy += lh*1.2f * 2;
	//	dash(dx, dy);
	//	fonsSetSize(fs, 18.0f);
	//	fonsSetFont(fs, fontFRIZ);
	//	fonsSetColor(fs, white);
	//	fonsDrawText(fs, dx, dy, "Account.", NULL);

	//	fonsVertMetrics(fs, NULL, NULL, &lh);
	//	dx = sx;
	//	dy += lh*1.2f;
	//	dash(dx, dy);
	//	fonsSetFont(fs, fontARIALN);
	//	fonsDrawText(fs, dx, dy, "User", NULL);

	//	// Font alignment
	//	fonsSetSize(fs, 18.0f);
	//	fonsSetFont(fs, fontARIALN);
	//	fonsSetColor(fs, white);

	//	dx = 50; dy = 350;
	//	line(dx - 10, dy, dx + 250, dy);
	//	fonsSetAlign(fs, FONS_ALIGN_LEFT | FONS_ALIGN_TOP);
	//	dx = fonsDrawText(fs, dx, dy, "Top", NULL);
	//	dx += 10;
	//	fonsSetAlign(fs, FONS_ALIGN_LEFT | FONS_ALIGN_MIDDLE);
	//	dx = fonsDrawText(fs, dx, dy, "Middle", NULL);
	//	dx += 10;
	//	fonsSetAlign(fs, FONS_ALIGN_LEFT | FONS_ALIGN_BASELINE);
	//	dx = fonsDrawText(fs, dx, dy, "Baseline", NULL);
	//	dx += 10;
	//	fonsSetAlign(fs, FONS_ALIGN_LEFT | FONS_ALIGN_BOTTOM);
	//	fonsDrawText(fs, dx, dy, "Bottom", NULL);

	//	dx = 150; dy = 400;
	//	line(dx, dy - 30, dx, dy + 80.0f);
	//	fonsSetAlign(fs, FONS_ALIGN_LEFT | FONS_ALIGN_BASELINE);
	//	fonsDrawText(fs, dx, dy, "Left", NULL);
	//	dy += 30;
	//	fonsSetAlign(fs, FONS_ALIGN_CENTER | FONS_ALIGN_BASELINE);
	//	fonsDrawText(fs, dx, dy, "Center", NULL);
	//	dy += 30;
	//	fonsSetAlign(fs, FONS_ALIGN_RIGHT | FONS_ALIGN_BASELINE);
	//	fonsDrawText(fs, dx, dy, "Right", NULL);

	//	// Blur
	//	dx = 500; dy = 350;
	//	fonsSetAlign(fs, FONS_ALIGN_LEFT | FONS_ALIGN_BASELINE);

	//	fonsSetSize(fs, 60.0f);
	//	fonsSetFont(fs, fontMORPHEUS);
	//	fonsSetColor(fs, white);
	//	fonsSetSpacing(fs, 5.0f);
	//	fonsSetBlur(fs, 10.0f);
	//	fonsDrawText(fs, dx, dy, "Account...", NULL);

	//	dy += 50.0f;

	//	fonsSetSize(fs, 18.0f);
	//	fonsSetFont(fs, fontARIALN);
	//	fonsSetColor(fs, black);
	//	fonsSetSpacing(fs, 0.0f);
	//	fonsSetBlur(fs, 3.0f);
	//	fonsDrawText(fs, dx, dy + 2, "login", NULL);

	//	fonsSetColor(fs, white);
	//	fonsSetBlur(fs, 0);
	//	fonsDrawText(fs, dx, dy, "login", NULL);

	//	if (debug)
	//		fonsDrawDebug(fs, 800.0, 50.0);


	//	glEnable(GL_DEPTH_TEST);

	//	glfwSwapBuffers(window);
	//	glfwPollEvents();
	//}

	//glfonsDelete(fs);

	//glfwTerminate();

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
	glClear(GL_COLOR_BUFFER_BIT);
	printElement("..\\Resources\\wow\\UI\\login_background.png", verticesBackground);
	printElement("..\\Resources\\wow\\UI\\COMMON\\Glues-Logo.png", verticeslogo);
	printElement("..\\Resources\\wow\\UI\\BUTTONS\\UI-DialogBox-Button-Up.png", verticesButtonMA);
	printElement("..\\Resources\\wow\\UI\\BUTTONS\\UI-DialogBox-Button-Up.png", verticesButtonCS);
	printElement("..\\Resources\\wow\\UI\\BUTTONS\\UI-DialogBox-Button-Up.png", verticesButtonLogin);
	printElement("..\\Resources\\wow\\UI\\BUTTONS\\UI-DialogBox-Button-Up.png", verticesButtonCinematics);
	printElement("..\\Resources\\wow\\UI\\BUTTONS\\UI-DialogBox-Button-Up.png", verticesButtonTerms);
	printElement("..\\Resources\\wow\\UI\\DialogFrame\\UI-DialogBox-Header.png", verticesInputLogin);
	printElement("..\\Resources\\wow\\UI\\DialogFrame\\UI-DialogBox-Header.png", verticesInputPass);

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
void ModuleUI::printElement(const char* path, float* vertices) {
	GLuint vertexID = 0;
	GLuint texID = 0;
   
	GLfloat texCoordsBackground[8] = {
		1,1,    0,1,    0,0,    1,0 };    // front
	GLubyte indices[6] = {
		0, 1, 2,   2, 3, 0 };      // front


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, vertexID);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glEnable(GL_TEXTURE_2D);
	glBindBuffer(GL_ARRAY_BUFFER, texID);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoordsBackground);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindTexture(GL_TEXTURE_2D, App->textures->GetTexture(path));

	glPushMatrix();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);
	glPopMatrix();

	glDisableClientState(GL_TEXTURE_2D_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glBindTexture(GL_TEXTURE_2D, 0);
}
//Glues - Logo
void ModuleUI::printButton2() {
	//glClear(GL_COLOR_BUFFER_BIT);

	GLuint vertexID = 0;
	GLuint texID = 0;
	float verticesBackground[12] = {
		-0.45, -0.30,0.15,  -0.650, -0.30,0.15,  -0.650,-0.35,0.15,   -0.45,-0.35,0.15 };   // v0,v1,v2,v3 (front)
	GLfloat texCoordsBackground[8] = {
		1,1,    0,1,    0,0,    1,0 };    // front
	GLubyte indices[6] = {
		0, 1, 2,   2, 3, 0 };      // front

	glEnable(GL_BLEND);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, vertexID);
	glVertexPointer(3, GL_FLOAT, 0, verticesBackground);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glEnable(GL_TEXTURE_2D);
	glBindBuffer(GL_ARRAY_BUFFER, texID);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoordsBackground);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindTexture(GL_TEXTURE_2D, App->textures->GetTexture("..\\Resources\\wow\\UI\\BUTTONS\\UI-DialogBox-Button-Up.png"));
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);
	glPopMatrix();

	glDisableClientState(GL_TEXTURE_2D_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glBindTexture(GL_TEXTURE_2D, 0);
}
