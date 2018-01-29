#ifndef _MODULERENDER_
#define _MODULERENDER_


#include "Module.h"
#include "SDL\include\SDL.h"

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

private:
	SDL_GLContext context_;
	SolidSphere *sphere;

	bool checkDepthTest_ = true;
	bool checkCullFace_ = true;
	bool checkLightning_ = true;
	bool checkColorMaterial_ = true;
	bool checkTexture2D_ = true;
	bool checkFog_ = false;
};

#endif // !_RENDER_