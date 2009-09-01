#include "worldrace.h"

WorldRace::WorldRace()
{
}

void WorldRace::init()
{
		numcritters = 20;

		settings->setCVar( "worldsizeX", 200 );
		settings->setCVar( "worldsizeY", 7 );
		
	// Wall Constants
		float WallWidth = 0.5f;
		float WallHalfWidth = WallWidth/2.0f;
		float WallHeight = 2.0f;
		float WallHalfHeight = WallHeight/2.0f;
	// Ground Floor
		btVector3 position( settings->getCVar("worldsizeX")/2.0f, -WallHalfWidth, settings->getCVar("worldsizeY")/2.0f );
		Wall* w = new Wall( settings->getCVar("worldsizeX"), WallWidth, settings->getCVar("worldsizeY"), position, m_dynamicsWorld );
		w->color[0] = 0.30f; w->color[1] = 0.20f; w->color[2] = 0.10f;
		walls.push_back(w);
	// Left Wall
		position = btVector3 ( 0.0f-WallHalfWidth, WallHalfHeight-WallWidth, settings->getCVar("worldsizeY")/2.0f );
		w = new Wall( WallWidth, WallHeight, settings->getCVar("worldsizeY"), position, m_dynamicsWorld );
		w->color[0] = 0.34f; w->color[1] = 0.25f; w->color[2] = 0.11f;
		walls.push_back(w);
	// Right Wall
		position = btVector3 ( settings->getCVar("worldsizeX")+WallHalfWidth, WallHalfHeight-WallWidth, settings->getCVar("worldsizeY")/2.0f );
		w = new Wall( WallWidth, WallHeight, settings->getCVar("worldsizeY"), position, m_dynamicsWorld );
		w->color[0] = 0.34f; w->color[1] = 0.25f; w->color[2] = 0.11f;
		walls.push_back(w);
	// Top Wall
		position = btVector3 ( settings->getCVar("worldsizeX")/2.0f, WallHalfHeight-WallWidth, 0.0f-WallHalfWidth );
		w = new Wall( settings->getCVar("worldsizeX")+(WallWidth*2), WallHeight, WallWidth, position, m_dynamicsWorld );
		w->color[0] = 0.34f; w->color[1] = 0.25f; w->color[2] = 0.11f;
		walls.push_back(w);
	// Bottom Wall
		position = btVector3 ( settings->getCVar("worldsizeX")/2.0f, WallHalfHeight-WallWidth, settings->getCVar("worldsizeY")+WallHalfWidth );
		w = new Wall( settings->getCVar("worldsizeX")+(WallWidth*2), WallHeight, WallWidth, position, m_dynamicsWorld );
		w->color[0] = 0.34f; w->color[1] = 0.25f; w->color[2] = 0.11f;
		walls.push_back(w);

		critterspacing = (float)settings->getCVar("worldsizeX") / numcritters;

	// seperator walls
		WallWidth = 0.2f;
		WallHalfWidth = WallWidth/2.0f;
		WallHeight = 1.0f;
		WallHalfHeight = WallHeight/2.0f;

	// insert first batch of critters
		for ( unsigned int i=1; i < numcritters; i++  )
		{
			position = btVector3 ( 0.0f-WallHalfWidth + (critterspacing*i), WallHalfHeight-WallWidth, settings->getCVar("worldsizeY")/2.0f );
			w = new Wall( WallWidth, WallHeight, settings->getCVar("worldsizeY"), position, m_dynamicsWorld );
			w->color[0] = 0.34f; w->color[1] = 0.25f; w->color[2] = 0.11f;
			walls.push_back(w);
		}

	// reset cam
		resetCamera();

	// insert first batch of critters
		for ( unsigned int i=0; i < numcritters; i++  )
			insCritter( i );

	// insert food
		for ( unsigned int i=0; i < numcritters; i++  )
			insFood( i );
		
		framecounter = 0;
		testduration = 1000;

		bestCritter = 0;
		bestCritter_distance = settings->getCVar("worldsizeY");
}

