#ifndef WALL_H
#define WALL_H

#include "btBulletDynamicsCommon.h"
#include "GL/gl.h"
#include "../../utils/displaylists.h"
#include <iostream>

#include "entity.h"

using namespace std;

class Wall : public Entity
{
	public:
		Wall(float X, float Y, float Z, btVector3 position, btDynamicsWorld* m_dynamicsWorld);
		~Wall();

		void			draw();
		void			drawDimmed(float dim);
		void			create(float X, float Y, float Z, btVector3 position, btDynamicsWorld* m_dynamicsWorld);

// 		float			color[4];
		btTransform		groundTransform;
	private:
		btDynamicsWorld* 	m_ownerWorld;
		float			halfX;
		float			halfY;
		float			halfZ;
		btCollisionShape*	groundShape;
		btScalar		nposition[16];
		btCollisionObject*	fixedGround;
};

#endif
