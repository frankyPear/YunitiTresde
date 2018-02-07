#pragma once
#include <string>
#include <vector>
#include "Component.h"



class GameObject
{
public:

	//Constructor
	GameObject();

	//Destructor
	virtual ~GameObject();

#pragma region Callbacks

	//OnStart callback
	virtual void OnStart();

	//OnDestroy callback
	virtual void OnDestroy();



#pragma endregion

#pragma region Life cycle methods
public:
	//PreUpdate
	virtual bool PreUpdate();

	//Update
	virtual bool Update();

	//PostUpdate
	virtual bool PostUpdate();

	void Destroy();

#pragma endregion

#pragma region Getters
	unsigned int GetId()const;

	bool GetActive()const;

	bool GetStatic()const;

	std::string GetName()const;

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

	int FindChildIndex(GameObject & gameObject)const;

	GameObject* GetChild(int index)const;

	unsigned int GetChildsCount()const;

	void DetatchChild(int index);

	void DetatchChild(GameObject &child);

	void DetachChildren();

private:
	void OnChildIsDisactived(GameObject &e);

	void OnChildIsActived(GameObject &g);

	void OnChildIsDestroyed(GameObject &g);




#pragma endregion

#pragma region Inspector Methods
public:
	void DrawGameObjectImgUI();
	void DrawComponentImgUI();
#pragma endregion

#pragma region Component Methods
	void AddComponent(Component *component);

	void DestroyComponent(Component &component);

	int FindComponentIndex(Component &component)const;

	void OnComponentIsEnabled(Component &component);

	void OnComponentIsDisabled(Component &component);

	//GetComponent per fer a analitzar tema dels tipus

#pragma endregion

private:
	unsigned int _id;

	bool _isActive = true;

	bool _isStatic = false;

	bool _drawBoundingBox = false;

	bool _removeOnFrameEnd = false;

	unsigned int _disactivedGameObjectsIndex=0, _destroyGameObjectsIndex=0;

	unsigned int _disabledComponentsIndex = 0, _destroyComponentsIndex = 0;

	std::string _name = "Default name";

#pragma region Hierarchy attributes

	std::vector<GameObject*> _childs;
	GameObject * _parent;

#pragma endregion


	std::vector<Component*> _components;





};

