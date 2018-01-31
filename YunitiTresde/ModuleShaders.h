#ifndef _MODULESHADERS_
#define _MODULESHADERS_

#include "Module.h"
#include "OpenGL.h"

class ModuleShaders : public Module
{
public:
	ModuleShaders();
	~ModuleShaders();

	bool CompileVertexShader();
	bool CompileFragmentShader();

private:
	const GLchar* vertexShader_;
	const GLchar* fragmentShader_;


};




#endif // !_MODULESHADERS_
