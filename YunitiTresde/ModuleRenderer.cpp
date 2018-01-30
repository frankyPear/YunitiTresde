#include "Application.h"
#include "ModuleRenderer.h"
#include "ModuleCamera.h"
#include "ModuleTextures.h"
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
	toggleDepthTest(checkDepthTest_);
	toggleCullFace(checkCullFace_);
	toggleLightning(checkLightning_);
	toggleColorMaterial(checkColorMaterial_);
	toggleTexture2D(checkTexture2D_);
	checkFog_ = false;
	//FOG Config //NEED OPTIMIZATION
	glFogi(GL_FOG_MODE, GL_EXP2);
	glFogf(GL_FOG_START, 1000.0f); 
	fogDensity_ = .1f;
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, fogDensity_);
	glHint(GL_FOG_HINT, GL_NICEST);
	//-----

	

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
		toggleDepthTest(checkDepthTest_);
	}
	if (ImGui::Checkbox("CULLFACE", &checkCullFace_))
	{
		toggleCullFace(checkCullFace_);
	}
	if (ImGui::Checkbox("LIGHTNING", &checkLightning_))
	{
		toggleLightning(checkLightning_);
	}
	if (ImGui::Checkbox("COLORMATERIAL", &checkColorMaterial_))
	{
		toggleColorMaterial(checkColorMaterial_);
	}
	if (ImGui::Checkbox("TEXTURE 2D", &checkTexture2D_))
	{
		toggleTexture2D(checkTexture2D_);
	}
	if (ImGui::CollapsingHeader("Fog"))
	{
		if(ImGui::Checkbox("Enable Fog", &checkFog_)) toggleFog(checkFog_); 
		if (ImGui::SliderFloat("Red", &fogRed_, 0.0f, 1.0f)); SetFogColor();
		if (ImGui::SliderFloat("Blue", &fogGreen_, 0.0f, 1.0f)); SetFogColor();
		if (ImGui::SliderFloat("Green", &fogBlue_, 0.0f, 1.0f)); SetFogColor();
	}
	if (ImGui::CollapsingHeader("Ambient Lightning"))
	{
		if (ImGui::SliderFloat("Red", &ambientRed_, 0.0f, 1.0f)); SetAmbientLightning();
		if (ImGui::SliderFloat("Blue", &ambientBlue_, 0.0f, 1.0f)); SetAmbientLightning();
		if (ImGui::SliderFloat("Green", &ambientGreen_, 0.0f, 1.0f)); SetAmbientLightning();
	}
	//TODO: COLOR PICKER FOR AMBIENT LIGHT
	ImGui::End();
}
void  ModuleRenderer::toggleDepthTest(bool check)
{
	check ? glEnable(GL_DEPTH_TEST): glDisable(GL_DEPTH_TEST);
	check = !check;
}
void  ModuleRenderer::toggleCullFace(bool check)
{
	check ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
	check = !check;
}
void  ModuleRenderer::toggleLightning(bool check)
{
	check ? glEnable(GL_LIGHTING) : glDisable(GL_LIGHTING);
	check = !check;
}
void  ModuleRenderer::toggleColorMaterial(bool check)
{
	check ? glEnable(GL_COLOR_MATERIAL) : glDisable(GL_COLOR_MATERIAL);
	check = !check;
}
void  ModuleRenderer::toggleTexture2D(bool check)
{
	check ? glEnable(GL_TEXTURE_2D) : glDisable(GL_TEXTURE_2D);
	check = !check;
}
void  ModuleRenderer::toggleFog(bool check)
{
	check ? glEnable(GL_FOG) : glDisable(GL_FOG);
	check = !check;
}
void ModuleRenderer::SetFogColor()
{
	GLfloat fogColor_[4] = { fogRed_,fogGreen_,fogBlue_, 1.0f };
	glFogfv(GL_FOG_COLOR, fogColor_);
}
void ModuleRenderer::SetAmbientLightning()
{
	GLfloat ambientLight[4] = { ambientRed_,ambientGreen_, ambientBlue_, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
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

update_status ModuleRenderer::Update(float dt)
{
	ConfigurationManager();
	return UPDATE_CONTINUE;
}


update_status ModuleRenderer::PostUpdate(float dt)
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