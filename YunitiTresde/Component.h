#pragma once

class GameObject;

enum Type {TRANSFORMATION,MATERIAL,MESH};

class Component
{
public:
	Component();
	~Component();
	bool IsEnabled() const;
	void Enable();
	void Disable();
	GameObject* LinkedTo() const;
	Type GetType() const;
	
	virtual bool PreUpdate() {}	
	virtual bool Update() {}
	virtual bool PostUpdate() {}
	virtual bool Destroy() {}


private:

	Type type;
	GameObject *linked_to;
	bool enabled;
};

