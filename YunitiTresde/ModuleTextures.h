#pragma once
#include "Module.h"
#include "OpenGL.h"
#include <map>
#include <string>

#pragma comment (lib, "Glew/libx86/glew32.lib")
#pragma comment (lib, "SDL/libx86/SDL2.lib")
#pragma comment (lib, "SDL/libx86/SDL2main.lib")
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")


struct loadedTex
{
	GLuint texId;
	uint numberOfReferences;
	loadedTex();
	loadedTex(GLuint id);
	~loadedTex();
	
};


class ModuleTextures :
	public Module
{
public:
	ModuleTextures();
	~ModuleTextures();

	bool Init();
	bool Start();
	update_status Update();	
	bool CleanUp();
	void DrawCheckers();
	GLuint loadImage(const char* fileName);
	void DeleteImage(uint imageID);

	void setWrapMode(int mode);
	void setFilterMode(int filter);

	GLuint GetTexture(const char* path);
	void RemoveTexture(const char* path);

	int GetNumberOfTextures();
	int GetNumberOfReferences(const char* path);
	int GetTexId(const char* path);

public:

	GLfloat texVect[8] =
	{
		0.0f,0.0f,	1.0f,0.0f,
		0.0f,1.0f,	1.0f,1.0f
	};
	
	GLubyte indices[6] =
	{
		0,	1,
		3,	3,
		2,	0
	};

	GLuint texId;
	GLubyte checkImage[128][128][4];


	int wrapModeID, filterID;
	GLint actualWrapMode = GL_CLAMP;
	GLint actualFilterMode = GL_LINEAR;

	GLfloat* width;
	GLfloat* heigth;
	GLfloat* selected_item;
	GLfloat* format;

	std::map<std::string, loadedTex> loadedTextures;

private:

	
};

