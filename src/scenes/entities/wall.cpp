#include "wall.h"

Wall::Wall(float X, float Y, float Z, btVector3 position, btDynamicsWorld* m_dynamicsWorld)
{
	m_ownerWorld = m_dynamicsWorld;

	halfX		= X/2;
	halfY		= Y/2;
	halfZ		= Z/2;

	color[0]	= 0.0f;
	color[1]	= 0.0f;
	color[2]	= 0.5f;
	color[3]	= 0.0f;

	groundShape = new btBoxShape( btVector3( halfX ,halfY, halfZ ) );
	
	groundTransform.setIdentity();
	groundTransform.setOrigin( position );

	fixedGround = new btCollisionObject();
	fixedGround->setCollisionShape(groundShape);
	fixedGround->setWorldTransform(groundTransform);
	m_ownerWorld->addCollisionObject(fixedGround);

	fixedGround->getWorldTransform().getOpenGLMatrix(nposition);
}

void Wall::draw()
{
// 	fixedGround->getWorldTransform().getOpenGLMatrix(m);
	glPushMatrix(); 
	glMultMatrixf(nposition);

		glColor4f( color[0], color[1], color[2], color[3] );

/*		const btBoxShape* boxShape = static_cast<const btBoxShape*>(groundShape);
		btVector3 halfExtent = boxShape->getHalfExtentsWithMargin();*/
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


