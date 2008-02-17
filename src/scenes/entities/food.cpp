#include "food.h"

Food::Food()
{
	size		= 0.1f;
 	energy		= 1000.0f;
	resize(size);

	totalFrames		= 0;
	maxtotalFrames		= 5000;

	color[0]	= 0.0f;
	color[1]	= 1.0f;
	color[2]	= 0.0f;
	color[3]	= 1.0f;
}

void Food::draw()
{
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	
	glPushMatrix();
		glColor4f( color[0], color[1], color[2], color[3] );
		glTranslatef( position.x, position.y, position.z );
	
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);
	glPopMatrix();
}

void Food::resize(float newsize)
{
	size = newsize;
	halfsize = (newsize / 2.0f);

	// change position according to height
	position.y = halfsize;

	// left plane
	vertices[0] = -halfsize; vertices[1] = halfsize; vertices[2] = halfsize;
	vertices[3] = -halfsize; vertices[4] = -halfsize; vertices[5] = halfsize;
	vertices[6] = -halfsize; vertices[7] = -halfsize; vertices[8] = -halfsize;
	vertices[9] = -halfsize; vertices[10] = halfsize; vertices[11] = -halfsize;

	// right plane
	vertices[12] = halfsize; vertices[13] = halfsize; vertices[14] = halfsize;
	vertices[15] = halfsize; vertices[16] = -halfsize; vertices[17] = halfsize;
	vertices[18] = halfsize; vertices[19] = -halfsize; vertices[20] = -halfsize;
	vertices[21] = halfsize; vertices[22] = halfsize; vertices[23] = -halfsize;

	indices[0] = 0; indices[1] = 3; indices[2] = 7; indices[3] = 4;
	indices[4] = 1; indices[5] = 2; indices[6] = 6; indices[7] = 5;
	indices[8] = 2; indices[9] = 3; indices[10] = 7; indices[11] = 6;
	indices[12] = 1; indices[13] = 0; indices[14] = 4; indices[15] = 5;
	indices[16] = 1; indices[17] = 2; indices[18] = 3; indices[19] = 0;
	indices[20] = 5; indices[21] = 6; indices[22] = 7; indices[23] = 4;
}
/*

void Food::draw()
{
	glColor4f( color[0], color[1], color[2], color[3] );
	glPushMatrix();

		glTranslatef( position.x, position.y, position.z );

// 		glRotatef( $self->{rotation3f}[0], 1.0, 0.0, 0.0 );
// 		glRotatef( $self->{rotation3f}[1], 0.0, 1.0, 0.0 );
// 		glRotatef( $self->{rotation3f}[2], 0.0, 0.0, 1.0 );

		glBegin(GL_QUADS);

			// top plane
			glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
			glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
			glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);
			glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);

			// bottom plane
			glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
			glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
			glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
			glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);

			// back plane
			glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
			glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
			glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);
			glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);

			// front plane
			glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
			glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
			glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);
			glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);

			// left plane
			glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
			glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
			glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
			glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);

			// right plane
			glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);
			glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
			glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);
			glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);

		glEnd();
	glPopMatrix();
}

void Food::resize(float newsize)
{
	size = newsize;
	halfsize = (newsize / 2.0f);

	// change position according to height
	position.y = halfsize;

	vertices.clear();
	// vertices of left plane
	vertices.push_back( Vector3f(-halfsize, halfsize, halfsize ) );
	vertices.push_back( Vector3f(-halfsize,-halfsize, halfsize ) );
	vertices.push_back( Vector3f(-halfsize,-halfsize,-halfsize ) );
	vertices.push_back( Vector3f(-halfsize, halfsize,-halfsize ) );

	// vertices of right plane
	vertices.push_back( Vector3f( halfsize, halfsize, halfsize ) );
	vertices.push_back( Vector3f( halfsize,-halfsize, halfsize ) );
	vertices.push_back( Vector3f( halfsize,-halfsize,-halfsize ) );
	vertices.push_back( Vector3f( halfsize, halfsize,-halfsize ) );
}*/

Food::~Food()
{
}


