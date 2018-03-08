#ifndef _MODULEUI_
#define _MODULEUI_

#include "Module.h"
#include "Globals.h"



class ModuleUI :
	public Module
{

public:
	ModuleUI();
	~ModuleUI();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);

	bool CleanUp();

public:




private:


};



#endif // !_MODULEUI_

