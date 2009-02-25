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
		void			resize(unsigned int X, unsigned int Y);

		float			color[4];

	private:
		unsigned int		gridsizeX;
		unsigned int		gridsizeY;
		float			resolution;

 		vector<Vector3f>	vertices;
};

#endif
