#include "ModuleShaders.h"
#include "OpenGL.h"

ModuleShaders::ModuleShaders()
{
	vertexShaderSource_ =
		"#version 330 core\n"
		"layout(location = 0) in vec3 position;\n"
		"layout(location = 1) in vec3 color;\n"
		//"layout(location = 2) in vec2 texCoord;\n"
		"out vec3 ourColor;\n"
		"out vec2 TexCoord;\n"
		"uniform mat4 model_matrix;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = projection * view * model_matrix * vec4(position, 1.0f);\n"
		"	ourColor = color;\n"
	//	"	TexCoord = texCoord;\n"
		"}\n";

	fragmentShaderSource_ =
		"#version 330 core\n"
		"in vec3 ourColor;\n"
	//	"in vec2 TexCoord;\n"
		"out vec4 color;\n"
		"uniform sampler2D ourTexture;\n"
		"void main()\n"
		"{\n"
		//"color = texture(ourTexture, TexCoord);\n"
		"color = vec4(ourColor,1.0f)\n"
		"}\n";
}

ModuleShaders::~ModuleShaders()
{

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