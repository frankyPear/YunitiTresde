#ifndef _MODULERENDER_
#define _MODULERENDER_


#include "Module.h"
#include "SDL\include\SDL.h"
#include "OpenGL.h"

class SolidSphere;

class Color 
{

public:
	Color(int r, int g, int b, int a):
		r_(r),g_(g), b_(b), a_(a)
	{}

private:
		int r_, g_, b_, a_;
};


class ModuleRenderer :
	public Module
{
public:
	ModuleRenderer();
	~ModuleRenderer();

	bool Init();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();

	bool CleanUp();

	void toggleDepthTest();
	void toggleCullface();
	void toggleLightning();
	void toggleColorMaterial();
	void toggleTexture();
	void toggleFog();
	void togglelWireframe();

	/*
		glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	*/

private:

	SDL_GLContext context_;
	GLuint loadedTexId;
	SolidSphere *sphere;

	bool depthTestEnabled, cullFaceEnabled,
		lightningEnabled, colorMaterialEnabled,
		textureEnabled, fogEnabled;
	bool wireframeEnabled;
};

#endif // !_RENDER_