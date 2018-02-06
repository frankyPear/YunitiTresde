#pragma once
#include <string>
#include <vector>
#include "Component.h"



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

<<<<<<< HEAD
	///PostUpdatee
=======
	virtual bool Update();

	///PostUpdate
>>>>>>> bb4e78869e77b5c22672cc5e746561eeef439b00
	virtual bool PostUpdate();

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

	GameObject* GetChild(int index)const;

	unsigned int GetChildsCount()const;

	void DetatchChild(int index);

	void DetatchChild(GameObject &child);

	void DetachChildren();



#pragma endregion

#pragma region Render Methods
	void DrawGameObjectImgUI();
	void DrawComponentImgUI();
#pragma endregion

#pragma region Component Methods
	void AddComponent(Component *component);

	void DestroyComponent(Component *component);

	//GetComponent per fer a analitzar tema dels tipus

#pragma endregion

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

