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

		settings->info_totalNeurons = 0;
		settings->info_totalSynapses = 0;
		settings->info_totalAdamDistance = 0;
		settings->info_totalBodyparts = 0;
		settings->info_totalWeight = 0;
		settings->info_critters = critters.size();
		settings->info_food = food.size();
}

TestWorld1::~TestWorld1()
{
}
