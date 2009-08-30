#ifndef MOUSEPICKER_H
#define MOUSEPICKER_H

#include "btBulletDynamicsCommon.h"
#include <iostream>
using namespace std;

class Mousepicker
{
	public:
		Mousepicker(btDynamicsWorld* btWorld);
		~Mousepicker();

		void attach( btRigidBody* pickBody, const btVector3& attachPosition, const btVector3& rayFrom, const btVector3& rayTo );
		void detach();
		void moveTo( const btVector3& origin, const btVector3& direction );

		bool			active;
		bool*			pickedBool;
		btTypedConstraint*	m_pickConstraint;
		float			gOldPickingDist;

	private:
		btDynamicsWorld*	btDynWorld;

		// picking
		int			gPickingConstraintId;
		btVector3		gOldPickingPos;
		btVector3		gHitPos;
		btRigidBody*		pickedBody;
		btScalar		mousePickClamping;
};

#endif
