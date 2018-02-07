#pragma once

class GameObject;

enum Type {TRANSFORMATION,MATERIAL,MESH,CAMERA};

class Component
{
public:
	Component();
	Component(Type componentType);
	~Component();
	bool IsEnabled() const;
	void Enable();
	void Disable();
	GameObject* LinkedTo() const;
	void SetLinkedTo(GameObject *parent);
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

public:
	bool to_be_destroyed;


protected:
	GameObject * linked_to;
	Type type;
	bool enabled;


};

