#pragma once
#include "Component.h"
#include <vector>
#include "OpenGL.h"

class ComponentLabel :
	public Component
{
public:

	//Constructor

	ComponentLabel(GameObject* obj, int x, int y, int sizex, int sizey);
	//Destructor
	~ComponentLabel();

	void SetHover_Focus(unsigned int uid);

	void SetPressed(unsigned int uid);

	void SetEnabled(unsigned int uid);

	void SetColourTransition(unsigned int uid);

	void SetSpriteSwap(unsigned int uid);

	void SetColour(unsigned int uid);

	void SetSize(unsigned int uid);

	void SetFont(unsigned int uid);

private:

};
