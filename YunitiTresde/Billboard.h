#pragma once
#include "Mathgeolib\include\Math\MathAll.h"
#include <map>
#include <vector>
#include "OpenGL.h"

class Billboard
{
public:
	struct billboard
	{
		float* vertices;
		GLuint texID;	
		float3 centerPoint;
		float width, height;
	};

	Billboard();
	~Billboard();
	
	void CreateBillboard(char* imagepath, const char* name, float3 centerpos, float width, float height);
	void Draw(billboard *b);
	void DrawBillboards();
	billboard * GetBillboard(const char* name);
	void ComputeQuad(billboard* b, float *vertex, Frustum& f);

public:
	std::map<const char*, billboard*> billboards;
	std::vector<billboard*> scene_billboards;

};

