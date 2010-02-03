#include "testworld2.h"

TestWorld2::TestWorld2()
{
}

void TestWorld2::init()
{
	//makeFloor();

	btCollisionShape* world = new btSphereShape(btScalar( settings->getCVar("worldsizeX") ));

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin( btVector3(0,0,0) );

	btCollisionObject* fixedGround;
	fixedGround = new btCollisionObject();
	fixedGround->setUserPointer(this);
	fixedGround->setCollisionShape(world);
	fixedGround->setWorldTransform(groundTransform);
	m_dynamicsWorld->addCollisionObject(fixedGround);
	
}

void TestWorld2::process()
{
	killHalf();
	expireFood();
	autoinsertFood();
	expireCritters();
	autosaveCritters();
	autoinsertCritters();

	// adjust gravity vectors of all entities' rigid bodies
	for( unsigned int j=0; j < food.size(); j++)
	{
		Food *f = food[j];
		for( unsigned int b=0; b < f->body.bodyparts.size(); b++)
		{
			btRigidBody* bo = f->body.bodyparts[b]->body;
			bo->setGravity( -(bo->getCenterOfMassPosition().normalized()*10) );
		}
	}
	for( unsigned int j=0; j < critters.size(); j++)
	{
		CritterB *f = critters[j];
		for( unsigned int b=0; b < f->body.bodyparts.size(); b++)
		{
			btRigidBody* bo = f->body.bodyparts[b]->body;
			bo->setGravity( -(bo->getCenterOfMassPosition().normalized()*10) );
		}
	}
	
	m_dynamicsWorld->stepSimulation(Timer::Instance()->bullet_ms / 1000.f);

	renderVision();
	grabVision();

	unsigned int lmax = critters.size();
	for( unsigned int i=0; i < lmax; i++)
	{
		CritterB *c = critters[i];

		checkCollisions(  c );
		c->process();
		freeEnergy += c->energyUsed;
		eat(c);
		procreate(c);
	}
}

void TestWorld2::drawWithGrid()
{
// 	drawfloor();
	glPushMatrix(); 
		glTranslatef(0,0,0);
		glColor4f( 0.3f, 0.2f, 0.1f, 1.0f );
		drawSphere(
			settings->getCVar("worldsizeX"),
			(12.56637*settings->getCVar("worldsizeX") / 6),
			(12.56637*settings->getCVar("worldsizeX") / 3)
		);
	glPopMatrix(); 

	for( unsigned int i=0; i < critters.size(); i++)
		critters[i]->draw(true);

	for( unsigned int i=0; i < food.size(); i++)
		food[i]->draw();
}

void TestWorld2::childPositionOffset(btVector3* v)
{
	*v+= (v->normalized()*insertHight);
}

btVector3 TestWorld2::findPosition()
{
	return btVector3(	((float)randgen->Instance()->get( 0, 200 )-100.0f) / 100,
				((float)randgen->Instance()->get( 0, 200 )-100.0f) / 100,
				((float)randgen->Instance()->get( 0, 200 )-100.0f) / 100
	).normalized() * (settings->getCVar("worldsizeX") + insertHight);
}

void TestWorld2::drawfloor()
{
	glPushMatrix(); 
		glTranslatef(0,0,0);
		glColor4f( 0.3f, 0.2f, 0.1f, 1.0f );
		drawSphere(
			settings->getCVar("worldsizeX"),
			(12.56637*settings->getCVar("worldsizeX") / 12),
			(12.56637*settings->getCVar("worldsizeX") / 6)
		);
	glPopMatrix(); 
}

void TestWorld2::drawSphere(btScalar radius, int lats, int longs) 
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

TestWorld2::~TestWorld2()
{
}
