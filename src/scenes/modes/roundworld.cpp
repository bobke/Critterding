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
}

void Roundworld::process()
{
	killHalf();
	expireFood();
	autoinsertFood();
	expireCritters();
	autosaveCritters();
	autoinsertCritters();

	// adjust gravity vectors of all entities' rigid bodies
	unsigned int j, b;
	Food* f;
	CritterB* bod;
	btRigidBody* bo;
	
	unsigned int biggest = food.size();
	if ( critters.size() > biggest )
		biggest = critters.size();
	
#pragma omp parallel for private(j, b, f, bod, bo)
	for ( j=0; j < biggest; j++ )
	{
// 		for( j=0; j < food.size(); j++)
		if( j < food.size() )
		{
			f = food[j];
			for( b=0; b < f->body.bodyparts.size(); b++)
			{
				bo = f->body.bodyparts[b]->body;
				bo->setGravity( -(bo->getCenterOfMassPosition().normalized()*10) );
			}
		}
// 		#pragma omp parallel for private(j, b)
// 		for( j=0; j < critters.size(); j++)
		if( j < critters.size() )
		{
			bod = critters[j];
			for( b=0; b < bod->body.bodyparts.size(); b++)
			{
				bo = bod->body.bodyparts[b]->body;
				bo->setGravity( -(bo->getCenterOfMassPosition().normalized()*10) );
			}
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
	int i;

	float freeEnergyc = 0.0f;

	// FIXME USE FROM WORLDB
// 	omp_set_num_threads(settings->getCVar("threads"));	
// 	#pragma omp parallel for shared(freeEnergyc) private(i, c)
	for( i=0; i < lmax; i++)
	{
		c = critters[i];

// 		omp_set_lock(&my_lock1);
			checkCollisions(  c );
// 		omp_unset_lock(&my_lock1);

		c->process();

		freeEnergy += c->energyUsed;

		eat(c);

// 		omp_set_lock(&my_lock1);
		procreate(c);
// 		omp_unset_lock(&my_lock1);
	}

	freeEnergy += freeEnergyc;
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
// 	drawfloor();
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

	for( unsigned int i=0; i < food.size(); i++)
		food[i]->draw();
}

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
