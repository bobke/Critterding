#include "wall.h"

Wall::Wall()
{
	size		= 0.1f;
 	energy		= 1000.0f;
	resize(size);

	disabled	= false;

	color[0]	= 0.5f;
	color[1]	= 0.5f;
	color[2]	= 0.0f;
	color[3]	= 0.0f;
}

void Wall::draw()
{
	if ( !disabled )
	{
		glVertexPointer(3, GL_FLOAT, 0, vertices);
		
		glPushMatrix();
			glColor4f( color[0], color[1], color[2], color[3] );
			glTranslatef( position.x, position.y, position.z );
		
			glDrawElements(GL_QUADS, 20, GL_UNSIGNED_BYTE, indices);
		glPopMatrix();
	}
}

void Wall::resize(float newsize)
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
	indices[4] = 2; indices[7] = 3; indices[6] = 7; indices[5] = 6;
	indices[8] = 1; indices[9] = 0; indices[10] = 4; indices[11] = 5;
	indices[12] = 1; indices[13] = 2; indices[14] = 3; indices[15] = 0;
	indices[16] = 5; indices[19] = 6; indices[18] = 7; indices[17] = 4;
}

void Wall::toggle()
{
	if ( disabled )	disabled = false;
	else		disabled = true;
}

Wall::~Wall()
{
}


