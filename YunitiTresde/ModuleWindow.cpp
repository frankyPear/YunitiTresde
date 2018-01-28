#include "ModuleWindow.h"
#include "SDL\include\SDL.h"


ModuleWindow::ModuleWindow()
{
	height_ = SCREEN_HEIGHT*SCREEN_SIZE;
	width_ = SCREEN_WIDTH*SCREEN_SIZE;

}


ModuleWindow::~ModuleWindow()
{
}

bool ModuleWindow::Init() {
	bool ret = true;
	LOG("Init SDL window & surface");

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Window can resize
		window_ = SDL_CreateWindow("YunitiTresDe", SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED, width_, height_, SDL_WINDOW_OPENGL |SDL_WINDOW_SHOWN| SDL_WINDOW_RESIZABLE );
		if (window_ == nullptr)
		{
			LOG("Failed to create window! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}

		//screen_surface not needed yet
		screen_surface_ = SDL_GetWindowSurface(window_);
	}

	return ret;
}

SDL_Window* ModuleWindow::GetWindow() const
{
	return window_;
}

bool ModuleWindow::Start() {
	return true;
}



update_status ModuleWindow::Update(float dt) {
	
	//Check if size has changed
	int temp_w = width_;
	width_ = GetWidth();
	if (temp_w != width_)
	{
		LOG("Width has changed");
	}

	int temp_h = height_;
	height_ = GetHeight();
	if (temp_w != width_)
	{
		LOG("Height has changed");
	}
		
	
	return UPDATE_CONTINUE;
}

int ModuleWindow::GetWidth()
{
	
	return SDL_GetWindowSurface(window_)->w;
}

int ModuleWindow::GetHeight()
{
	return SDL_GetWindowSurface(window_)->h;
}

void ModuleWindow::SetWindowHeight(int height)
{
	height_ = height;
}
void ModuleWindow::SetWindowWidth(int width)
{
	width_ = width;
}

bool ModuleWindow::CleanUp() {
	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if (window_ != nullptr)
	{
		SDL_DestroyWindow(window_);
	}
	//Quit SDL subsystems
	SDL_Quit();
	return true;
}