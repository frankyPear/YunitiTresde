#include "ModuleShader.h"
#include <iostream>
using namespace std;


ModuleShader::ModuleShader()
{


}


ModuleShader::~ModuleShader()
{
}

bool ModuleShader::Init() 
{
	bool ret = true;
	return ret;
}

bool ModuleShader::Start() 
{
	bool ret = true;
	return ret;
}

update_status ModuleShader::Update() 
{
	return UPDATE_CONTINUE;
}

bool ModuleShader::CleanUp()
{
	bool ret = true;
	return ret;
}

GLuint ModuleShader::VertexShaderLoad()
{
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_link, NULL);
	glCompileShader(vertexShader);
	GLint success;
	GLchar vertex_infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (success == 0)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, vertex_infoLog);
		cout << "Vertex shader compilation error: " << vertex_infoLog << endl;;
		return -1;
	}
	cout << "vertex shader compiled succefully with ID: "<< vertexShader << endl;
	return vertexShader;
}

GLuint ModuleShader::FragmentShaderLoad()
{
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_link, NULL);
	glCompileShader(fragmentShader);
	GLint success;
	GLchar fragment_infoLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (success == 0)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, fragment_infoLog);
		cout << "Fragment shader compilation error: " << fragment_infoLog << endl;
		return -1;
	}
	cout << "fragment shader compiled succefully with ID: "<< fragmentShader<< endl;
	return fragmentShader;
}

void ModuleShader::LinkShaders(GLuint vertexID, GLuint fragmentID)
{
	if (vertexID != -1 && fragmentID != -1)
	{
		GLuint shaderProgram;
		shaderProgram = glCreateProgram();
		if (vertexID != -1)	glAttachShader(shaderProgram, vertexID);
		if (fragmentID != -1)	glAttachShader(shaderProgram, fragmentID);
		glLinkProgram(shaderProgram);
		GLchar linking_infoLog[512];
		GLint success;
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, linking_infoLog);
			LOG("Shader link error: %s", linking_infoLog);
		}

		if (vertexID != -1)	glDeleteShader(vertexID);
		if (fragmentID != -1) glDeleteShader(fragmentID);
	}
}