#ifndef _MODULEPHYSICS_
#define _MODULEPHYSICS_

#include "Module.h"
#include "Globals.h"
#include <vector>

class ModulePhysics :
	public Module
{

public:
	ModulePhysics();
	~ModulePhysics();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);

	bool CleanUp();

	bool AddBody(float box_size);

	int debug = 0;


private:

};



#endif // !_MODULEPHYSICS_