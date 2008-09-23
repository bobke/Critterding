#include "bullet.h"

Bullet::Bullet()
{
	size		= 0.04f;
	speed		= 0.1f;
	resize(size);

	totalSteps	= 0;
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


void Bullet::resize(float newsize)
{
	size = newsize;
	halfsize = (newsize / 2.0f);

	// change position according to height
	position.y = halfsize;
}

Bullet::~Bullet()
{
}


