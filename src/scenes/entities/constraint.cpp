#include "constraint.h"

Constraint::Constraint(btDynamicsWorld* ownerWorld, btRigidBody& bodyA, btRigidBody& bodyB, btTransform& localA, btTransform& localB, double limitA, double limitB)
{
	// init constraint inputs
	Inputs.push_back(&input1); // 0: direction +
	Inputs.push_back(&input2); // 1: direction -
	
	m_ownerWorld = ownerWorld;

	hinge = new btHingeConstraint( bodyA, bodyB, localA, localB );
	hinge->setLimit( limitA, limitB );
	m_ownerWorld->addConstraint( hinge, true );

	// Calculate full and half range of hinge, HACK could be more efficient
		float smallestLimit = limitA;
		if ( limitB < limitA )
			smallestLimit = limitB;

		diffFromZero = 0.0f - smallestLimit ;
		//cerr << "diff" << diffFromZero << endl;

		fullRange = 0.0f;
		if ( limitA > 0.0f ) fullRange += limitA;
		else fullRange += (limitA * -1.0f);
		if ( limitB > 0.0f ) fullRange += limitB;
		else fullRange += (limitB * -1.0f);

	hinge->setDbgDrawSize(5.0f);
}

float Constraint::getAngle()
{
	float percentAngle = (hinge->getHingeAngle() + diffFromZero) / fullRange;
	if ( percentAngle > 1.0f )
		percentAngle = 1.0f;
	if ( percentAngle < 0.0f )
		percentAngle = 0.0f;

	return percentAngle;
}

void Constraint::motorate()
{
	
	float direction = 0.0f;
	if ( input1 )
		direction +=10.0f;
	if ( input2 )
		direction -=10.0f;

	if ( direction != 0.0f )
	{
		hinge->enableAngularMotor(true, direction, 5000.0f);
	}
}

Constraint::~Constraint()
{
	m_ownerWorld->removeConstraint( hinge );
	delete hinge;
}


