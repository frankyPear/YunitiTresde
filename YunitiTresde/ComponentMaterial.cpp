#include "ComponentMaterial.h"

#include "Application.h"
#include "ModuleResources.h"
#include "imgui-1.53\imgui.h"
#include "imgui-1.53\imgui_impl_sdl_gl3.h"

ComponentMaterial::ComponentMaterial(GameObject *gameObject):Component(gameObject,Type::MATERIAL)
{
	//Constructor
	

}



ComponentMaterial::~ComponentMaterial()
{
}

bool ComponentMaterial::SetResource(uid resourceId)
{
	bool r = false;
	if (_resourceId != 0) {
		Resource *resource = App->resources->Get(resourceId);
		if (resource != nullptr && resource->GetType() == Resource::Type::texture) {
			if (resource->LoadToMemory()) {
				_resourceId = resourceId;
				r = true;
			}
		}
	}

	return r;
}



void ComponentMaterial::AddMaterialResource(unsigned int uid)
{

}

void ComponentMaterial::OnEditor()
{
	if (ImGui::TreeNodeEx("Material"))
	{
		if (_resourceId != 0)
		{
			ImGui::Text("Resource ID: %i", _resourceId);
		}
		else
		{
			ImGui::Text("Missing resource texture!");
		}
		if (ImGui::Button("Delete Component"))
		{
			//wantsToDie = true;
		}
		ImGui::TreePop();
	}
}

