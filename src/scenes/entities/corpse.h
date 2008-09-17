#ifndef CORPSE_H
#define CORPSE_H

#include "GL/gl.h"
#include "vector3f.h"
#include <vector>
#include <iostream>

using namespace std;

class Corpse
{
	public:
		Corpse();
		~Corpse();

		float			size;
		float			energy;

		float			maxsize;
		float			maxenergy;

		Vector3f		position;

		unsigned int		totalFrames;
		unsigned int		maxtotalFrames;

		void			draw();
		void			resize();
	private:

		GLubyte			indices[20];
		GLfloat 		vertices[24];
		float			color[4];
		float			halfsize;

};

#endif
