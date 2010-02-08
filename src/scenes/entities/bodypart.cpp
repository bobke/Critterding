#include "bodypart.h"

Bodypart::Bodypart(btDynamicsWorld* ownerWorld, void* owner, const btVector3& dimensions, float weight, btTransform& offset, btTransform& transform)
{
	m_ownerWorld = ownerWorld;

	shape = new btBoxShape( dimensions );

	btVector3 localInertia(0,0,0);
	if (weight != 0.f) // weight of non zero = dynamic
		shape->calculateLocalInertia(weight,localInertia);

	myMotionState = new btDefaultMotionState(offset*transform);
	
	btRigidBody::btRigidBodyConstructionInfo rbInfo(weight,myMotionState,shape,localInertia);
	body = new btRigidBody(rbInfo);

	body->setUserPointer(owner);
	body->setDamping(0.05, 0.85);
	body->setDeactivationTime(0.001);
	body->setSleepingThresholds(1.6, 2.5);

	m_ownerWorld->addRigidBody(body);
}

Bodypart::~Bodypart()
{
	// Remove all bodies and shapes
	m_ownerWorld->removeRigidBody(body);
	m_ownerWorld->getBroadphase()->getOverlappingPairCache()->cleanProxyFromPairs(body->getBroadphaseHandle(),m_ownerWorld->getDispatcher());
	delete body->getMotionState();
	delete body;
	delete shape;
}


