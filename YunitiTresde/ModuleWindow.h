#ifndef _MODULEWINDOW_
#define _MODULEWINDOW_

#include "Module.h"
#include "SDL\include\SDL.h"

class ModuleWindow :
	public Module
{
public:

	ModuleWindow();
	~ModuleWindow();

	SDL_Window* GetWindow() const;
	int GetHeight();
	int GetWidth();
	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();
	


private:

	SDL_Surface* screen_surface_ = nullptr;
	SDL_Window* window_ = nullptr;
	SDL_Event event_;

	int height_;
	int width_;
	int* h = nullptr;
    int *w = nullptr;

};

#endif // !_MODULEWINDOW_