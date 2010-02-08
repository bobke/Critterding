#ifndef BODYPART_H
#define BODYPART_H

#include <iostream>
#include "btBulletDynamicsCommon.h"

using namespace std;

class Bodypart
{
	public:
		Bodypart(btDynamicsWorld* ownerWorld, void* owner, const btVector3& dimensions, float weight, btTransform& offset, btTransform& transform);
		~Bodypart();

		btRigidBody* 		body;
		btCollisionShape* 	shape;

		btDefaultMotionState*	myMotionState;

	private:
		btDynamicsWorld* 	m_ownerWorld;

};
#endif
