#include "ModuleWindow.h"
#include "SDL\include\SDL.h"
#include "imgui-1.53\imgui.h"
#include "imgui-1.53\imgui_impl_sdl_gl3.h"


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
		flags_ |= SDL_WINDOW_OPENGL;
		flags_ |= SDL_WINDOW_SHOWN;
		flags_ |= SDL_WINDOW_RESIZABLE;
		//Window can resize
		window_ = SDL_CreateWindow("YunitiTresDe", SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED, width_, height_, flags_ );
		if (window_ == nullptr)
		{
			LOG("Failed to create window! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}

		//screen_surface not needed yet
		screen_surface_ = SDL_GetWindowSurface(window_);
	}

	//Get the screen size
	SDL_GetCurrentDisplayMode(0, &display_);
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
	//int temp_w = width_;
	
	//if (temp_w != width_)
	//{
	//	LOG("Width has changed");
	//}

	//int temp_h = height_;

	//if (temp_w != width_)
	//{
	//	LOG("Height has changed");
	//}
	
	WindowImGui();
	
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
	SDL_SetWindowSize(window_, width_, height_);
	height_ = GetHeight();
	
}
void ModuleWindow::SetWindowWidth(int width)
{
	width_ = width;
	SDL_SetWindowSize(window_, width_, height_);
	width_ = GetWidth();
}

void ModuleWindow::WindowImGui()
{
	ImGui::Begin("Window");
	static bool check1 = true;
	if (ImGui::Checkbox("Shown", &check1))
	{
		flags_ |= SDL_WINDOW_SHOWN;
		check1 = true;
	}
	static bool check2 = false;
	if (ImGui::Checkbox("FullScreen", &check2))
	{
		if (check2)
		{
			flags_ |= SDL_WINDOW_FULLSCREEN_DESKTOP;
			SDL_SetWindowFullscreen(window_, flags_);
			height_ = GetHeight();
			width_ = GetWidth();
			
		}
		if (!check2)
		{
			flags_ &= ~SDL_WINDOW_FULLSCREEN_DESKTOP;
			SDL_SetWindowFullscreen(window_, flags_);
		}
	}
	static bool check3 = false;
	if (ImGui::Checkbox("Borderless", &check3))
	{	
		if(!check3) SDL_SetWindowBordered(window_, SDL_TRUE);
		if(check3) SDL_SetWindowBordered(window_, SDL_FALSE);
	}
	int tempHeight = 0;
	if (ImGui::SliderInt("Width", &width_, 100, display_.w))
	{
		
		tempHeight = (width_ - SCREEN_WIDTH) * (9 / 16);
		SetWindowWidth(width_);
		SetWindowHeight(tempHeight);
	}
	if (ImGui::SliderInt("Height", &height_, 100, display_.h))
	{
		SetWindowWidth(width_);
	}
	ImGui::End();
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