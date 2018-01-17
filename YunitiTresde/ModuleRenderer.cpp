#include "Application.h"
#include "ModuleRenderer.h"
#include "ModuleWindow.h"
#include "SDL\include\SDL.h"
#include "OpenGL.h"

#pragma comment (lib, "SDL/libx86/SDL2.lib")
#pragma comment (lib, "SDL/libx86/SDL2main.lib")
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")
#pragma comment (lib, "Glew/libx86/glew32.lib")

ModuleRenderer::ModuleRenderer()
{
}


ModuleRenderer::~ModuleRenderer()
{
}

bool ModuleRenderer::Init() {
	bool ret = true;

	//Set Attributes (NOTE DOWN WHAT IT MEANS EACH LINE!)
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	
	//Create context
	context_ = SDL_GL_CreateContext(App->window->GetWindow());

	if (context_ == NULL)
	{
		LOG("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
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

	}

	return ret;
}

bool ModuleRenderer::Start()
{
	return true;
}

update_status ModuleRenderer::PreUpdate()
{
	/*Color c = cam->background;
	glClearColor(, c.g, c.b, c.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(cam->GetOpenGLViewMatrix())*/

	return UPDATE_CONTINUE;
}

update_status ModuleRenderer::Update()
{
	return UPDATE_CONTINUE;
}


update_status ModuleRenderer::PostUpdate()
{
	SDL_GL_SwapWindow(App->window->GetWindow());
	return UPDATE_CONTINUE;
}

bool ModuleRenderer::CleanUp() {
	return true;
}