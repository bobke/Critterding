#include "floor.h"

Floor::Floor()
{
	gridsize	= 20;
	resolution	= 1.0f;
	resize(gridsize);

	color[0]	= 0.0f;
	color[1]	= 0.0f;
	color[2]	= 1.0f;
	color[3]	= 0.0f;
}

void Floor::draw()
{
	glColor4f( color[0], color[1], color[2], color[3] );
	glPushMatrix();
		glBegin(GL_QUADS);
			for( unsigned int i=0; i < vertices.size(); i++)
			{
				//cout << vertices[i].x() << " " << vertices[i].y() << " " << vertices[i].z() << endl;
				glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
			}
		glEnd();
	glPopMatrix();
}

void Floor::resize(int newsize)
{
	gridsize = newsize;

	vertices.clear();

	vertices.push_back( Vector3f( 0.0f, 0.0f, 0.0f ) );
	vertices.push_back( Vector3f( 0.0f, 0.0f, gridsize ) );

	vertices.push_back( Vector3f( gridsize, 0.0f, gridsize ) );
	vertices.push_back( Vector3f( gridsize, 0.0f, 0.0f ) );
}

Floor::~Floor()
{
}


