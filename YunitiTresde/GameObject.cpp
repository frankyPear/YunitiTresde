#include "GameObject.h"
#include "Globals.h"
GameObject::GameObject()
{
	//Do anything it should
	OnStart();
}


GameObject::~GameObject()
{

	unsigned int componentsSize = _components.size();
	int *d;
	
	for (unsigned int i = 0; i < componentsSize; i++) 
		RELEASE(_components[i]);
	
	_components.clear();

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
	return true;
}

bool GameObject::Update()
{
	for (std::vector<Component*>::iterator it = _components.begin(); it != _components.end();) {
			(*it)->Update();		
	}
	for (std::vector<GameObject*>::iterator it = _childs.begin(); it != _childs.end();) {
		(*it)->Update();
	}
	return true;
}

bool GameObject::PostUpdate()
{

	for (std::vector<Component*>::iterator it = _components.begin(); it != _components.end();) {
		if ((*it)->to_be_destroyed) {
			(*it)->Destroy();
			delete *it;
			*it = nullptr;
			it = _components.erase(it);
		}

		else {
			(*it)->PostUpdate();
		}
	}
	for (std::vector<GameObject*>::iterator it = _childs.begin(); it != _childs.end();) {
		(*it)->PostUpdate();
	}
	return true;
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

void GameObject::SetParent(GameObject  * parent)
{
	_parent = parent;
}

void GameObject::AddChild(GameObject * child)
{
	_childs.push_back(child);
}

GameObject*  GameObject::GetChild(int index) const
{
	if (index < 0 || index >= _childs.size())
		throw "Index of childs out of range";


	return _childs[index];
}

void GameObject::DetatchChild(int index)
{
}

void GameObject::DetachChildren()
{
	unsigned int childrenSize = _childs.size();

	for (int i = 0; i < childrenSize; i++)
		_childs[i]->SetParent(nullptr);

	_childs.clear();
}

void GameObject::DrawGameObjectImgUI() {
	// Mirar que no sigui el root, renderitzar al imgui les propietats
	// Si ho es cridar per cada fill la seva funcio de DrawGameObjectImgUI
}


void GameObject::DrawComponentImgUI()
{
	for (int i = 0; i < _components.size(); ++i) {
		//_components[i]->DisplayImgUINode();
	}
}

void GameObject::AddComponent(Component * component)
{
	_components.push_back(component);
}

void GameObject::DestroyComponent(Component * component)
{
	unsigned int componentsSize = _components.size();
	for (std::vector<Component*>::iterator it = _components.begin(); it != _components.end();){
		if ((*it)->to_be_destroyed) {
			(*it)->Destroy();

			delete *it;
			*it = nullptr;
		}

	}
}




