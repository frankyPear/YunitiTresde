#pragma once
#include "Module.h"
#include "Globals.h"
#include <map>
#include "Resource.h"
class ModuleResources :public Module
{
public:

	//Constructor
	ModuleResources();

	//Destructor
	~ModuleResources();

	Resource *Get(uid resourceId);


protected:
#pragma region Callbacks
	void OnSaveResource(Config &config)const;

	void OnLoadResource(Config *config);
#pragma endregion

private:
	std::map<uid, Resource*> _resources;//Resources indexed by id

};

