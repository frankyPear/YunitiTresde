#pragma once
#include "Module.h"
#include <string>
#include "GameObject.h"
#include "Component2DTransform.h"
#include "SDL\include\SDL_rect.h"
class Component2D
{
public:
	Component2D(GameObject* obj, int x, int y, int h, int w);
	~Component2D();

public:
	SDL_Rect rectangle;
	GameObject* gameObject = nullptr;

};