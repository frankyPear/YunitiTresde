#include "ModuleShaders.h"
#include "OpenGL.h"

ModuleShaders::ModuleShaders()
{
	 vertexShaderSource_ =
	"layout (location = 0) in vec3 position; \n"
	"layout (location = 1) in vec3  color; \n"
	"out vec3 ourColor;"
	"uniform mat4 gl_ModelViewMatrix;\n"
	"uniform mat4 gl_ProjectionMatrix;\n"
	"void main()\n"
	"{ gl_Position =gl_ProjectionMatrix*gl_ModelViewMatrix* vec4 (position.x, position.y, position.z, 1.0);\n"
	"ourColor = color;"
	"}";

	 fragmentShaderSource_ =
	"in vec3 ourColor;"
	"void main()"
	"{ gl_FragColor = vec4(ourColor.x,ourColor.y,ourColor.z, 1.0f); }";

}

ModuleShaders::~ModuleShaders()
{
	glDeleteProgram(shaderProgram);
}

bool ModuleShaders::CompileVertexShader()
{
	bool ret = true;

	vertexShader_ = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader_, 1, &vertexShaderSource_, NULL);
	glCompileShader(vertexShader_);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader_, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader_, 512, NULL, infoLog);
		LOG("SHADER::VERTEX::COMPILATION_FAILED\n", infoLog);
		ret = false;
	}
	return ret;
}

bool ModuleShaders::CompileFragmentShader()
{
	bool ret = true;

	fragmentShader_ = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader_, 1, &fragmentShaderSource_, NULL);
	glCompileShader(fragmentShader_);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(fragmentShader_, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader_, 512, NULL, infoLog);
		LOG("SHADER::FRAGMENT::COMPILATION_FAILED\n", infoLog);
		ret = false;
	}
	return ret;
}

bool ModuleShaders::CreateShaderProgram()
{
	bool ret = true;
	//Shall shaderProgram_ be public?
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader_);
	glAttachShader(shaderProgram, fragmentShader_);
	glLinkProgram(shaderProgram);

	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		LOG("SHADER::PROGRAM::LINKING_FAILED\n", infoLog);
		ret = false;
	}

	glDeleteShader(vertexShader_);
	glDeleteShader(fragmentShader_);

	return ret;
}

bool ModuleShaders::ActivateShaderProgram()
{
	//TODO: Add LOG
	bool ret = true;
	glUseProgram(shaderProgram);

	return ret;
}
