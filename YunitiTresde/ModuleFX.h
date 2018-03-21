#pragma once
#include "Module.h"
#include "Billboard.h"
#include <vector>

class ModuleFX :
	public Module
{
public:
	ModuleFX();
	~ModuleFX();

	bool Init();
	bool Start();
	update_status Update();
	bool Clear();
	void AddBillboard( Billboard* b);
	void DeleteBillboard();
	
public:
	std::vector<Billboard *> billboards;
	
};

