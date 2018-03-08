#include "Component2DTransform.h"
#include "OpenGL.h"
#include "GameObject.h"
#include "Brofiler\include\Brofiler.h"
#include "imgui-1.53\imgui.h"
#include "imgui-1.53\imgui_impl_sdl_gl3.h"

Component2DTransform::Component2DTransform()
{

}


Component2DTransform::~Component2DTransform()
{
}

bool Component2DTransform::PreUpdate()
{
	return true;
}

bool Component2DTransform::Update()
{
	BROFILER_CATEGORY("Component2DTransform Update", Profiler::Color::Azure);
	return true;
}

bool Component2DTransform::PostUpdate()
{
	return true;
}

bool Component2DTransform::Destroy()
{
	return true;
}

bool Component2DTransform::OnEditor()
{
	return true;
}

void Component2DTransform::SetFOV(float degrees)
{

}

void Component2DTransform::SetAspectRatio()
{
	
}

void Component2DTransform::SetPlaneDistances(float zNear, float zFar)
{
	
}

void Component2DTransform::SetPosition(float3 newPos)
{
	
}

