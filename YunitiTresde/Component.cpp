#include "Component.h"



Component::Component()
{
}


Component::~Component()
{

}

bool Component::IsEnabled() const
{
	return enabled;
}
void Component::Enable()
{
	if (!enabled) enabled = true;
}
void Component::Disable()
{
	if (enabled) enabled = false;
}
GameObject* Component::LinkedTo() const
{
	return linked_to;
}
Type Component::GetType() const
{
	return type;
}
