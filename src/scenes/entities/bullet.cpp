#include "bullet.h"

Bullet::Bullet()
{
	size		= 0.05f;
	speed		= 0.03f;
	resize(size);

	maxSteps	= 30;
	totalSteps	= 0;

	color[0]	= 1.0f;
	color[1]	= 0.0f;
	color[2]	= 0.0f;
	color[3]	= 1.0f;
}

void Bullet::moveForward()
{
	totalSteps++;
	position.x -= directionX;
	position.z -= directionZ;
}

void Bullet::calcDirection(float direction)
{
	float reused = direction * 0.0174532925f;
	directionX = sin(reused) * speed;
	directionZ = cos(reused) * speed;
}


void Bullet::draw()
{

	// enable and specify pointers to vertex arrays
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	
	glPushMatrix();
		glColor4f( color[0], color[1], color[2], color[3] );
		glTranslatef( position.x, position.y, position.z );
	
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);
	glPopMatrix();
}

void Bullet::resize(float newsize)
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

Bullet::~Bullet()
{
}


