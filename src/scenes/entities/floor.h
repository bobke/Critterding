#ifndef FLOOR_H
#define FLOOR_H

#include "GL/gl.h"
#include "vector3f.h"
#include <vector>
#include <iostream>

using namespace std;

class Floor
{
	public:
		Floor();
		~Floor();

		void			draw();
		void			resize(int newsize);

		float			color[4];

	private:
		unsigned int		gridsize;
		float			resolution;

 		vector<Vector3f>	vertices;
};

#endif
