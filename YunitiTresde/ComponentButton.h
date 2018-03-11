#pragma once
#include "Component.h"
#include <vector>
#include "OpenGL.h"
#include "SDL\include\SDL.h"

class ComponentButton :
	public Component
{
public:

	//Constructor

	ComponentButton(int x, int y,int sizex, int sizey, bool visible);

	//Destructor
	~ComponentButton();

	void SetHover_Focus(unsigned int uid);

	void SetPressed(unsigned int uid);

	void SetEnabled(unsigned int uid);

	void SetColourTransition(unsigned int uid);

	void SetSpriteSwap(unsigned int uid);

public:
	SDL_Rect rect;
	bool visible;

};
