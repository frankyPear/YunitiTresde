#pragma once

class GameObject;

enum Type {TRANSFORMATION,MATERIAL,MESH};

class Component
{
public:
	Component();
	Component(Type componentType, GameObject* obj);
	~Component();
	bool IsEnabled() const;
	void Enable();
	void Disable();
<<<<<<< HEAD

	void SetGameObject(GameObject &gameObject);
#pragma endregion

#pragma region Callbacks
	virtual void OnStart();

	virtual void OnDestroy();


#pragma endregion

#pragma region Life cycle methods


=======
	GameObject* LinkedTo() const;
	Type GetType() const;
	
>>>>>>> bb4e78869e77b5c22672cc5e746561eeef439b00
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

public:
	bool to_be_destroyed;


private:

	Type type;
	GameObject *linked_to;
	bool enabled;


};

