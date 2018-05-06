#pragma once
#include "Component.h"
#include <vector>
#include "OpenGL.h"

class ComponentInput2D :
	public Component
{
public:

	//Constructor

	ComponentInput2D(GameObject* obj, int x, int y, int sizex, int sizey);
	//Destructor
	~ComponentInput2D();

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