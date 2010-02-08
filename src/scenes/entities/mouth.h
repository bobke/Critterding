#ifndef MOUTH_H
#define MOUTH_H

#include <iostream>
#include "btBulletDynamicsCommon.h"
#include <BulletCollision/CollisionDispatch/btGhostObject.h>

using namespace std;

class Mouth
{
public:
	Mouth(btDynamicsWorld* ownerWorld, void* owner, const btVector3& dimensions, float weight, btTransform& offset, btTransform& transform);
	~Mouth();

	btPairCachingGhostObject*	ghostObject;
	btRigidBody* 			body;
	btCollisionShape* 		shape;
	
	void				updateGhostObjectPosition();
	void				connectMouthAndBody();

	btDefaultMotionState*		myMotionState;

private:
	btDynamicsWorld* 		m_ownerWorld;
};
#endif
