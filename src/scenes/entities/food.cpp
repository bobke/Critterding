#include "food.h"

Food::Food()
{
	settings	= Settings::Instance();
	totalFrames	= 0;
	lifetime	= 0;
	energyLevel	= 0;

	color[0] = 0.0f;
	color[1] = 0.5f;
	color[2] = 0.0f;
	color[3] = 1.0f;

	type = 1;
	isPicked = false;
}

void Food::draw()
{
	myMotionState->m_graphicsWorldTrans.getOpenGLMatrix(position);
/*	btVector3 pos = myMotionState->m_graphicsWorldTrans.getOrigin();
	cerr << pos.getY() */
	
	glPushMatrix(); 
	glMultMatrixf(position);

			glColor4f( color[0], color[1], color[2], 1.0f );
			glScaled(halfExtent[0], halfExtent[1], halfExtent[2]);
			Displaylists::Instance()->call(1);

	glPopMatrix();
}

void Food::createBody(btDynamicsWorld* m_dynamicsWorld, const btVector3& startOffset)
{
	body.m_ownerWorld = m_dynamicsWorld;

	btTransform offset; offset.setIdentity();
	offset.setOrigin(startOffset);

	btTransform transform; transform.setIdentity();
	transform.setOrigin( btVector3(0.0f, 0.10f, 0.0f) );

	body.addBodyPart_Box((void*)this, (float)settings->getCVar("food_size")/1000, (float)settings->getCVar("food_size")/1000, (float)settings->getCVar("food_size")/1000, 1.0f, offset, transform);

	myMotionState = (btDefaultMotionState*)body.bodyparts[0]->body->getMotionState();
	boxShape = static_cast<btBoxShape*>(body.bodyparts[0]->shape);
	halfExtent = boxShape->getHalfExtentsWithMargin();
}

Food::~Food()
{
}


