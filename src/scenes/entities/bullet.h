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
		unsigned int	maxSteps;
		unsigned int	totalSteps;
		Vector3f	position;

		void		draw();
		void		calcDirection(float direction);
		void		moveForward();

	private:

		GLfloat		*pvertices;
		float		speed;
		float		color[4];
		float		directionX;
		float		directionZ;

		GLfloat 	vertices[24];
		//GLubyte		indices[24];
		GLubyte		indices[20];

		void		resize(float size);

};

#endif
