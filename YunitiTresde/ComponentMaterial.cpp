#pragma once
#include "ComponentMaterial.h"
#include "GameObject.h"
#include "Application.h"
#include "ModuleResources.h"
#include "ModuleRenderer.h"
#include "imgui-1.53\imgui.h"
#include "imgui-1.53\imgui_impl_sdl_gl3.h"

ComponentMaterial::ComponentMaterial(GameObject *gameObject) :Component(gameObject, Type::MATERIAL)
{
	//Constructor
	type = MATERIAL;
	component_id = App->rng->GetRandomNumber();
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
	static const char* selected_item_ = NULL;
	//if (ImGui::TreeNodeEx("Material")) {
		ImGui::LabelText("", "Select Texture: ");
		{
			const char* textures_[] = { IMAGE1, IMAGE2, IMAGE3, IMAGE4 };

			if (ImGui::BeginCombo("", selected_item_))
			{
				for (int n = 0; n < IM_ARRAYSIZE(textures_); n++)
				{
					bool is_selected = (selected_item_ == textures_[n]);
					if (ImGui::Selectable(textures_[n], is_selected)) {
						selected_item_ = textures_[n];
						ImGui::SetItemDefaultFocus();
						App->renderer->SetIdImage(n);
					}
				}
				ImGui::EndCombo();
			}
		}
		ImGui::Text("WIDTH: %d", App->renderer->width_);
		ImGui::Text("HEIGTH: %d", App->renderer->heigth_);
		ImGui::Text("File: %s", selected_item_);
		ImGui::Text("BYTES: %d", App->renderer->bytes_);
		if (ImGui::Button("Reset"))
		{
			App->renderer->width_ = 0;
			App->renderer->heigth_ = 0;
			App->renderer->bytes_ = 0;
			App->textures->loadImage(" ");
			App->textures->DeleteImage(0);
			App->textures->DeleteImage(1);
			App->textures->DeleteImage(2);
			App->textures->DeleteImage(3);
			App->textures->DeleteImage(4);
			App->renderer->SetIdImage(-1);
		}
		//ImGui::TreePop();
	//}
}

