#ifndef RAYCAST_H
#define RAYCAST_H

#include "btBulletDynamicsCommon.h"
#include <iostream>
using namespace std;

struct castResult
{
	bool		hit;
	btRigidBody*	hitBody;
	btVector3	hitPosition;
};

class Raycast
{
	public:
		Raycast(btDynamicsWorld* btWorld);
		~Raycast();

		castResult cast(const btVector3& rayFrom, const btVector3& rayTo);
	private:
		btDynamicsWorld*	btDynWorld;
		castResult result;
};

#endif
