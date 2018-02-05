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
	GameObject* LinkedTo() const;
	Type GetType() const;
	
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

private:

	Type type;
	GameObject *linked_to;
	bool enabled;

protected:

	bool to_be_destroyed;
};

