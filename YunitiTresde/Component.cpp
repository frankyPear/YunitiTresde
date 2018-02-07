#include "Component.h"

#include "GameObject.h"

Component::Component()
{
	OnStart();
}

Component::Component(Type componentType, GameObject* obj) : _type(componentType), _gameObject(obj), _enabled(true)
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
	if (!_enabled) {
		_enabled = true;
		_gameObject->OnComponentIsEnabled(*this);
	}
}
void Component::Disable()
{
	if (_enabled) {
		_enabled = false;
		_gameObject->OnComponentIsDisabled(*this);
	}
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

}

Component::Type Component::GetType() const
{
	return _type;
}

