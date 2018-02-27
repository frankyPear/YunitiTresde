#include "GameObject.h"
#include "Globals.h"
#include "ModuleRenderer.h"
#include "Application.h"
#include "ModuleScene.h"
#include "Brofiler\include\Brofiler.h"
#include "ComponentMesh.h"

GameObject::GameObject()
{
	//Do anything it should
	OnStart();
}


GameObject::~GameObject()
{
	//ADDED IN ON DESTROY
	/*unsigned int componentsSize = _components.size();
	int *d;

	for (unsigned int i = 0; i < componentsSize; i++)
		RELEASE(_components[i]);

	_components.clear();*/

	//---
	App->scene->OnSceneObjectIsDestroyed(this);
	OnDestroy();
}

void GameObject::OnStart()
{
	//Seting BB starting values
	axisBoundingBox_.SetNegativeInfinity();
	ComponentMesh* cm = (ComponentMesh*)this->GetComponent(MESH);
	if (cm != nullptr)
	{
		//axisBoundingBox_.Enclose((float3*)cm->GetMeshVertices(), 8);
	}
}

void GameObject::OnDestroy()
{
	unsigned int componentsSize = _components.size();

	for (unsigned int i = 0; i < componentsSize; i++)
		RELEASE(_components[i]);

	_components.clear();
}

bool GameObject::PreUpdate()
{
	return true;
}

bool GameObject::Update()
{
	BROFILER_CATEGORY("ComponentTransform Update", Profiler::Color::Azure);
	for (std::vector<Component*>::iterator it = _components.begin(); it != _components.end();++it) {
		(*it)->Update();
	}
	for (std::vector<GameObject*>::iterator it = _childs.begin(); it != _childs.end();++it) {
		(*it)->Update();
	}
	return true;
}

bool GameObject::PostUpdate()
{
	for (std::vector<Component*>::iterator it = _components.begin(); it != _components.end();) {
		if ((*it)->to_be_destroyed) {
			Component *toDestroy = *it;
			it = _components.erase(it);
			toDestroy->Destroy();
			delete toDestroy;
		}
		else {
			(*it)->PostUpdate();
			++it;
		}
	}
	for (std::vector<GameObject*>::iterator it = _childs.begin(); it != _childs.end();) {
		if ((*it)->_toBeDestroyed) {
			
			GameObject *toDestroy = *it;
			toDestroy->SetParent(nullptr);
			it = _childs.erase(it);
			toDestroy->Destroy();
			delete toDestroy;
		}
		else {
			(*it)->PostUpdate();
			++it;
		}
	}
	return true;
}

void GameObject::Destroy()
{
	_toBeDestroyed = true;
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

std::vector<GameObject*> GameObject::GetChilds() const
{
	return _childs;
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
	if (parent == nullptr && _parent!=nullptr) 
		_parent->DetatchChild(this);	
	else {


	}
}

void GameObject::AddChild(GameObject * child)
{
	_childs.push_back(child);
	child->SetParent(this);
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

void GameObject::DetatchChild(GameObject * gameObject)
{
	std::vector<GameObject*>::iterator child=_childs.end();
	
	for (std::vector<GameObject*>::iterator it = _childs.begin(); it != _childs.end(); ++it) {
		if ((*it) == gameObject) {
			child = it;
			break;
		}
	}
		
	if (child !=_childs.end()) 
		_childs.erase(child);
	

	gameObject->_parent = nullptr;
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
	component->SetLinkedTo(this);
	if (component->GetType() == MESH)	_meshes.push_back((ComponentMesh*)component);
}

void GameObject::DestroyComponent(Component * component)
{
	component->to_be_destroyed = true;
}

Component* GameObject::GetComponent(Type t)
{
	for (int i = 0; i < _components.size(); ++i)
	{
		if (_components[i]->GetType() == t) {
			return _components[i];
		}
	}
	return nullptr;
}

void GameObject::ChildrenTransformUpdate()
{
	for (int i = 0; i < _childs.size(); ++i)
	{
		ComponentTransform *childTransform = (ComponentTransform*)_childs[i]->GetComponent(TRANSFORMATION);
		if (childTransform != nullptr) {
			childTransform->UpdateTransform();
			_childs[i]->ChildrenTransformUpdate();
		}
	}
}

void GameObject::DrawObjectAndChilds()
{
	App->renderer->Draw(this);

	for (int i = 0; i < _childs.size(); ++i) _childs[i]->DrawObjectAndChilds();
}


bool GameObject::CheckRayIntersection(Ray r, float &distance)
{
	ComponentMesh *cm = (ComponentMesh *)GetComponent(MESH);
	ComponentTransform* ct = (ComponentTransform*)GetComponent(TRANSFORMATION);
	if (cm != nullptr && ct != nullptr) {
		AABB newBox = *(cm->GetBoundingBox());
		newBox.TransformAsAABB(ct->GetGlobalTransform());
		r.Transform(ct->GetGlobalTransform().Inverted());
		if (cm->CheckRayIntersectsMesh(r, distance)) return true;
	}
	return false;
}


unsigned int GameObject::GetId()
{
	return _id;
}

void GameObject::SetId(unsigned int newId)
{
	_id = newId;
}

std::vector<ComponentMesh*> GameObject::GetMeshes()
{
	return _meshes;
}