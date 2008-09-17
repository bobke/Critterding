#ifndef WALL_H
#define WALL_H

#include "GL/gl.h"
#include "vector3f.h"
#include <vector>
#include <iostream>

using namespace std;

class Wall
{
	public:
		Wall();
		~Wall();

		float			size;
		float			halfsize;
		float			energy;

		bool			disabled;

		Vector3f		position;

		void			draw();
		void			toggle();
		void			resize(float size);

	private:

		float			color[4];
		GLfloat 		vertices[24];
		GLubyte			indices[20];


};

#endif
