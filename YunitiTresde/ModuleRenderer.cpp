#include "Application.h"
#include "ModuleRenderer.h"
#include "ModuleCamera.h"
#include "ModuleTextures.h"
#include "ModuleWindow.h"
#include "SDL\include\SDL.h"
#include "Mathgeolib\include\MathGeoLib.h"
#include "Quad.h"

#pragma comment (lib, "Glew/libx86/glew32.lib")
#pragma comment (lib, "SDL/libx86/SDL2.lib")
#pragma comment (lib, "SDL/libx86/SDL2main.lib")
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")


ModuleRenderer::ModuleRenderer()
{
}


ModuleRenderer::~ModuleRenderer()
{
}

bool ModuleRenderer::Init() {
	bool ret = true;

	//Set Attributes 
	//CORE_PROFILE, uses the new opengl profile
	//There are several context profiles (Ex:_ES for mobile
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	//Used to limit the area of rendering 
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	//Set the version of openGL to 3.1
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	//Create context
	context_ = SDL_GL_CreateContext(App->window->GetWindow());

	if (context_ == NULL)
	{
		LOG("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	//used in the tutorial, to use modern way of glew
	glewExperimental = GL_TRUE;
	//Init GLEW
	if (glewInit() != GLEW_OK)
	{
		LOG("Failed to initalize GLEW! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	//Select the area that will be framed; perhaps change to efectively resize
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	//Init Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Init Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glClearDepth(1.0f);
	//Init color to black
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);

	

	//Set the camera 
	//glOrtho(-5, 5, -5, 5, -5, 5);
	//gluLookAt(1.0, 0.0, -3.0, 0.0, 5.0, 0.0, 0.0, 1.0, 0.0);
	//loadedTexId = App->textures->loadImage	("../Resources/lena.png");
	//loadedTexId = App->textures->loadImage("../Resources/sonic.jpg");
	//loadedTexId = App->textures->loadImage("../Resources/residentevil.gif");
	//loadedTexId = App->textures->loadImage	("../Resources/mario.bmp");
	//switch (0)
	//{
	//case 1:
	//	loadedTexId = App->textures->loadImage(IMAGE1);
	//	break;
	//case 2:
	//	loadedTexId = App->textures->loadImage(IMAGE2);
	//	break;
	//case 3:
	//	loadedTexId = App->textures->loadImage(IMAGE3);
	//	break;
	//case 4:
	//	loadedTexId = App->textures->loadImage(IMAGE4);
	//	break;
	//
	//default:
	//	loadedTexId = App->textures->loadImage(IMAGE1);
	//	break;
	//}


	return ret;
}


bool ModuleRenderer::Start()
{
	return true;
}

update_status ModuleRenderer::PreUpdate()
{
	//Clear the window to draw the next frame
	glClearColor(0, 0, 0, 255);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(App->cam->GetProjectionMatrix());

	//Init Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(App->cam->GetViewMatrix());
	switch (intTex)
	{
	case 0:
		loadedTexId_ = App->textures->loadImage(IMAGE1);
		intTex = -1;
		break;
	case 1:
		loadedTexId_ = App->textures->loadImage(IMAGE2);
		intTex = -1;
		break;
	case 2:
		loadedTexId_ = App->textures->loadImage(IMAGE3);
		intTex = -1;
		break;
	case 3:
		loadedTexId_ = App->textures->loadImage(IMAGE4);
		intTex = -1;
		break;
	default:
		App->textures->DeleteImage(loadedTexId_);
		App->renderer->SetIdImage(-1);
		break;
	}
	
	return UPDATE_CONTINUE;
}

update_status ModuleRenderer::Update()
{
	return UPDATE_CONTINUE;
}


update_status ModuleRenderer::PostUpdate()
{
//	Quad
	DrawElementPlane();
	DrawElementQuadTexturized(loadedTexId_);
	//DrawElementQuad();
	SDL_GL_SwapWindow(App->window->GetWindow());

	return UPDATE_CONTINUE;
}

bool ModuleRenderer::CleanUp() {

	bool ret = true;
	LOG("Destroying 3D Renderer");

	SDL_GL_DeleteContext(context_);

	return ret;
}
//GLuint ModuleRenderer::GetImage()
//{
//	return loadedTexId_;
//}
void ModuleRenderer::SetIdImage(int texID_)
{
	intTex = texID_;
}