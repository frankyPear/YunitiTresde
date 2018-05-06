#include "Component2D.h"

Component2D::Component2D(GameObject * objParent, int x, int y, int h, int w)
{
	gameObject = objParent;
	rectangle.x = x;
	rectangle.y = y;
	rectangle.h = h;
	rectangle.w = w;
}

Component2D::~Component2D()
{
}