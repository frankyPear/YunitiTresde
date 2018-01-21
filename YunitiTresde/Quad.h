#ifndef _QUAD_
#define _QUAD_

#include "OpenGL.h"

void DrawImmediateQuad()
{
	glPushMatrix();
	//draw stuff
	
	glRotatef(0.75f, 1, 1, 0);
	glBegin(GL_TRIANGLES);
	// front faces
	glNormal3f(0, 0, 1);
	// face v0-v1-v2
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);
	glColor3f(1, 1, 0);
	glVertex3f(-1, 1, 1);
	glColor3f(1, 0, 0);
	glVertex3f(-1, -1, 1);
	// face v2-v3-v0
	glColor3f(1, 0, 0);
	glVertex3f(-1, -1, 1);
	glColor3f(1, 0, 1);
	glVertex3f(1, -1, 1);
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);

	// right faces
	glNormal3f(1, 0, 0);
	// face v0-v3-v4
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);
	glColor3f(1, 0, 1);
	glVertex3f(1, -1, 1);
	glColor3f(0, 0, 1);
	glVertex3f(1, -1, -1);
	// face v4-v5-v0
	glColor3f(0, 0, 1);
	glVertex3f(1, -1, -1);
	glColor3f(0, 1, 1);
	glVertex3f(1, 1, -1);
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);

	// top faces
	glNormal3f(0, 1, 0);
	// face v0-v5-v6
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);
	glColor3f(0, 1, 1);
	glVertex3f(1, 1, -1);
	glColor3f(0, 1, 0);
	glVertex3f(-1, 1, -1);
	// face v6-v1-v0
	glColor3f(0, 1, 0);
	glVertex3f(-1, 1, -1);
	glColor3f(1, 1, 0);
	glVertex3f(-1, 1, 1);
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);

	// left faces
	glNormal3f(-1, 0, 0);
	// face  v1-v6-v7
	glColor3f(1, 1, 0);
	glVertex3f(-1, 1, 1);
	glColor3f(0, 1, 0);
	glVertex3f(-1, 1, -1);
	glColor3f(0, 0, 0);
	glVertex3f(-1, -1, -1);
	// face v7-v2-v1
	glColor3f(0, 0, 0);
	glVertex3f(-1, -1, -1);
	glColor3f(1, 0, 0);
	glVertex3f(-1, -1, 1);
	glColor3f(1, 1, 0);
	glVertex3f(-1, 1, 1);

	// bottom faces
	glNormal3f(0, -1, 0);
	// face v7-v4-v3
	glColor3f(0, 0, 0);
	glVertex3f(-1, -1, -1);
	glColor3f(0, 0, 1);
	glVertex3f(1, -1, -1);
	glColor3f(1, 0, 1);
	glVertex3f(1, -1, 1);
	// face v3-v2-v7
	glColor3f(1, 0, 1);
	glVertex3f(1, -1, 1);
	glColor3f(1, 0, 0);
	glVertex3f(-1, -1, 1);
	glColor3f(0, 0, 0);
	glVertex3f(-1, -1, -1);

	// back faces
	glNormal3f(0, 0, -1);
	// face v4-v7-v6
	glColor3f(0, 0, 1);
	glVertex3f(1, -1, -1);
	glColor3f(0, 0, 0);
	glVertex3f(-1, -1, -1);
	glColor3f(0, 1, 0);
	glVertex3f(-1, 1, -1);
	// face v6-v5-v4
	glColor3f(0, 1, 0);
	glVertex3f(-1, 1, -1);
	glColor3f(0, 1, 1);
	glVertex3f(1, 1, -1);
	glColor3f(0, 0, 1);
	glVertex3f(1, -1, -1);
	glPopMatrix();
	glEnd();
}