void WorldRace::process()
{
	// do a bullet step
		m_dynamicsWorld->stepSimulation(Timer::Instance()->bullet_ms / 1000000.f);

	grabVision();
		
	settings->info_totalNeurons = 0;
	settings->info_totalSynapses = 0;
	settings->info_totalAdamDistance = 0;

	// process all critters
	for( unsigned int i=0; i < critters.size(); i++)
	{
		CritterB *c = critters[i];

		// process
		c->process();

		// count totals of neurons, synapses and adamdistances
			settings->info_totalNeurons		+= c->brain.totalNeurons;
			settings->info_totalSynapses		+= c->brain.totalSynapses;
			settings->info_totalAdamDistance	+= c->adamdist;
	}

	settings->info_critters = critters.size();
	settings->info_food = food.size();

	framecounter++;
	if ( framecounter == testduration  )
	{
		// evaluation
		cerr << endl << "Evaluation..." << endl;

			unsigned int best = 0;
			float shortestdistance = settings->getCVar("worldsizeY");

			// measure their distances from their respective food targets
			for ( unsigned int i=0; i < numcritters; i++  )
			{
				// calculate the distance between food and critter
				btDefaultMotionState* cmyMotionState = (btDefaultMotionState*)critters[i]->body.mouths[0]->body->getMotionState();
				btVector3 cposi = cmyMotionState->m_graphicsWorldTrans.getOrigin();

				btDefaultMotionState* fmyMotionState = (btDefaultMotionState*)food[i]->body.bodyparts[0]->body->getMotionState();
				btVector3 fposi = fmyMotionState->m_graphicsWorldTrans.getOrigin();

				float distance = cposi.distance(fposi);
				if ( distance < shortestdistance )
				{
					best = i;
					shortestdistance = distance;
				}
			}

		cerr << "best critter of run : " << best << " with a distance of " << shortestdistance << endl;

// 		if ( shortestdistance < bestCritter_distance )
// 		{
// 			cerr << "IMPROVEMENT:  " << shortestdistance << " vs " << bestCritter_distance << endl;
			// this is the best critter so far, replaces previous best
			if ( bestCritter )
				delete bestCritter;
			bestCritter = new CritterB(*critters[best], currentCritterID++, btVector3( 0.0f, 0.0f, 0.0f ), false, false);
			bestCritter_distance = shortestdistance;
// 		}
		cerr << endl;

		// reinitialisation

			// backup our best critter

			// remove critters and food
				for ( unsigned int i=0; i < critters.size(); i++ )
					delete critters[i];
				critters.clear();
				for ( unsigned int i=0; i < food.size(); i++ )
					delete food[i];
				critters.clear();
				food.clear();

			// insert mutated batch of critters

				for ( unsigned int i=0; i < numcritters-1; i++  )
				{
					bool brainmutant = false;
					bool bodymutant = false;
					if ( randgen->Instance()->get(1,100) <= settings->getCVar("brain_mutationrate") )
						brainmutant = true;

					if ( randgen->Instance()->get(1,100) <= settings->getCVar("body_mutationrate") )
						bodymutant = true;

					insMutatedCritter( *bestCritter, i, brainmutant, bodymutant );
				}

				for ( unsigned int i=0; i < numcritters; i++  )
					insFood( i );

			// insert best critter in lane 10

				insMutatedCritter( *bestCritter, numcritters-1, false, false );

		framecounter = 0;
	}
}

void WorldRace::insCritter(int nr)
{
	CritterB *c = new CritterB(m_dynamicsWorld, currentCritterID++, btVector3( (critterspacing/2)+(critterspacing*nr), 1.0f, settings->getCVar("worldsizeY")-1.0f ), retina);
	critters.push_back( c );
	c->calcFramePos(critters.size()-1);
}

void WorldRace::insMutatedCritter(CritterB& other, int nr, bool mutateBrain, bool mutateBody)
{
	CritterB *nc = new CritterB(other, currentCritterID++, btVector3( (critterspacing/2)+(critterspacing*nr), 1.0f, settings->getCVar("worldsizeY")-1.0f ), mutateBrain, mutateBody);
	critters.push_back( nc );
	nc->calcFramePos(critters.size()-1);
}

void WorldRace::insFood(int nr)
{
	if ( nr == 0 )
	{
		cerr << "dropping nr 0 at " << (critterspacing/2)+(critterspacing*nr) << endl;
	}
		
	Food *f = new Food;
	f->energyLevel = 5000;

	f->createBody( m_dynamicsWorld, btVector3( (critterspacing/2)+(critterspacing*nr), 1.0f, 1.0f ) );

	food.push_back( f );
}

WorldRace::~WorldRace()
{
}
