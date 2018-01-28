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

	bool CleanUp();


private:

	SDL_GLContext context_;
	
	SolidSphere *sphere;
};

#endif // !_RENDER_