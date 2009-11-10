#include "raycast.h"

Raycast::Raycast(btDynamicsWorld* btWorld)
{
	btDynWorld = btWorld;
}

castResult Raycast::cast(const btVector3& rayFrom, const btVector3& rayTo)
{
	result.hit = false;

	btCollisionWorld::ClosestRayResultCallback resultCallback(rayFrom,rayTo);
	btDynWorld->rayTest(rayFrom,rayTo,resultCallback);

	if (resultCallback.hasHit())
	{
// 		cerr << "1 true" << endl;
		result.hitBody = resultCallback.m_collisionObject;
		result.hit = true;
		result.hitPosition = resultCallback.m_hitPointWorld;

/*		if ( result.hitBody )
		{
			cerr << "2 true" << endl;
			result.hit = true;
			result.hitPosition = resultCallback.m_hitPointWorld;
		}*/
	}

	return result;
}

Raycast::~Raycast()
{
}


