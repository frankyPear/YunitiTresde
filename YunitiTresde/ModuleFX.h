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
		
		GLuint texID;
		float3 centerPoint;
		float width, height;
	};

	float offsetX = 1.0f;
	float offsetY = -1.0f;

	std::vector<std::vector<billboard> > grid;

	ModuleFX();
	~ModuleFX();

	bool Init();
	bool Start();
	update_status Update();
	bool Clear();

	void CreateBillboard(char* imagepath, float3 centerpos, float width, float height);
	void Draw(billboard b,  Frustum& f);
	void DrawBillboards(Frustum& f);
	void ComputeQuad(billboard b,std::vector<GLfloat>& vertex, Frustum& f);
	void CreateGrid(char* imagepath, float3 initialcenterpos, float width, float height, int rows, int columns);



public:
	std::vector<billboard> scene_billboards;


};

