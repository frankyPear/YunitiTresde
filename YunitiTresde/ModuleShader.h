#pragma once
#include "Module.h"
#include "SDL\include\SDL.h"
#include "OpenGL.h"

class ModuleShader :
	public Module
{
public:
	ModuleShader();
	~ModuleShader();
	bool Init();
	bool Start();
	update_status Predate(float dt);
	update_status Update(float dt);
	bool CleanUp();

	GLuint VertexShaderLoad();
	GLuint FragmentShaderLoad();
	GLuint LinkShaders(GLuint vertexID, GLuint fragmentID);
	bool CompileShader();
	bool CompileVertexShader();
	bool CompileFragmentShader();
	bool CreateShaderProgram();
	bool ActivateShaderProgram();
	bool DeactivateShaderProgram();
public:
	const char* vertex_link = "uniform mat4 gl_ModelViewMatrix; uniform mat4 gl_ProjectionMatrix; attribute vec4 gl_Vertex;	void main() { gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix* gl_Vertex;} ";
	const char* fragment_link = "void main(){ gl_FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f); }";
	GLuint shaderProgram;
private:
	const GLchar* vertexShader_2;
	const GLchar* fragmentShader_2;
	const GLchar* vertexShaderSource_;
	const GLchar* fragmentShaderSource_;
	GLuint vertexShader_;
	GLuint fragmentShader_;


};