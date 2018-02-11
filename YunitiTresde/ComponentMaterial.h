#pragma once
#include "Component.h"
#include <vector>
#include "OpenGL.h"
#include "ComponentWithResource.h"

class ComponentMaterial :
	public Component, public ComponentWithResource
{
public:

	//Constructor

	ComponentMaterial(GameObject *gameObject);

	//Destructor
	~ComponentMaterial();

	bool SetResource(uid resourceId)override;
	
	void AddMaterialResource(unsigned int uid);

	void OnEditor();


private:

};

//class ComponentMaterial : public Component, public ComponentWithResource
//{
//public:
//
//	//Constructor
//
//	ComponentMaterial();
//
//	~ComponentMaterial();
//	ComponentMaterial(GameObject *gameObject);
//	ComponentMaterial(GLuint loadIdTexture);
////	bool SetResource(uid resourceId)override;
//
//	void AddMaterialResource(unsigned int uid);
//	bool SetResource(uid resourceId)override;
//
//	void OnEditor();
//
//	std::vector<GLint> materialtexture;
//	std::vector<GLint> GetMaterialTexture() const;
//
//	//TextureMaterial texture;
//
//};