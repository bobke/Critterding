#include "food.h"

Food::Food()
{
	settings	= Settings::Instance();
	totalFrames	= 0;
	color[0] = 0.0f;
	color[1] = 0.5f;
	color[2] = 0.0f;

	type = 1;
}

void Food::draw()
{
	for( unsigned int j=0; j < body.bodyparts.size(); j++)
	{
		btRigidBody* bodypart = body.bodyparts[j]->body;
 		btDefaultMotionState* myMotionState = (btDefaultMotionState*)bodypart->getMotionState();
 		myMotionState->m_graphicsWorldTrans.getOpenGLMatrix(position);

		glPushMatrix(); 
		glMultMatrixf(position);

				glColor4f( color[0], color[1], color[2], 0.0f );

				const btBoxShape* boxShape = static_cast<const btBoxShape*>(body.bodyparts[j]->shape);
				btVector3 halfExtent = boxShape->getHalfExtentsWithMargin();
				glScaled(halfExtent[0], halfExtent[1], halfExtent[2]);

				Displaylists::Instance()->call(0);

		glPopMatrix();
	}
}

void Food::createBody(btDynamicsWorld* m_dynamicsWorld, btVector3 startOffset)
{
//	body = new Body ();
	body.m_ownerWorld = m_dynamicsWorld;
	btTransform offset;
	offset.setIdentity();
	offset.setOrigin(startOffset);

	btTransform transform;
	transform.setIdentity();
	transform.setOrigin( btVector3(0.0f, 0.10f, 0.0f) );

	body.addBodyPart_Box((void*)this, 0.10f, 0.10f, 0.10f, 1.0f, offset, transform);
}

Food::~Food()
{
}


