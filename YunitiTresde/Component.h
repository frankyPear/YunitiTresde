#pragma once

class GameObject;



class Component
{
public:
	///Component type enum
	enum Type {
		DEFAULT,
		TRANSFORMATION,
		MATERIAL,
		MESH
	};

	///Constructor
	Component();

	//Constructor
	Component(Type componentType, GameObject &obj);

	///Destructor
	virtual ~Component();
	
#pragma region Getters
	bool IsEnabled() const;
	GameObject* GetGameObject() const;
	Type GetType() const;

#pragma endregion

#pragma region Setters
	void Enable();
	void Disable();
#pragma endregion

#pragma region Callbacks
	virtual void OnStart();

	virtual void OnDestroy();


#pragma endregion

#pragma region Life cycle methods


	virtual bool PreUpdate() {
		return true;
	}	

	virtual bool Update() {
		return true;
	}

	virtual bool PostUpdate() {
		return true;
	}

#pragma endregion

	

private:
	Type _type=Type::DEFAULT;
	GameObject *_gameObject=nullptr;
	bool _enabled=true;
};

