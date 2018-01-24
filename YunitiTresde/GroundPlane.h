
#include "Globals.h"

#include "OpenGL.h"
#pragma comment (lib, "Glew/libx86/glew32.lib")
#pragma comment (lib, "SDL/libx86/SDL2.lib")
#pragma comment (lib, "SDL/libx86/SDL2main.lib")
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")

//#include "glut/glut.h"
//GroundPlane::GroundPlane()
//{
//	float r = 1.0f;
//	float g = 1.0f;
//	float b = 1.0f;
//}

void RenderPlane()
{
	//glPushMatrix();
	//glMultMatrixf(transform.M);
	//
	//if (axis == true)
	//{
	//	// Draw Axis Grid
	//	glLineWidth(2.0f);
	//
	//	glBegin(GL_LINES);
	//
	//	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	//
	//	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(1.0f, 0.0f, 0.0f);
	//	glVertex3f(1.0f, 0.1f, 0.0f); glVertex3f(1.1f, -0.1f, 0.0f);
	//	glVertex3f(1.1f, 0.1f, 0.0f); glVertex3f(1.0f, -0.1f, 0.0f);
	//
	//	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	//
	//	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 1.0f, 0.0f);
	//	glVertex3f(-0.05f, 1.25f, 0.0f); glVertex3f(0.0f, 1.15f, 0.0f);
	//	glVertex3f(0.05f, 1.25f, 0.0f); glVertex3f(0.0f, 1.15f, 0.0f);
	//	glVertex3f(0.0f, 1.15f, 0.0f); glVertex3f(0.0f, 1.05f, 0.0f);
	//
	//	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	//
	//	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 1.0f);
	//	glVertex3f(-0.05f, 0.1f, 1.05f); glVertex3f(0.05f, 0.1f, 1.05f);
	//	glVertex3f(0.05f, 0.1f, 1.05f); glVertex3f(-0.05f, -0.1f, 1.05f);
	//	glVertex3f(-0.05f, -0.1f, 1.05f); glVertex3f(0.05f, -0.1f, 1.05f);
	//
	//	glEnd();
	//
	//	glLineWidth(1.0f);
	//}
	//
	//glColor3f(1.0f, 1.0f, 1.0f);
	//
	//if (wire)
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//else
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//
	//InnerRender();
	//
	//glPopMatrix();
}

void InnerRender() 
{
	glLineWidth(1.0f);

	glBegin(GL_LINES);

	float d = 200.0f;

	for (float i = -d; i <= d; i += 1.0f)
	{
		glVertex3f(i, 0.0f, -d);
		glVertex3f(i, 0.0f, d);
		glVertex3f(-d, 0.0f, i);
		glVertex3f(d, 0.0f, i);
	}

	glEnd();
}

//void GroundPlane::SetPos(float x, float y, float z)
//{
//}

//void GroundPlane::SetRotation(float angle, const vec3 & u)
//{
//}

//void GroundPlane::Scale(float x, float y, float z)
//{
//}

//class GroundPlane
//{
//public:
//
//	GroundPlane();
//
//	virtual void	Render() const;
//	virtual void	InnerRender() const;
//	void			SetPos(float x, float y, float z);
//	//void			SetRotation(float angle, const vec3 &u);
//	void			Scale(float x, float y, float z);
//	//PrimitiveTypes	GetType() const;
//
//public:
//	
//	float r, g, b, a;
////	mat4x4 transform;
//	bool axis, wire;
//
//protected:
//	//PrimitiveTypes type;
//};


