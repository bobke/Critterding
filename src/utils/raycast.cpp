#include "raycast.h"

Raycast::Raycast(btDynamicsWorld* btWorld)
{
	btDynWorld = btWorld;
}

castResult Raycast::cast(const btVector3& rayFrom, const btVector3& rayTo)
{
	castResult result;
	btCollisionWorld::ClosestRayResultCallback resultCallback(rayFrom,rayTo);
	btDynWorld->rayTest(rayFrom,rayTo,resultCallback);

	if (resultCallback.hasHit())
	{
		result.hit = true;
		result.hitBody = btRigidBody::upcast(resultCallback.m_collisionObject);
		result.hitPosition = resultCallback.m_hitPointWorld;
	}
	else
		result.hit = false;

	return result;
}

Raycast::~Raycast()
{
}


