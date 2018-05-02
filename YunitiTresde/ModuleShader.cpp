#include "ModuleShader.h"
#include <iostream>
using namespace std;


ModuleShader::ModuleShader()
{
	vertexShader_2 =
		"#version 330 core\n"
		"layout(location = 0) in vec3 position;\n"
		"layout(location = 1) in vec3 color;\n"
		"layout(location = 2) in vec2 texCoord;\n"
		"out vec3 ourColor;\n"
		"out vec2 TexCoord;\n"
		"uniform mat4 model_matrix;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = projection * view * model_matrix * vec4(position, 1.0f);\n"
		"	ourColor = color;\n"
		"	TexCoord = texCoord;\n"
		"}\n";

	fragmentShader_2 = "#version 330 core\n"
		"in vec3 ourColor;\n"
		"in vec2 TexCoord;\n"
		"out vec4 color;\n"
		"uniform sampler2D ourTexture;\n"
		"void main()\n"
		"{\n"
		"color = texture(ourTexture, TexCoord);\n"
		"}\n";

	/*Shaders add*/
	vertexShaderSource_ =
		"layout (location = 0) in vec3 position; \n"
		"layout (location = 1) in vec3  color; \n"
		//"layout (location = 2) in vec2 texCoord; \n"
		"out vec3 ourColor;"
		//"out vec2 TexCoord;"
		"uniform mat4 gl_ModelViewMatrix;\n"
		"uniform mat4 gl_ProjectionMatrix;\n"
		"void main()\n"
		"{ gl_Position =gl_ProjectionMatrix*gl_ModelViewMatrix* vec4 (position.x, position.y, position.z, 1.0);\n"
		"ourColor = color;"
		//"TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);\n"
		"}";

	fragmentShaderSource_ =
		"in vec3 ourColor; \n"
		//"in vec2 TexCoord; \n"
		//"uniform sampler2D tex0; "
		"void main() \n"
		"{ \n"
		// "vec4 color = texture2D(tex0.x, tex0.y, TexCoord.x,TexCoord.y); \n"
		// "gl_FragColor = color; \n"
		"gl_FragColor = vec4(ourColor.x,ourColor.y,ourColor.z, 1.0f); \n"
		"}";


}


ModuleShader::~ModuleShader()
{
	glDeleteProgram(shaderProgram);
}

bool ModuleShader::Init()
{
	CompileShader();
	return true;
}

bool ModuleShader::Start()
{
	VertexShaderLoad();
	FragmentShaderLoad();
	CreateShaderProgram();
	ActivateShaderProgram();
	return true;
}

update_status ModuleShader::Preupdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleShader::Update(float dt)
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
	cout << "vertex shader compiled succefully with ID: " << vertexShader << endl;
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
	cout << "fragment shader compiled succefully with ID: " << fragmentShader << endl;
	return fragmentShader;
}

GLuint ModuleShader::LinkShaders(GLuint vertexID, GLuint fragmentID)
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
			cout << "Shader link error: " << linking_infoLog << endl;
		}
		cout << "linking shaders compiled succefully with ID: " << shaderProgram << endl;
		if (vertexID != -1)	glDeleteShader(vertexID);
		if (fragmentID != -1) glDeleteShader(fragmentID);
		return shaderProgram;
	}
	return -1;
}

bool ModuleShader::CompileShader()
{
	bool ret = true;

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShader_2, NULL);
	glCompileShader(vertexShader);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		LOG("SHADER::VERTEX::COMPILATION_FAILED\n", infoLog);
	}
	return ret;
}
bool ModuleShader::CompileVertexShader()
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

bool ModuleShader::CompileFragmentShader()
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

bool ModuleShader::CreateShaderProgram()
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

bool ModuleShader::ActivateShaderProgram()
{
	//TODO: Add LOG
	bool ret = true;
	glUseProgram(shaderProgram);

	return ret;
}
bool ModuleShader::DeactivateShaderProgram()
{
	//TODO: Add LOG
	bool ret = true;
	glDeleteProgram(shaderProgram);

	return ret;
}