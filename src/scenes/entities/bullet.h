#ifndef BULLET_H
#define BULLET_H

#include <vector>
#include <iostream>
#include <cmath>

#include "GL/gl.h"
#include "vector3f.h"

using namespace std;

class Bullet
{
	public:
		Bullet();
		~Bullet();

		float		size;
		float		halfsize;
		unsigned int	totalSteps;
		Vector3f	position;

		void		calcDirection(float direction);
		void		moveForward();

	private:

		GLfloat		*pvertices;
		float		speed;
		float		directionX;
		float		directionZ;

		void		resize(float size);

};

#endif
