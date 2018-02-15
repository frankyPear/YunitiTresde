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
	const int& GetHeight() const;
	const int& GetWidth() const;
	void SetWindowHeight(const int& height);
	void SetWindowWidth(const int& width);
	void WindowImGui();
	bool Init();
	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	
	

private:

	SDL_Surface* screen_surface_ = nullptr;
	SDL_Window* window_ = nullptr;
	SDL_Event* event_;
	SDL_DisplayMode DM;
	int height_;
	int width_;
	int* h = nullptr;
    int* w = nullptr;
	Uint32 flags_;
	SDL_DisplayMode display_;
	float brightness_;
	
};

#endif // !_MODULEWINDOW_