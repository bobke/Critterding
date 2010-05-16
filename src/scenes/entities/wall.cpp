#include "wall.h"

Wall::Wall(float X, float Y, float Z, btVector3 position, btDynamicsWorld* m_dynamicsWorld)
{
	m_ownerWorld = m_dynamicsWorld;

	halfX		= X/2;
	halfY		= Y/2;
	halfZ		= Z/2;

	color.r		= 0.0f;
	color.g		= 0.0f;
	color.b		= 0.5f;
	color.a		= 0.0f;

	groundShape = new btBoxShape( btVector3( halfX ,halfY, halfZ ) );
	
	groundTransform.setIdentity();
	groundTransform.setOrigin( position );

	fixedGround = new btCollisionObject();
	fixedGround->setUserPointer(this);
	fixedGround->setCollisionShape(groundShape);
	fixedGround->setWorldTransform(groundTransform);
	m_ownerWorld->addCollisionObject(fixedGround);

	fixedGround->getWorldTransform().getOpenGLMatrix(nposition);
	
	type = WALL;
	isPicked = false;
}

void Wall::draw()
{
	glColor4f( color.r, color.g, color.b, color.a );
	glPushMatrix(); 
	glMultMatrixf(nposition);

		glScaled(halfX, halfY, halfZ);
		Displaylists::Instance()->call(1);

	glPopMatrix(); 
}

void Wall::drawDimmed(float dim)
{
	glColor4f( color.r*0.3f, color.g*0.3f, color.b*0.3f, color.a );
	glPushMatrix(); 
	glMultMatrixf(nposition);

		glScaled(halfX, halfY, halfZ);
		Displaylists::Instance()->call(1);

	glPopMatrix(); 
}

Wall::~Wall()
{
	m_ownerWorld->removeCollisionObject(fixedGround);
	delete groundShape;
	delete fixedGround;
}


