#ifndef FOOD_H
#define FOOD_H

#include "GL/gl.h"
#include "vector3f.h"
#include <vector>
#include <iostream>

using namespace std;

class Food
{
	public:
		Food();
		~Food();

		float			size;
		float			halfsize;
		float			energy;

		Vector3f		position;
		float			color[4];

		unsigned int		totalFrames;
		unsigned int		maxtotalFrames;

		GLfloat 		vertices[24];

		void			draw();
		void			resize(float size);


	private:

		GLubyte			indices[20];


};

#endif
