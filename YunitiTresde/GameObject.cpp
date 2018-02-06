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

unsigned int GameObject::GetId() const
{
	return _id;
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
	if (parent == nullptr && _parent != nullptr)
		_parent->DetatchChild(*this);
	else if (parent != nullptr && parent!=_parent)
		parent->AddChild(this);
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

unsigned int GameObject::GetChildsCount() const
{
	return _childs.size();
}

void GameObject::DetatchChild(int index)
{
	unsigned int childrenSize = _childs.size();
	if (index >= 0 && index < childrenSize) {
		_childs[index]->_parent = nullptr;
		_childs.erase(_childs.begin() + index);
	}
	
}

void GameObject::DetatchChild(GameObject & child)
{
	unsigned int childrenSize = _childs.size();
	unsigned int selectedIndex = -1;
	for (int i = 0; i < childrenSize; i++) {
		if (&child == _childs[i]) {
			selectedIndex = i;
			break;
		}
	}
	if (selectedIndex != -1) {
		child._parent = nullptr;
		_childs.erase(_childs.begin() + selectedIndex);
		
		
	}

}

void GameObject::DetachChildren()
{
	unsigned int childrenSize = _childs.size();

	for (int i = 0; i < childrenSize; i++)
		_childs[i]->_parent=nullptr;

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
	component->SetGameObject(*this);
	_components.push_back(component);
}

void GameObject::DestroyComponent(Component * component)
{
	unsigned int componentsSize = _components.size();
<<<<<<< HEAD
	int selectedIndex = -1;
	for (int i = 0; i < componentsSize; i++) {
		if (_components[i] == component) {			
			selectedIndex = i;
			break;
=======
	for (std::vector<Component*>::iterator it = _components.begin(); it != _components.end();){
		if ((*it)->to_be_destroyed) {
			(*it)->Destroy();

			delete *it;
			*it = nullptr;
>>>>>>> bb4e78869e77b5c22672cc5e746561eeef439b00
		}
	}
	if (selectedIndex != -1) {
		RELEASE(_components[selectedIndex]);
		_components.erase(_components.begin() + selectedIndex);
	}
}




