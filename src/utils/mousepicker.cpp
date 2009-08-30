#include "mousepicker.h"

Mousepicker::Mousepicker(btDynamicsWorld* btWorld)
{
	btDynWorld = btWorld;

	active = false;
}

void Mousepicker::attach( btRigidBody* pickBody, const btVector3& attachPosition, const btVector3& rayFrom, const btVector3& rayTo )
{
	active = true;

	pickedBody = pickBody;
	pickedBody->setActivationState(DISABLE_DEACTIVATION);

	btVector3 localPivot = pickedBody->getCenterOfMassTransform().inverse() * attachPosition;

	constraint = new btPoint2PointConstraint(*pickedBody,localPivot);
	constraint->m_setting.m_impulseClamp = 30.f;

	btDynWorld->addConstraint(constraint);

	oldPickingDist = (attachPosition - rayFrom).length();

	constraint->m_setting.m_tau = 0.1f;
}

void Mousepicker::detach()
{
	if ( active )
	{
		active = false;

		btDynWorld->removeConstraint(constraint);
		delete constraint;
		pickedBody->forceActivationState(ACTIVE_TAG);
		pickedBody->setDeactivationTime( 0.0f );

		// set the object that was picked back to false
		*pickedBool = false;
	}
}

void Mousepicker::moveTo( const btVector3& origin, const btVector3& direction )
{
	if ( active )
	{
		btVector3 oldPivotInB = constraint->getPivotInB();

		btVector3 dir = origin + direction;
		dir.normalize();
		dir *= oldPickingDist;

		constraint->setPivotB( dir - origin);
	}
}


Mousepicker::~Mousepicker()
{
}
