#ifndef _MODULERENDER_
#define _MODULERENDER_


#include "Module.h"
#include "SDL\include\SDL.h"
#include "OpenGL.h"

#include "ComponentMesh.h"


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
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	void ConfigurationManager();
	bool CleanUp();
	void toggleDepthTest(bool check = true);
	void toggleCullFace(bool check = true);
	void toggleLightning(bool check = true);
	void toggleColorMaterial(bool check = true);
	void toggleTexture2D(bool check = true);
	void toggleFog(bool check = true);
	void SetFogColor();
	void SetAmbientLightning();
	void SetIdImage(int texID_);
	void Draw(ComponentMesh *cm);

private:
	SDL_GLContext context_;
	ComponentMesh *cm = nullptr;

	bool checkDepthTest_ = true;
	bool checkCullFace_ = true;
	bool checkLightning_ = true;
	bool checkColorMaterial_ = true;
	bool checkTexture2D_ = true;
	bool checkFog_ = false;
	float fogDensity_ = 0.3f;
	float fogColor[4] = { 0.5f,0.5f,0.5f,1.0f };
	float fogRed_;
	float fogBlue_;
	float fogGreen_;
	//Perhaps init them at init() Discuse with the team--
	float ambientRed_ = 0.5f;
	float ambientBlue_ = 0.5f;
	float ambientGreen_ = 0.5f;
	GLuint loadedTexId_;
	int intTex = -1;
};

#endif // !_RENDER_