// cube ///////////////////////////////////////////////////////////////////////
//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3
// vertex coords array for glDrawArrays() =====================================
// A cube has 6 sides and each side has 2 triangles, therefore, a cube consists
// of 36 vertices (6 sides * 2 tris * 3 vertices = 36 vertices). And, each
// vertex is 3 components (x,y,z) of floats, therefore, the size of vertex
// array is 108 floats (36 * 3 = 108).
GLfloat vertices1[] = 
{ 
1, 1, 1,  -1, 1, 1,  -1,-1, 1,      // v0-v1-v2 (front)
-1,-1, 1,   1,-1, 1,   1, 1, 1,      // v2-v3-v0

1, 1, 1,   1,-1, 1,   1,-1,-1,      // v0-v3-v4 (right)
1,-1,-1,   1, 1,-1,   1, 1, 1,      // v4-v5-v0

1, 1, 1,   1, 1,-1,  -1, 1,-1,      // v0-v5-v6 (top)
-1, 1,-1,  -1, 1, 1,   1, 1, 1,      // v6-v1-v0

-1, 1, 1,  -1, 1,-1,  -1,-1,-1,      // v1-v6-v7 (left)
-1,-1,-1,  -1,-1, 1,  -1, 1, 1,      // v7-v2-v1

-1,-1,-1,   1,-1,-1,   1,-1, 1,      // v7-v4-v3 (bottom)
1,-1, 1,  -1,-1, 1,  -1,-1,-1,      // v3-v2-v7

1,-1,-1,  -1,-1,-1,  -1, 1,-1,      // v4-v7-v6 (back)
-1, 1,-1,   1, 1,-1,   1,-1,-1	    // v6-v5-v4
};    

									 // normal array
GLfloat normals1[] = 
{
0, 0, 1,   0, 0, 1,   0, 0, 1,      // v0-v1-v2 (front)
0, 0, 1,   0, 0, 1,   0, 0, 1,      // v2-v3-v0

1, 0, 0,   1, 0, 0,   1, 0, 0,      // v0-v3-v4 (right)
1, 0, 0,   1, 0, 0,   1, 0, 0,      // v4-v5-v0

0, 1, 0,   0, 1, 0,   0, 1, 0,      // v0-v5-v6 (top)
0, 1, 0,   0, 1, 0,   0, 1, 0,      // v6-v1-v0

-1, 0, 0,  -1, 0, 0,  -1, 0, 0,      // v1-v6-v7 (left)
-1, 0, 0,  -1, 0, 0,  -1, 0, 0,      // v7-v2-v1

0,-1, 0,   0,-1, 0,   0,-1, 0,      // v7-v4-v3 (bottom)
0,-1, 0,   0,-1, 0,   0,-1, 0,      // v3-v2-v7

0, 0,-1,   0, 0,-1,   0, 0,-1,      // v4-v7-v6 (back)
0, 0,-1,   0, 0,-1,   0, 0,-1	 // v6-v5-v4
};   

									// color array
GLfloat colors1[] = 
{
1, 1, 1,   1, 1, 0,   1, 0, 0,      // v0-v1-v2 (front)
1, 0, 0,   1, 0, 1,   1, 1, 1,      // v2-v3-v0

1, 1, 1,   1, 0, 1,   0, 0, 1,      // v0-v3-v4 (right)
0, 0, 1,   0, 1, 1,   1, 1, 1,      // v4-v5-v0

1, 1, 1,   0, 1, 1,   0, 1, 0,      // v0-v5-v6 (top)
0, 1, 0,   1, 1, 0,   1, 1, 1,      // v6-v1-v0

1, 1, 0,   0, 1, 0,   0, 0, 0,      // v1-v6-v7 (left)
0, 0, 0,   1, 0, 0,   1, 1, 0,      // v7-v2-v1

0, 0, 0,   0, 0, 1,   1, 0, 1,      // v7-v4-v3 (bottom)
1, 0, 1,   1, 0, 0,   0, 0, 0,      // v3-v2-v7

0, 0, 1,   0, 0, 0,   0, 1, 0,      // v4-v7-v6 (back)
0, 1, 0,   0, 1, 1,   0, 0, 1 
};    // v6-v5-v4

