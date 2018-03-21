#pragma once
#include "Module.h"
#include "Billboard.h"
#include <vector>

class ModuleFX :
	public Module
{
public:
	struct billboard
	{
		float* vertices;
		GLuint texID;
	};

	ModuleFX();
	~ModuleFX();

	bool Init();
	bool Start();
	update_status Update();
	bool Clear();

	void CreateBillboard(const char* imagepath, const char* name, float3 centerpos, float width, float height);
	void Draw(billboard *b);
	void DrawBillboards();

public:
	std::vector<billboard*> scene_billboards;


	
};

