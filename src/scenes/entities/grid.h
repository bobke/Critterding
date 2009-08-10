#ifndef GRID_H
#define GRID_H

#include "btBulletDynamicsCommon.h"
#include "GL/gl.h"
#include "../../utils/displaylists.h"
#include <iostream>

using namespace std;

class Grid
{
	public:
		Grid();
		~Grid();

		void			draw();
		void			resize(unsigned int X, unsigned int Y, btDynamicsWorld* m_dynamicsWorld);

		float			color[4];

	private:
		unsigned int		gridsizeX;
		unsigned int		gridsizeY;
		btCollisionShape*	groundShape;
		btCollisionObject*	fixedGround;
		btScalar		m[16];
};

#endif
