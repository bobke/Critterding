#ifndef GRID_H
#define GRID_H

#include "GL/gl.h"
#include "vector3f.h"
#include <vector>
#include <iostream>

using namespace std;

class Grid
{
	public:
		Grid();
		~Grid();

		void			draw();
		void			resize(int newsize);

		float			color[4];

	private:
		unsigned int		gridsize;
		float			resolution;

 		vector<Vector3f>	vertices;
};

#endif
