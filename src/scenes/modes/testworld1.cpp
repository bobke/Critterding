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

	// render critter vision, optimized for this sim
		for( unsigned int i=0; i < critters.size(); i++)
			if ( critters[i]->body.mouths.size() > 0 )
			{
				critters[i]->place();
				food[i]->draw();

				for( unsigned int i=0; i < walls.size(); i++)
					walls[i]->draw();
			}

		// Read pixels into retina
		grabVision();

	settings->info_totalNeurons = 0;
	settings->info_totalSynapses = 0;
	settings->info_totalAdamDistance = 0;
	settings->info_totalBodyparts = 0;
	settings->info_totalWeight = 0;

	// process all critters
	for( unsigned int i=0; i < critters.size(); i++)
	{
		CritterB *c = critters[i];

		// TOUCH inputs and references -> find overlappings
			checkCollisions(  c );

		// process
			c->process();

		// count totals of neurons, synapses and adamdistances
			settings->info_totalNeurons		+= c->brain.totalNeurons;
			settings->info_totalSynapses		+= c->brain.totalSynapses;
			settings->info_totalAdamDistance	+= c->adamdist;
			settings->info_totalBodyparts		+= c->body.bodyparts.size();
			settings->info_totalWeight		+= c->body.totalWeight;
	}

	settings->info_critters = critters.size();
	settings->info_food = food.size();
}

TestWorld1::~TestWorld1()
{
}
