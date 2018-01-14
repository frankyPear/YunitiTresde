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

update_status ModuleRenderer::Update(){
	return UPDATE_CONTINUE;
}

bool ModuleRenderer::CleanUp() {
	return true;
}