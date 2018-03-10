#pragma once
#include "Component.h"
#include <vector>
#include "OpenGL.h"

class ComponentButton :
	public Component
{
public:

	//Constructor

	ComponentButton(GameObject *gameObject);

	//Destructor
	~ComponentButton();

	void SetHover_Focus(unsigned int uid);

	void SetPressed(unsigned int uid);

	void SetEnabled(unsigned int uid);

	void SetColourTransition(unsigned int uid);

	void SetSpriteSwap(unsigned int uid);

private:

};
