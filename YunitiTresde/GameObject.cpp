#include "GameObject.h"

GameObject::GameObject()
{
	//Do anything it should
	OnStart();
}


GameObject::~GameObject()
{

	//Do anything it should
	OnDestroy();
}

void GameObject::OnStart()
{
}

void GameObject::OnDestroy()
{

}

bool GameObject::PreUpdate()
{
	return false;
}

bool GameObject::PostUpdate()
{
	return false;
}

bool GameObject::GetActive() const
{
	return _isActive;
}

bool GameObject::GetStatic() const
{
	return _isStatic;
}

std::string GameObject::GetName() const
{
	return _name;
}

void GameObject::SetActive(bool b)
{
	_isActive = b;
}

void GameObject::SetStatic(bool b)
{
	_isStatic = b;
}

void GameObject::SetName(const char * name)
{
	_name = name;
}

GameObject* GameObject::GetParent() const
{
	return _parent;
}

void GameObject::SetParent(GameObject & parent)
{	
	_parent = &parent;
}

void GameObject::AddChild(GameObject & child)
{
	_childs.push_back(&child);
}

GameObject*  GameObject::GetChild(int index) const
{
	if (index < 0 || index >= _childs.size()) 
		throw "Index of childs out of range";
	

	return _childs[index];
}

void GameObject::AddComponent(Component & component)
{
	_components.push_back(&component);
}




