#ifndef WALL_H
#define WALL_H

#include "btBulletDynamicsCommon.h"
#include "GL/gl.h"
#include "../../utils/displaylists.h"
#include <iostream>

using namespace std;

class Wall
{
	public:
		Wall(float X, float Y, float Z, btVector3 position, btDynamicsWorld* m_dynamicsWorld);
		~Wall();

		void			draw();
		void			create(float X, float Y, float Z, btVector3 position, btDynamicsWorld* m_dynamicsWorld);

		float			color[4];

	private:
		btDynamicsWorld* 	m_ownerWorld;
		float			halfX;
		float			halfY;
		float			halfZ;
		btCollisionShape*	groundShape;
		btCollisionObject*	fixedGround;
		btScalar		m[16];
};

#endif
