#include "roundworld.h"

Roundworld::Roundworld()
{
}

void Roundworld::init()
{
	//makeFloor();

	groundTransform.setIdentity();
	groundTransform.setOrigin( btVector3(0,0,0) );

	groundShape = new btSphereShape(btScalar( *worldsizeX ));
	
	fixedGround = new btCollisionObject();
	fixedGround->setUserPointer(this);
	fixedGround->setCollisionShape(groundShape);
	fixedGround->setWorldTransform(groundTransform);
	m_dynamicsWorld->addCollisionObject(fixedGround);
	
	if ( settings->getCVar("autoload") )
		loadAllCritters();
	if ( settings->getCVar("autoloadlastsaved") )
		loadAllLastSavedCritters();
}

void Roundworld::process()
{
	if ( !pause )
	{
		killHalf();
		expireFood();
		autoinsertFood();
		expireCritters();
		autoexchangeCritters();
		autosaveCritters();
		autoinsertCritters();
		// adjust gravity vectors of all entities' rigid bodies
		unsigned int j, b;
		Food* f;
		CritterB* bod;
		btRigidBody* bo;
		
		for( j=0; j < entities.size(); j++)
		{	
			if ( entities[j]->type == FOOD )
			{
// 				f = food[j];
				Food* f = static_cast<Food*>( entities[j] );
				for( b=0; b < f->body.bodyparts.size(); b++)
				{
					bo = f->body.bodyparts[b]->body;
					bo->setGravity( -(bo->getCenterOfMassPosition().normalized()*10) );
				}
			}
		}
		for( j=0; j < critters.size(); j++)
		{
			bod = critters[j];
			for( b=0; b < bod->body.bodyparts.size(); b++)
			{
				bo = bod->body.bodyparts[b]->body;
				bo->setGravity( -(bo->getCenterOfMassPosition().normalized()*10) );
			}
		}
		
		if ( *critter_raycastvision == 0 )
		{
			renderVision();
			grabVision();
		}

		// do a bullet step
			m_dynamicsWorld->stepSimulation(0.016667f, 0, 0.016667f);
	// 		m_dynamicsWorld->stepSimulation(Timer::Instance()->bullet_ms / 1000.f);

		int lmax = (int)critters.size();
		CritterB *c;
		float freeEnergyc = 0.0f;

		// FIXME USE FROM WORLDB
		omp_set_num_threads( *threads );
		#pragma omp parallel for ordered shared(freeEnergyc, lmax) private(c) // ordered 
		for( int i=0; i < lmax; i++)
		{
			c = critters[i];
			
			omp_set_lock(&my_lock1);
				checkCollisions(  c );
			omp_unset_lock(&my_lock1);

			// process
				c->process();

			// record critter used energy
				freeEnergyc += c->energyUsed;

			// process Output Neurons
				eat(c);

			// procreation if procreation energy trigger is hit
			omp_set_lock(&my_lock1);
				procreate(c);
			omp_unset_lock(&my_lock1);
		}

		freeEnergy += freeEnergyc;

		getGeneralStats();
	}
}

void Roundworld::makeFloor()
{
	m_dynamicsWorld->removeCollisionObject(fixedGround);
	delete groundShape;
	delete fixedGround;

	groundShape = new btSphereShape(btScalar( *worldsizeX ));
	
	fixedGround = new btCollisionObject();
	fixedGround->setUserPointer(this);
	fixedGround->setCollisionShape(groundShape);
	fixedGround->setWorldTransform(groundTransform);
	m_dynamicsWorld->addCollisionObject(fixedGround);
}


