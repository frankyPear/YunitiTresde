#pragma once
#include "Module.h"
#include <vector>
#include <map>
#include "OpenGL.h"
#include "Mathgeolib\include\Math\MathAll.h"
#include "Mathgeolib\include\Geometry\Frustum.h"


class ModuleFX :
	public Module
{
public:
	struct billboard
	{
		float* vertices;
		GLuint texID;
		float3 centerPoint;
		float width, height;
	};
	ModuleFX();
	~ModuleFX();

	bool Init();
	bool Start();
	update_status Update();
	bool Clear();

	void CreateBillboard(char* imagepath, const char* name, float3 centerpos, float width, float height);
	void Draw(billboard *b,  Frustum& f);
	void DrawBillboards(Frustum& f);
	billboard * GetBillboard(const char* name);
	void ComputeQuad(billboard* b,float *vertex, Frustum& f);

public:
	std::map<const char*, billboard*> billboards;
	std::vector<billboard*> scene_billboards;
	
};

