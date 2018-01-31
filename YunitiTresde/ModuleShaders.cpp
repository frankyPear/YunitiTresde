#include "ModuleShaders.h"
#include "OpenGL.h"

ModuleShaders::ModuleShaders()
{
	vertexShader_ =
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
		"}\n";	fragmentShader_ =		"#version 330 core\n"
		"in vec3 ourColor;\n"
		"in vec2 TexCoord;\n"
		"out vec4 color;\n"
		"uniform sampler2D ourTexture;\n"
		"void main()\n"
		"{\n"
		"color = texture(ourTexture, TexCoord);\n"
		"}\n";
}

bool ModuleShaders::CompileShader()
{
	bool ret = true;

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShader_, NULL);
	glCompileShader(vertexShader); 

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512,NULL, infoLog);
		LOG("SHADER::VERTEX::COMPILATION_FAILED\n", infoLog);
	}
	return ret;
}