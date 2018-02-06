#include "Component.h"



Component::Component()
{
}

Component::Component(Type componentType, GameObject* obj) : type(componentType), linked_to(obj), enabled(true), to_be_destroyed(false)
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
<<<<<<< HEAD
	if (_enabled) _enabled = false;
}
void Component::SetGameObject(GameObject & gameObject)
{
	_gameObject = &gameObject;
}
void Component::OnStart()
{
}
void Component::OnDestroy()
{
=======
	if (enabled) enabled = false;
>>>>>>> bb4e78869e77b5c22672cc5e746561eeef439b00
}
GameObject* Component::LinkedTo() const
{
	return linked_to;
}
Type Component::GetType() const
{
	return type;
}

