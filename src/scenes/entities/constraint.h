#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include <iostream>
#include <vector>
#include "btBulletDynamicsCommon.h"

using namespace std;

class Constraint
{
public:
	Constraint(btDynamicsWorld* ownerWorld, btRigidBody& bodyA, btRigidBody& bodyB, btTransform& localA, btTransform& localB, double limitA, double limitB);
	~Constraint();

	void			motorate();
	float			getAngle();
	
	vector<bool*>		Inputs;
// 	btTypedConstraint*	hinge;
	btHingeConstraint*	hinge;
	float			fullRange;
	float			diffFromZero;
private:
	btDynamicsWorld* 	m_ownerWorld;

	bool			input1;
	bool			input2;
	
// 	float			limitA;
// 	float			limitB;
};
#endif
