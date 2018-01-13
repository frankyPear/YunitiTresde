#include "ModuleRenderer.h"



ModuleRenderer::ModuleRenderer()
{
}


ModuleRenderer::~ModuleRenderer()
{
}

bool ModuleRenderer::Init() {
	return true;
}

bool ModuleRenderer::Start() {
	return true;
}

update_status ModuleRenderer::Update(float deltaTime){
	return UPDATE_CONTINUE;
}

bool ModuleRenderer::CleanUp() {
	return true;
}