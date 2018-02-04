#include "Component.h"



Component::Component()
{

	OnStart();
}

Component::Component(Type componentType, GameObject& obj): _type(componentType), _gameObject(&obj), _enabled(true)
{

	OnStart();
}


Component::~Component()
{

	OnDestroy();

}

bool Component::IsEnabled() const
{
	return _enabled;
}
void Component::Enable()
{
	if (!_enabled) _enabled = true;
}
void Component::Disable()
{
	if (_enabled) _enabled = false;
}
void Component::OnStart()
{
}
void Component::OnDestroy()
{
}
GameObject* Component::GetGameObject() const
{
	return _gameObject;
}
Component::Type Component::GetType() const
{
	return _type;
}
