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
	bool CreateShaderProgram();
public:
	GLuint shaderProgram;

private:
	const GLchar* vertexShaderSource_;
	const GLchar* fragmentShaderSource_;
	GLuint vertexShader_;
	GLuint fragmentShader_;
	

};




#endif // !_MODULESHADERS_
