#ifndef FOOD_H
#define FOOD_H

#include "GL/gl.h"
#include "vector3f.h"
#include "../../utils/settings.h"
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

		unsigned int		totalFrames;

		bool			isCarried;

		void			resize();
	private:
		Settings		*settings;
};

#endif
