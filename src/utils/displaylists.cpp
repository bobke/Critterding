#include "displaylists.h"

Displaylists* Displaylists::Instance() 
{
	static Displaylists t;
	return &t;
}

Displaylists::Displaylists()
{
	generateList();
}

void Displaylists::call(unsigned int index)
{
	glCallList(displayLists+index);
}

void Displaylists::generateList()
{
	cerr << "generating displaylists" << endl;
	displayLists = glGenLists(2);

	// 0 = cube with the bottom missing
	glNewList(displayLists,GL_COMPILE);

		glBegin(GL_QUADS);
			//Quad 1
			glVertex3f( 1.0f, 1.0f, 1.0f);   //V2
			glVertex3f( 1.0f,-1.0f, 1.0f);   //V1
			glVertex3f( 1.0f,-1.0f,-1.0f);   //V3
			glVertex3f( 1.0f, 1.0f,-1.0f);   //V4
			//Quad 2
			glVertex3f( 1.0f, 1.0f,-1.0f);   //V4
			glVertex3f( 1.0f,-1.0f,-1.0f);   //V3
			glVertex3f(-1.0f,-1.0f,-1.0f);   //V5
			glVertex3f(-1.0f, 1.0f,-1.0f);   //V6
			//Quad 3
			glVertex3f(-1.0f, 1.0f,-1.0f);   //V6
			glVertex3f(-1.0f,-1.0f,-1.0f);   //V5
			glVertex3f(-1.0f,-1.0f, 1.0f);   //V7
			glVertex3f(-1.0f, 1.0f, 1.0f);   //V8
			//Quad 4
			glVertex3f(-1.0f, 1.0f, 1.0f);   //V8
			glVertex3f(-1.0f,-1.0f, 1.0f);   //V7
			glVertex3f( 1.0f,-1.0f, 1.0f);   //V1
			glVertex3f( 1.0f, 1.0f, 1.0f);   //V2
			//Quad 5
			glVertex3f(-1.0f, 1.0f,-1.0f);   //V6
			glVertex3f(-1.0f, 1.0f, 1.0f);   //V8
			glVertex3f( 1.0f, 1.0f, 1.0f);   //V2
			glVertex3f( 1.0f, 1.0f,-1.0f);   //V4
			//Quad 6
			glVertex3f( 1.0f,-1.0f,-1.0f);   //V4
			glVertex3f( 1.0f,-1.0f, 1.0f);   //V2
			glVertex3f(-1.0f,-1.0f, 1.0f);   //V8
			glVertex3f(-1.0f,-1.0f,-1.0f);   //V6
		glEnd();

	glEndList();

	// 0 = cube with the bottom missing
	glNewList(displayLists+1,GL_COMPILE);

		glBegin(GL_QUADS);
			//Quad 1
			glNormal3f( 1.0f, 0.0f, 0.0f);
			glVertex3f( 1.0f, 1.0f, 1.0f);   //V2
			glVertex3f( 1.0f,-1.0f, 1.0f);   //V1
			glVertex3f( 1.0f,-1.0f,-1.0f);   //V3
			glVertex3f( 1.0f, 1.0f,-1.0f);   //V4
			//Quad 2
			glNormal3f( 0.0f, 0.0f,-1.0f);
			glVertex3f( 1.0f, 1.0f,-1.0f);   //V4
			glVertex3f( 1.0f,-1.0f,-1.0f);   //V3
			glVertex3f(-1.0f,-1.0f,-1.0f);   //V5
			glVertex3f(-1.0f, 1.0f,-1.0f);   //V6
			//Quad 3
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(-1.0f, 1.0f,-1.0f);   //V6
			glVertex3f(-1.0f,-1.0f,-1.0f);   //V5
			glVertex3f(-1.0f,-1.0f, 1.0f);   //V7
			glVertex3f(-1.0f, 1.0f, 1.0f);   //V8
			//Quad 4
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glVertex3f(-1.0f, 1.0f, 1.0f);   //V8
			glVertex3f(-1.0f,-1.0f, 1.0f);   //V7
			glVertex3f( 1.0f,-1.0f, 1.0f);   //V1
			glVertex3f( 1.0f, 1.0f, 1.0f);   //V2
			//Quad 5
			glNormal3f( 0.0f, 1.0f, 0.0f);
			glVertex3f(-1.0f, 1.0f,-1.0f);   //V6
			glVertex3f(-1.0f, 1.0f, 1.0f);   //V8
			glVertex3f( 1.0f, 1.0f, 1.0f);   //V2
			glVertex3f( 1.0f, 1.0f,-1.0f);   //V4
			//Quad 6
			glNormal3f(0.0f, -1.0f, 0.0f);
			glVertex3f( 1.0f,-1.0f,-1.0f);   //V4
			glVertex3f( 1.0f,-1.0f, 1.0f);   //V2
			glVertex3f(-1.0f,-1.0f, 1.0f);   //V8
			glVertex3f(-1.0f,-1.0f,-1.0f);   //V6
		glEnd();

	glEndList();

	// 1 = floor
	glNewList(displayLists+2,GL_COMPILE);

		glColor4f( 0.0f, 0.0f, 1.0f, 0.0f );
		glBegin(GL_QUADS);
			glVertex3f( 0.0f, 0.0f, 0.0f);
			glVertex3f( 0.0f, 0.0f, 1.0f);
			glVertex3f( 1.0f, 0.0f, 1.0f);
			glVertex3f( 1.0f, 0.0f, 0.0f);
		glEnd();

	glEndList();
}
