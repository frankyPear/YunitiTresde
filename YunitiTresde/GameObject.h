#pragma once
#include <string>
#include <vector>
#include "Component.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"

#include "Mathgeolib\include\Geometry\AABB.h"

class GameObject
{
public:
	///Constructor
	GameObject();

	//Destructor
	virtual ~GameObject();

#pragma region Callbacks
	//OnStart callback
	virtual void OnStart();

	///OnDestroy callback
	virtual void OnDestroy();
#pragma endregion

#pragma region Life cycle methods

	///PreUpdate
	virtual bool PreUpdate();

	virtual bool Update();

	///PostUpdate
	virtual bool PostUpdate();

#pragma endregion

#pragma region Getters
	bool GetActive()const;

	bool GetStatic()const;

	std::string GetName()const;

	std::vector<GameObject*> GetChilds() const;

#pragma endregion

#pragma region Setters
	void SetActive(bool b);

	void SetStatic(bool b);

	void SetName(const char *name);

#pragma endregion

#pragma region Hierarchy methods

	GameObject* GetParent()const;

	void SetParent(GameObject  * parent);

	void AddChild(GameObject *child);

	GameObject* GetChild(int index)const;

	void DetatchChild(int index);

	void DetachChildren();

#pragma endregion

#pragma region Render Methods
	void DrawGameObjectImgUI();
	void DrawComponentImgUI();
#pragma endregion

#pragma region Component Methods
	void AddComponent(Component *component);

	void DestroyComponent(Component *component);

	Component* GetComponent(Type t);

	void ChildrenTransformUpdate();

	void DrawObjectAndChilds();

	void GetAxisBB();

	bool CheckRayIntersection(Ray r, float &distance);

	unsigned int GetId();

	void SetId(unsigned int newId);

	AABB axisBoundingBox_;
#pragma endregion
public:
	//to be changed to private //shall be static?
 bool isSelected = false;

private:
	unsigned int _id;

	bool _isActive = true;

	bool _isStatic = false;

	std::string _name = "Default name";

#pragma region Hierarchy attributes

	std::vector<GameObject*> _childs;
	GameObject * _parent;


#pragma endregion

	std::vector<Component*> _components;








};

