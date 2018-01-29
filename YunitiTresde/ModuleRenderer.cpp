#include "Application.h"
#include "ModuleRenderer.h"
#include "ModuleCamera.h"
#include "ModuleWindow.h"
#include "SDL\include\SDL.h"
#include "Mathgeolib\include\MathGeoLib.h"
#include "imgui-1.53\imgui.h"
#include "imgui-1.53\imgui_impl_sdl_gl3.h"
#include "OpenGL.h"
#include "Quad.h"
#include "Sphere.h"

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
	
	sphere = new SolidSphere(1.0f,20.0f,20.0f);
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
	if (glewInit()!=GLEW_OK)
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
	glEnable(GL_DEPTH_TEST); checkDepthTest_ = true;
	glEnable(GL_CULL_FACE); checkCullFace_ = true;
	glEnable(GL_LIGHTING); checkLightning_ = true;
	glEnable(GL_COLOR_MATERIAL); checkColorMaterial_ = true;
	glEnable(GL_TEXTURE_2D); checkTexture2D_ = true;

	//Set the camera 
	//glOrtho(-5, 5, -5, 5, -5, 5);
	//Implement gluLookAt in a ImGUI
	//gluLookAt(1.0, 0.0, -3.0, 0.0, 5.0, 0.0, 0.0, 1.0, 0.0);

		

	return ret;
}
//Perhaps better to use bool?
void ModuleRenderer::ConfigurationManager()
{
	ImGui::Begin("Render Manager");
	
	if (ImGui::Checkbox("DEPTH TEST", &checkDepthTest_))
	{
		if(checkDepthTest_) glDisable(GL_DEPTH_TEST);
		if (!checkDepthTest_) glEnable(GL_DEPTH_TEST);
	}
	if (ImGui::Checkbox("CULLFACE", &checkCullFace_))
	{
		if (checkCullFace_) glDisable(GL_CULL_FACE);
		if (!checkCullFace_) glEnable(GL_CULL_FACE);
	}
	if (ImGui::Checkbox("LIGHTNING", &checkLightning_))
	{
		if (checkLightning_) glDisable(GL_LIGHTING);
		if (!checkLightning_) glEnable(GL_LIGHTING);
	}
	if (ImGui::Checkbox("COLORMATERIAL", &checkColorMaterial_))
	{
		if (checkColorMaterial_) glDisable(GL_COLOR_MATERIAL);
		if (!checkColorMaterial_) glEnable(GL_COLOR_MATERIAL);
	}
	if (ImGui::Checkbox("TEXTURE 2D", &checkTexture2D_))
	{
		if (checkTexture2D_) glDisable(GL_TEXTURE_2D);
		if (!checkTexture2D_) glEnable(GL_TEXTURE_2D);
	}
	if (ImGui::Button("fog"))
	{

	}
	ImGui::End();
}
bool ModuleRenderer::Start()
{
	return true;
}

update_status ModuleRenderer::PreUpdate(float dt)
{
	//Readapt the render size, once window is resized
	//CAREFUL!! NOW EVERYTHING DEFORMS!
	glViewport(0, 0, App->window->GetWidth(), App->window->GetHeight());

	//Clear the window to draw the next frame
	glClearColor(0, 0, 0, 255);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(App->cam->GetProjectionMatrix());

	//Init Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(App->cam->GetViewMatrix());


	return UPDATE_CONTINUE;
}

update_status ModuleRenderer::Update(float dt)
{
	ConfigurationManager();
	return UPDATE_CONTINUE;
}


update_status ModuleRenderer::PostUpdate(float dt)
{

	
	DrawElementPlane();
	sphere->draw(0.0f,0.0f,0.0f);
	SDL_GL_SwapWindow(App->window->GetWindow());

	return UPDATE_CONTINUE;
}

bool ModuleRenderer::CleanUp() {

	bool ret = true;
	LOG("Destroying 3D Renderer");

	SDL_GL_DeleteContext(context_);

	return ret;
}