#include "mousepicker.h"

Mousepicker::Mousepicker(btDynamicsWorld* btWorld)
{
	btDynWorld = btWorld;

	gPickingConstraintId = 0;
	gHitPos = btVector3(-1,-1,-1);
	gOldPickingDist  = 0.f;
	pickedBody = 0;//for deactivation state
	m_pickConstraint = 0;
	mousePickClamping = 30.f;
}

void Mousepicker::attach( btRigidBody* pickBody, const btVector3& attachPosition, const btVector3& rayFrom, const btVector3& rayTo )
{
	pickedBody = pickBody;
	pickedBody->setActivationState(DISABLE_DEACTIVATION);

	btVector3 localPivot = pickedBody->getCenterOfMassTransform().inverse() * attachPosition;

	btPoint2PointConstraint* p2p = new btPoint2PointConstraint(*pickedBody,localPivot);
	p2p->m_setting.m_impulseClamp = mousePickClamping;

	btDynWorld->addConstraint(p2p);
	m_pickConstraint = p2p;

	//save mouse position for dragging
	gOldPickingPos = rayTo;
	gHitPos = attachPosition;

	gOldPickingDist  = (attachPosition - rayFrom).length();

	//very weak constraint for picking
	p2p->m_setting.m_tau = 0.1f;
}

void Mousepicker::detach()
{
	if (m_pickConstraint)
	{
		btDynWorld->removeConstraint(m_pickConstraint);
		delete m_pickConstraint;
		//printf("removed constraint %i",gPickingConstraintId);
		m_pickConstraint = 0;
		pickedBody->forceActivationState(ACTIVE_TAG);
		pickedBody->setDeactivationTime( 0.f );
		pickedBody = 0;

		// set the object that was picked back to false
		*pickedBool = false;
	}
}

Mousepicker::~Mousepicker()
{
}