void Roundworld::drawWithGrid()
{
	glClear(GL_STENCIL_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glPushMatrix(); 
		glTranslatef(0,0,0);
		glColor4f( 0.3f, 0.2f, 0.1f, 1.0f );
		drawSphere(
			*worldsizeX,
			(12.56637* *worldsizeX / 6),
			(12.56637* *worldsizeX / 3)
		);
	glPopMatrix(); 
	for( unsigned int i=0; i < critters.size(); i++)
		critters[i]->draw(true);

	for( unsigned int i=0; i < entities.size(); i++)
		entities[i]->draw();

	if ( *drawshadows )
	{
		btVector3 aabbMin,aabbMax;
		m_dynamicsWorld->getBroadphase()->getBroadphaseAabb(aabbMin,aabbMax);
		aabbMin-=btVector3(BT_LARGE_FLOAT,BT_LARGE_FLOAT,BT_LARGE_FLOAT);
		aabbMax+=btVector3(BT_LARGE_FLOAT,BT_LARGE_FLOAT,BT_LARGE_FLOAT);
		btScalar mmatrix[16];
		btVector3 sundir = btVector3(0.3f, -1.0f, 0.3f);


		glDisable(GL_LIGHTING);
		glDepthMask(GL_FALSE);
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_STENCIL_TEST);
		glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
		glStencilFunc(GL_ALWAYS,1,0xFFFFFFFFL);
		glFrontFace(GL_CCW);
		glStencilOp(GL_KEEP,GL_KEEP,GL_INCR);

		for( unsigned int i=0; i < critters.size(); i++)
		{
			for ( unsigned int bp = 0; bp < critters[i]->body.bodyparts.size(); bp++ )
			{
				critters[i]->body.bodyparts[bp]->myMotionState->m_graphicsWorldTrans.getOpenGLMatrix(mmatrix);
				drawShadow(mmatrix, sundir * critters[i]->body.bodyparts[bp]->myMotionState->m_graphicsWorldTrans.getBasis() ,critters[i]->body.bodyparts[bp]->shape, critters[i]->body.bodyparts[bp], aabbMin,aabbMax);
			}
		}
		for( unsigned int i=0; i < entities.size(); i++)
		{
			if ( entities[i]->type == FOOD )
			{
				Food* f = static_cast<Food*>(entities[i]);
				f->myMotionState->m_graphicsWorldTrans.getOpenGLMatrix(mmatrix);
				drawShadow(mmatrix,sundir * f->myMotionState->m_graphicsWorldTrans.getBasis(),f->body.bodyparts[0]->shape, f->body.bodyparts[0], aabbMin, aabbMax);

			}
		}

		glFrontFace(GL_CW);
		glStencilOp(GL_KEEP,GL_KEEP,GL_DECR);

		for( unsigned int i=0; i < critters.size(); i++)
		{
			for ( unsigned int bp = 0; bp < critters[i]->body.bodyparts.size(); bp++ )
			{
				critters[i]->body.bodyparts[bp]->myMotionState->m_graphicsWorldTrans.getOpenGLMatrix(mmatrix);
				drawShadow(mmatrix, sundir * critters[i]->body.bodyparts[bp]->myMotionState->m_graphicsWorldTrans.getBasis() ,critters[i]->body.bodyparts[bp]->shape, critters[i]->body.bodyparts[bp], aabbMin,aabbMax);
			}
		}
		for( unsigned int i=0; i < entities.size(); i++)
		{
			if ( entities[i]->type == FOOD )
			{
				Food* f = static_cast<Food*>(entities[i]);
				f->myMotionState->m_graphicsWorldTrans.getOpenGLMatrix(mmatrix);
				drawShadow(mmatrix,sundir * f->myMotionState->m_graphicsWorldTrans.getBasis(),f->body.bodyparts[0]->shape, f->body.bodyparts[0], aabbMin, aabbMax);

			}
		}

		glDepthMask(GL_TRUE);
		glFrontFace(GL_CCW);
		glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
		glDepthFunc(GL_LEQUAL);
		glStencilFunc( GL_NOTEQUAL, 0, 0xFFFFFFFFL );
		glStencilOp( GL_KEEP, GL_KEEP, GL_KEEP );
		glDisable(GL_LIGHTING);

		for( unsigned int i=0; i < critters.size(); i++)
			critters[i]->drawDimmed(0.6f);

		for( unsigned int i=0; i < entities.size(); i++)
			entities[i]->drawDimmed(0.6f);
		glPushMatrix(); 
			glTranslatef(0,0,0);
			glColor4f( 0.3f * 0.6f, 0.2f * 0.6f, 0.1f * 0.6f, 1.0f );
			drawSphere(
				*worldsizeX,
				(12.56637* *worldsizeX / 6),
				(12.56637* *worldsizeX / 3)
			);
		glPopMatrix(); 

	}
	glDisable(GL_STENCIL_TEST);
	glDisable(GL_CULL_FACE);}

void Roundworld::childPositionOffset(btVector3* v)
{
	*v+= (v->normalized()*insertHight);
}

btVector3 Roundworld::findPosition()
{
	return btVector3(	((float)randgen->Instance()->get( 0, 200 )-100.0f) / 100,
				((float)randgen->Instance()->get( 0, 200 )-100.0f) / 100,
				((float)randgen->Instance()->get( 0, 200 )-100.0f) / 100
	).normalized() * ( *worldsizeX + insertHight);
}

void Roundworld::drawfloor()
{
	glPushMatrix(); 
		glTranslatef(0,0,0);
		glColor4f( 0.3f, 0.2f, 0.1f, 1.0f );
		drawSphere(
			*worldsizeX,
			(12.56637* *worldsizeX / 12),
			(12.56637* *worldsizeX / 6)
		);
	glPopMatrix(); 
}

void Roundworld::drawSphere(btScalar radius, int lats, int longs) 
{
	int i, j;
	for(i = 0; i <= lats; i++) {
		btScalar lat0 = SIMD_PI * (-btScalar(0.5) + (btScalar) (i - 1) / lats);
		btScalar z0  = radius*sin(lat0);
		btScalar zr0 =  radius*cos(lat0);

		btScalar lat1 = SIMD_PI * (-btScalar(0.5) + (btScalar) i / lats);
		btScalar z1 = radius*sin(lat1);
		btScalar zr1 = radius*cos(lat1);

		glBegin(GL_QUAD_STRIP);
		for(j = 0; j <= longs; j++) {
			btScalar lng = 2 * SIMD_PI * (btScalar) (j - 1) / longs;
			btScalar x = cos(lng);
			btScalar y = sin(lng);
			glNormal3f(x * zr1, y * zr1, z1);
			glVertex3f(x * zr1, y * zr1, z1);
			glNormal3f(x * zr0, y * zr0, z0);
			glVertex3f(x * zr0, y * zr0, z0);
		}
		glEnd();
	}
}

Roundworld::~Roundworld()
{
	m_dynamicsWorld->removeCollisionObject(fixedGround);
	delete groundShape;
	delete fixedGround;
}
