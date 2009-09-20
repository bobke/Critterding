#include "testworld1.h"

TestWorld1::TestWorld1()
{
}

void TestWorld1::init()
{
	makeFloor();
}

void TestWorld1::process()
{
	// do a bullet step
		m_dynamicsWorld->stepSimulation(Timer::Instance()->bullet_ms / 1000000.f);

	// render and grab vision
		renderVision();
		grabVision();

	// process all critters
		unsigned int lmax = critters.size();
		for( unsigned int i=0; i < lmax; i++)
		{
			CritterB *c = critters[i];
			c->process();
		}
}

TestWorld1::~TestWorld1()
{
}
