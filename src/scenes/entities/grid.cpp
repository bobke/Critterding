#include "grid.h"

Grid::Grid()
{
 	gridsizeX	= 0;
 	gridsizeY	= 0;

	color[0]	= 0.0f;
	color[1]	= 0.0f;
	color[2]	= 0.5f;
	color[3]	= 0.0f;
}

void Grid::draw()
{
	fixedGround->getWorldTransform().getOpenGLMatrix(m);
	glPushMatrix(); 
	glMultMatrixf(m);

		glColor4f( color[0], color[1], color[2], color[3] );

		const btBoxShape* boxShape = static_cast<const btBoxShape*>(groundShape);
		btVector3 halfExtent = boxShape->getHalfExtentsWithMargin();
		glScaled(halfExtent[0], halfExtent[1], halfExtent[2]);

		Displaylists::Instance()->call(0);

	glPopMatrix(); 

}

void Grid::resize(unsigned int X, unsigned int Y, btDynamicsWorld* m_dynamicsWorld)
{
	gridsizeX = X;
	gridsizeY = Y;

	groundShape = new btBoxShape( btVector3( (float)X/2 ,0.1f,(float)Y/2 ) );
	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(((float)X/2),0,((float)Y/2)));

	fixedGround = new btCollisionObject();
	fixedGround->setCollisionShape(groundShape);
	fixedGround->setWorldTransform(groundTransform);
	m_dynamicsWorld->addCollisionObject(fixedGround);
}

Grid::~Grid()
{
}


