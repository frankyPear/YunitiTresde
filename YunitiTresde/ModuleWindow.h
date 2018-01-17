#pragma once
#include "Module.h"
#include "SDL\include\SDL.h"

class ModuleWindow :
	public Module
{
public:
	ModuleWindow();
	~ModuleWindow();

	SDL_Window* GetWindow() const;
	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();

private:
	SDL_Window* window_ = nullptr;
	SDL_Surface* screen_surface_ = nullptr;

};