void DrawArrayQuad()
{
	// enble and specify pointers to vertex arrays
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normals1);
	glColorPointer(3, GL_FLOAT, 0, colors1);
	glVertexPointer(3, GL_FLOAT, 0, vertices1);
	glRotatef(0.75f, 1, 1, 0);
	glPushMatrix();
	
	          
	
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

	  // vertex array for glDrawElements() and glDrawRangeElement() =================
	  // Notice that the sizes of these arrays become samller than the arrays for
	  // glDrawArrays() because glDrawElements() uses an additional index array to
	  // choose designated vertices with the indices. The size of vertex array is now
	  // 24 instead of 36, but the index array size is 36, same as the number of
	  // vertices required to draw a cube.
GLfloat vertices2[] = { 
1, 1, 1,  -1, 1, 1,  -1,-1, 1,   1,-1, 1,   // v0,v1,v2,v3 (front)
1, 1, 1,   1,-1, 1,   1,-1,-1,   1, 1,-1,   // v0,v3,v4,v5 (right)
1, 1, 1,   1, 1,-1,  -1, 1,-1,  -1, 1, 1,   // v0,v5,v6,v1 (top)
-1, 1, 1,  -1, 1,-1,  -1,-1,-1,  -1,-1, 1,   // v1,v6,v7,v2 (left)
-1,-1,-1,   1,-1,-1,   1,-1, 1,  -1,-1, 1,   // v7,v4,v3,v2 (bottom)
1,-1,-1,  -1,-1,-1,  -1, 1,-1,   1, 1,-1 }; // v4,v7,v6,v5 (back)

											// normal array
GLfloat normals2[] = { 
0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1,   // v0,v1,v2,v3 (front)
1, 0, 0,   1, 0, 0,   1, 0, 0,   1, 0, 0,   // v0,v3,v4,v5 (right)
0, 1, 0,   0, 1, 0,   0, 1, 0,   0, 1, 0,   // v0,v5,v6,v1 (top)
-1, 0, 0,  -1, 0, 0,  -1, 0, 0,  -1, 0, 0,   // v1,v6,v7,v2 (left)
0,-1, 0,   0,-1, 0,   0,-1, 0,   0,-1, 0,   // v7,v4,v3,v2 (bottom)
0, 0,-1,   0, 0,-1,   0, 0,-1,   0, 0,-1 }; // v4,v7,v6,v5 (back)

											// color array
GLfloat colors2[] = {
1, 1, 1,   1, 1, 0,   1, 0, 0,   1, 0, 1,   // v0,v1,v2,v3 (front)
1, 1, 1,   1, 0, 1,   0, 0, 1,   0, 1, 1,   // v0,v3,v4,v5 (right)
1, 1, 1,   0, 1, 1,   0, 1, 0,   1, 1, 0,   // v0,v5,v6,v1 (top)
1, 1, 0,   0, 1, 0,   0, 0, 0,   1, 0, 0,   // v1,v6,v7,v2 (left)
0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,   // v7,v4,v3,v2 (bottom)
0, 0, 1,   0, 0, 0,   0, 1, 0,   0, 1, 1 }; // v4,v7,v6,v5 (back)

// index array of vertex array for glDrawElements() & glDrawRangeElement()
GLubyte indices[] = { 
0, 1, 2,   2, 3, 0,      // front
4, 5, 6,   6, 7, 4,      // right
8, 9,10,  10,11, 8,      // top
12,13,14,  14,15,12,      // left
16,17,18,  18,19,16,      // bottom
20,21,22,  22,23,20 };    // back

///////////////////////////////////////////////////////////////////////////////
// draw cube at bottom-left corner with glDrawElements
// The main advantage of glDrawElements() over glDrawArray() is that
// glDrawElements() allows hopping around the vertex array with the associated
// index values.
// In a cube, the number of vertex data in the vertex array can be reduced to
// 24 vertices for glDrawElements().
// Note that you need an additional array (index array) to store how to traverse
// the vertext data. For a cube, we need 36 entries in the index array.
///////////////////////////////////////////////////////////////////////////////

void DrawElementQuad()
{
	// enable and specify pointers to vertex arrays
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normals2);
	glColorPointer(3, GL_FLOAT, 0, colors2);
	glVertexPointer(3, GL_FLOAT, 0, vertices2);
	glRotatef(0.75f, 1, 1, 0);
	glPushMatrix();	
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);
	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}
#endif // !_QUAD_

