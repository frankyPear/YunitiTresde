#include "Component.h"


Component::Component()
{
}

Component::Component(Type componentType) : type(componentType),  enabled(true), to_be_destroyed(false), component_id(App->rng->GetRandomNumber())
{
}

Component::Component(GameObject * gameObject, Type componentType) : type(componentType), enabled(true), to_be_destroyed(false), linked_to(false), component_id(App->rng->GetRandomNumber())
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

void Component::SetLinkedTo(GameObject *parent)
{
	linked_to = parent;
}