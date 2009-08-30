#include "raycast.h"

Raycast::Raycast(btDynamicsWorld* btWorld)
{
	btDynWorld = btWorld;
}

castResult Raycast::cast(const btVector3& rayFrom, const btVector3& rayTo)
{
	castResult result;
	result.hit = false;

	btCollisionWorld::ClosestRayResultCallback resultCallback(rayFrom,rayTo);
	btDynWorld->rayTest(rayFrom,rayTo,resultCallback);

	if (resultCallback.hasHit())
	{
		result.hitBody = btRigidBody::upcast(resultCallback.m_collisionObject);
		if ( result.hitBody )
		{
			result.hit = true;
			result.hitPosition = resultCallback.m_hitPointWorld;
		}
	}

	return result;
}

Raycast::~Raycast()
{
}


