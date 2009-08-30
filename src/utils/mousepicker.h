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

		void		attach( btRigidBody* pickBody, const btVector3& attachPosition, const btVector3& rayFrom, const btVector3& rayTo );
		void		detach();
		void		moveTo( const btVector3& origin, const btVector3& direction );

		bool*				pickedBool;
	private:
		btDynamicsWorld*		btDynWorld;

		bool				active;
		btPoint2PointConstraint*	constraint;
		btRigidBody*			pickedBody;
		float				oldPickingDist;
};

#endif
