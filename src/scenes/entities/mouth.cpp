#include "mouth.h"

Mouth::Mouth(btDynamicsWorld* ownerWorld, void* owner, const btVector3& dimensions, float weight, btTransform& offset, btTransform& transform)
{
	m_ownerWorld = ownerWorld;

	// Add a box body
		shape = new btBoxShape( dimensions );

		btVector3 localInertia(0,0,0);
		if (weight != 0.f) // weight of non zero = dynamic
			shape->calculateLocalInertia(weight,localInertia);

		btDefaultMotionState* myMotionState = new btDefaultMotionState(offset*transform);
		
		btRigidBody::btRigidBodyConstructionInfo rbInfo(weight,myMotionState,shape,localInertia);
		body = new btRigidBody(rbInfo);

	// 	body->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);

		body->setUserPointer(owner);
		body->setDamping(0.05, 0.85);
		body->setDeactivationTime(0.001);
		body->setSleepingThresholds(1.6, 2.5);

		m_ownerWorld->addRigidBody(body);

	// Mouth piece
		ghostObject = new btPairCachingGhostObject();
// 		ghostObject->setCollisionShape( new btBoxShape( btVector3( x+0.01f, y+0.01f, z+0.01f ) ) );
		ghostObject->setCollisionShape( new btBoxShape( dimensions ) );
		ghostObject->setCollisionFlags( btCollisionObject::CF_KINEMATIC_OBJECT | btCollisionObject::CF_NO_CONTACT_RESPONSE );
		ghostObject->setWorldTransform(offset*transform);

		m_ownerWorld->addCollisionObject(ghostObject);

	// create a pointer to the body's motionstate
}

void Mouth::connectMouthAndBody()
{
	myMotionState = (btDefaultMotionState*)body->getMotionState();
}

void Mouth::updateGhostObjectPosition()
{
	ghostObject->setWorldTransform(myMotionState->m_graphicsWorldTrans);
}

Mouth::~Mouth()
{
	// Remove all bodies and shapes
	m_ownerWorld->removeRigidBody(body);
	delete body->getMotionState();
	delete body;
	delete shape;

	m_ownerWorld->removeCollisionObject(ghostObject);
	delete ghostObject->getCollisionShape();
	delete ghostObject;
}


