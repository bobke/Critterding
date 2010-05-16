#include "testworld1.h"

TestWorld1::TestWorld1()
{
}

void TestWorld1::init()
{
	makeFloor();

	// extra Ground Floor

	float WallWidth = 0.1f;
	float WallHalfWidth = WallWidth/2.0f;

	decSizeFactor = 0.5f;
	elevations = 10;

	insertHight = 1.0f + (WallWidth*elevations);

	for ( unsigned int i=0; i < elevations; i++ )
	{
		btVector3 position( (float)settings->getCVar("worldsizeX")/2.0f, (i*WallWidth)+WallHalfWidth, (float)settings->getCVar("worldsizeY")/2.0f );
		Wall* w = new Wall( (float)settings->getCVar("worldsizeX")/(decSizeFactor*(i+2)), WallWidth, (float)settings->getCVar("worldsizeY")/(decSizeFactor*(i+2)), position, m_dynamicsWorld );
		w->color.r = 0.34f+(0.005f*i); w->color.g = 0.25f+(0.005f*i); w->color.b = 0.11f+(0.005f*i);
		entities.push_back(w);
	}
}

void TestWorld1::process()
{
	killHalf();
	expireFood();
	autoinsertFood();
	expireCritters();
	autosaveCritters();
	autoinsertCritters();

// 	m_dynamicsWorld->stepSimulation(0.016667f);
	m_dynamicsWorld->stepSimulation(0.016667f, 0, 0.016667f);
// 	m_dynamicsWorld->stepSimulation(Timer::Instance()->bullet_ms / 1000.f);

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

btVector3 TestWorld1::findPosition()
{
	for ( unsigned int i=0; i < elevations; i++ )
	{
		if ( randgen->Instance()->get( i, elevations-1 ) == i )
		{
			return btVector3( 
				(float)settings->getCVar("worldsizeX")/2.0f - (float)settings->getCVar("worldsizeX")/(decSizeFactor*2*(i+2)) + ((float)randgen->Instance()->get( 0, (float)settings->getCVar("worldsizeX")/(decSizeFactor*(i+2))*100 ) / 100),
				insertHight, 
				(float)settings->getCVar("worldsizeY")/2.0f - (float)settings->getCVar("worldsizeY")/(decSizeFactor*2*(i+2)) + ((float)randgen->Instance()->get( 0, (float)settings->getCVar("worldsizeY")/(decSizeFactor*(i+2))*100 ) / 100)
			);
		}
	}
}

TestWorld1::~TestWorld1()
{
}
