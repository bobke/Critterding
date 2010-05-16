#ifndef BODYPART_H
#define BODYPART_H

#include <iostream>
#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionShapes/btShapeHull.h"

using namespace std;

struct ShapeCache
{
	struct Edge { btVector3 n[2];int v[2]; };
	ShapeCache(btConvexShape* s) : m_shapehull(s) {}
	btShapeHull			m_shapehull;
	btAlignedObjectArray<Edge>	m_edges;
};

class Bodypart
{
	public:
		Bodypart(btDynamicsWorld* ownerWorld, void* owner, const btVector3& dimensions, float weight, btTransform& offset, btTransform& transform);
		~Bodypart();

		btRigidBody* 		body;
		btCollisionShape* 	shape;

		btDefaultMotionState*	myMotionState;
		ShapeCache*		cache(btConvexShape*);

	private:
		btDynamicsWorld* 	m_ownerWorld;

// 		btAlignedObjectArray<ShapeCache*>	m_shapecaches;
		ShapeCache*		sc;
		

};
#endif
