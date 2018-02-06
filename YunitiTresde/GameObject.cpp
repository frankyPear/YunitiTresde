#include "GameObject.h"
#include "Globals.h"
#include "ModuleImGui.h"
GameObject::GameObject()
{
	//Do anything it should
	OnStart();
}


GameObject::~GameObject()
{
	unsigned int componentsSize = _components.size();

	for (unsigned int i = 0; i < componentsSize; i++)
		RELEASE(_components[i]);

	_components.clear();

	OnDestroy();
	OnChildIsDestroyed(*this);
}

void GameObject::OnStart()
{
}

void GameObject::OnDestroy()
{
}

void GameObject::OnChildIsDisactived(GameObject &g)
{
	//Swap to disactiveblock
	int index = FindChildIndex(g);
	if (index != -1) {
		if (index != (_disactivedGameObjectsIndex - 1)) {
			GameObject *aux = _childs[_disactivedGameObjectsIndex - 1];
			_childs[_disactivedGameObjectsIndex - 1] = &g;
			_childs[index] = aux;
		}
		_disactivedGameObjectsIndex--;
	}
}



void GameObject::OnChildIsDestroyed(GameObject & g)
{
	int index = FindChildIndex(g);
	if (index != -1) {
		if (index < _disabledComponentsIndex) {//Destroy an activeObject
			if (index != (_disabledComponentsIndex - 1)) 
				_childs[index] = _childs[_disabledComponentsIndex - 1];
			if(_disabledComponentsIndex!=_destroyComponentsIndex)
			_childs[_disabledComponentsIndex-1]=_childs[_destroyComponentsIndex-1];

		}
		else if (index < _destroyComponentsIndex) {//Destroy an disactiveObject
			if (index != (_destroyComponentsIndex - 1)) {
				GameObject *aux = _childs[index];
				_childs[index] = _childs[_destroyComponentsIndex - 1];
				_childs[_destroyComponentsIndex - 1] = aux;
			}

		}
		_childs[_destroyComponentsIndex - 1] = &g;
		_destroyComponentsIndex--;
		_disabledComponentsIndex--;


	}



}

void GameObject::OnChildIsActived(GameObject &g)
{
	int index = FindChildIndex(g);
	if (index != -1) {
		if (index != (_disactivedGameObjectsIndex)) {
			GameObject *aux = _childs[_disactivedGameObjectsIndex];
			_childs[_disactivedGameObjectsIndex] = &g;
			_childs[index] = aux;
		}
		_disactivedGameObjectsIndex++;
	}
}

bool GameObject::PreUpdate()
{
	for (int i = 0; i < _disactivedGameObjectsIndex; i++)
		_childs[i]->PreUpdate();


	for (int i = 0; i < _disabledComponentsIndex; i++)
		_components[i]->PreUpdate();
	return true;

}

bool GameObject::Update()
{
	for (int i = 0; i < _disactivedGameObjectsIndex; i++)
		_childs[i]->Update();

	for (int i = 0; i < _disabledComponentsIndex; i++)
		_components[i]->Update();

	return true;
}

bool GameObject::PostUpdate()
{
	for (int i = 0; i < _disactivedGameObjectsIndex; i++)
		_childs[i]->PostUpdate();


	for (int i = 0; i < _disabledComponentsIndex; i++)
		_components[i]->PostUpdate();

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
	if (_isActive == b)
		return;
	if (_parent != nullptr) {
		if (b)
			_parent->OnChildIsActived(*this);
		else
			_parent->OnChildIsDisactived(*this);
	}

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
	if (_parent == parent)
		return;

	if (_parent != nullptr)
		_parent->DetatchChild(*this);

	if (parent != nullptr)
		parent->AddChild(this);
	else
		_parent = nullptr;

}

void GameObject::AddChild(GameObject * child)
{
	_childs.push_back(nullptr);
	unsigned int childsSize = _childs.size();
	//Swapping
	if (_destroyComponentsIndex == _disactivedGameObjectsIndex) {
		_childs[childsSize - 1] = _childs[_disactivedGameObjectsIndex];
	}
	else {
		_childs[childsSize - 1] = _childs[_destroyComponentsIndex];
		_childs[_destroyComponentsIndex] = _childs[_disactivedGameObjectsIndex];
	}

	_childs[_disactivedGameObjectsIndex] = child;
	_destroyGameObjectsIndex++;
	_disactivedGameObjectsIndex++;
	child->_parent = this;
}

int GameObject::FindChildIndex(GameObject & gameObject) const
{
	int selectedIndex = -1;
	unsigned int childrenSize = _childs.size();
	for (int i = 0; i < childrenSize; i++) {
		if (&gameObject == _childs[i]) {
			selectedIndex = i;
			break;
		}
	}

	return selectedIndex;
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
	unsigned int selectedIndex = FindChildIndex(child);
	if (selectedIndex != -1) {
		_childs.erase(_childs.begin() + selectedIndex);
		child._parent = nullptr;
	}

}

void GameObject::DetachChildren()
{
	unsigned int childrenSize = _childs.size();

	for (int i = 0; i < childrenSize; i++)
		_childs[i]->_parent = nullptr;

	_childs.clear();
}

void GameObject::DrawGameObjectImgUI() {
	// Mirar que no sigui el root, renderitzar al imgui les propietats
	// Si ho es cridar per cada fill la seva funcio de DrawGameObjectImgUI
	ImGui::Checkbox("##object_active", &_isActive);

	ImGui::SameLine();

	ImGui::SameLine();

	//Static Object
	if (ImGui::Checkbox("Static##object_static", &_isStatic))
		SetStatic(_isStatic);

	//Bounding box
	ImGui::Checkbox("Bounding Box", &_drawBoundingBox);

	//Components inspectors
	uint size = _components.size();
	for (uint k = 0; k < size; k++)
	{
		//Show component inspector data
		_components[k]->DisplayImgUINode();
	}

	//Components factory
	ImGui::Separator();


	/*if (App->scene->GetComponentsWinState())
	{
		App->scene->BlitComponentsWindow(this);
	}*/

	//Add a margin to scroll
	ImGui::NewLine(); ImGui::NewLine(); ImGui::NewLine(); ImGui::NewLine();
}


void GameObject::DrawComponentImgUI()
{
}

void GameObject::AddComponent(Component * component)
{
	component->SetGameObject(*this);
	_components.push_back(component);
}

void GameObject::DestroyComponent(Component * component)
{
	unsigned int componentsSize = _components.size();
	int selectedIndex = -1;
	for (int i = 0; i < componentsSize; i++) {
		if (_components[i] == component) {
			selectedIndex = i;
			break;
		}
	}
	if (selectedIndex != -1) {
		RELEASE(_components[selectedIndex]);
		_components.erase(_components.begin() + selectedIndex);
	}
}




