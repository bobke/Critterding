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
		float			halfsize;
		float			energy;

		float			maxsize;
		float			maxenergy;

		Vector3f		position;

		unsigned int		totalFrames;

		bool			isCarried;

		void			resize();
	private:
};

#endif