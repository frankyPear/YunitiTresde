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
		float3 *vertices;
		GLuint texID;	
	};

	Billboard();
	~Billboard();
	
	void CreateBillboard(const char* imagepath, const char* name, float3 centerpos, float width, float height);
	void Draw(billboard b);
	void DrawBillboards();

public:
	std::map<const char*, billboard> billboards;
	std::vector<billboard> scene_billboards;

};

