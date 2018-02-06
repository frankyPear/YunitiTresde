#pragma once

class GameObject;


class Component
{
public:
	//Enum for component
	enum Type {
		TRANSFORMATION,
		MATERIAL,
		MESH 
	};

	Component();

	Component(Type componentType, GameObject* obj);

	virtual ~Component();
#pragma region Getters

	bool IsEnabled() const;

	Type GetType()const;
#pragma endregion
	void Enable();

	void Disable();

	void SetGameObject(GameObject &gameObject);

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

	virtual bool Destroy() {
		return true;
	}

	virtual bool DisplayImgUINode(){
		return true;
	}

#pragma endregion

private:
	Type _type;	//Component Type

	GameObject *_gameObject;//Attached GameObject

	bool _enabled;//Is enabled


};

