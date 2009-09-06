#include "worldrace.h"

WorldRace::WorldRace()
{
}

void WorldRace::init()
{
	testcounter = 1;

	// reset cam
		resetCamera();

	cerr << endl << "Initializing run " << testcounter << " ... " << endl;

	// insert Floor
		makeFloor();

	// insert first batch of critters
		for ( unsigned int i=0; i < settings->getCVar("mincritters"); i++  )
			insCritter( i );

	// insert food
		for ( unsigned int i=0; i < settings->getCVar("mincritters"); i++  )
			insFood( i );
		
		framecounter = 0;
		haveWinner = false;

	cerr<< "Running" << " ... " << endl;
}

void WorldRace::makeFloor()
{
	for ( unsigned int i=0; i < walls.size(); i++ )	
		delete walls[i];
	walls.clear();

	critterspacing = (float)settings->getCVar("worldsizeX") / settings->getCVar("mincritters");

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

	// seperator walls
		WallWidth = 0.2f;
		WallHalfWidth = WallWidth/2.0f;
		WallHeight = 1.0f;
		WallHalfHeight = WallHeight/2.0f;

		for ( unsigned int i=1; i < settings->getCVar("mincritters"); i++  )
		{
			position = btVector3 ( 0.0f-WallHalfWidth + (critterspacing*i), WallHalfHeight-WallWidth, settings->getCVar("worldsizeY")/2.0f );
			w = new Wall( WallWidth, WallHeight, settings->getCVar("worldsizeY"), position, m_dynamicsWorld );
			w->color[0] = 0.34f; w->color[1] = 0.25f; w->color[2] = 0.11f;
			walls.push_back(w);
		}
}

void WorldRace::clearFloor()
{
}

void WorldRace::process()
{
// 	cerr << "1" << endl;
	// do a bullet step
		m_dynamicsWorld->stepSimulation(Timer::Instance()->bullet_ms / 1000000.f);

// 	cerr << critters.size() << endl;
	// render critter vision
		for( unsigned int i=0; i < critters.size(); i++)
		{
			if ( critters[i]->body.mouths.size() > 0 )
			{
				critters[i]->place();
				food[i]->draw();

				for( unsigned int i=0; i < walls.size(); i++)
					walls[i]->draw();
			}
		}

// 	cerr << "2" << endl;
		// Read pixels into retina
		if ( critters.size() > 0 )
		{
			// determine width
			unsigned int picwidth = *retinasperrow * (*critter_retinasize+1);

			// determine height
			unsigned int picheight = *critter_retinasize;
			unsigned int rows = critters.size();
			while ( rows > *retinasperrow )
			{
				picheight += *critter_retinasize;
				rows -= *retinasperrow;
			}
			glReadBuffer(GL_BACK);
			glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
			glReadPixels(0, 0, picwidth, picheight, GL_RGBA, GL_UNSIGNED_BYTE, retina);
		}
// 	cerr << "3" << endl;


	settings->info_totalNeurons = 0;
	settings->info_totalSynapses = 0;
	settings->info_totalAdamDistance = 0;

	// process all critters
	for( unsigned int i=0; i < critters.size(); i++)
	{
		CritterB *c = critters[i];

		// set inputs to false and recheck
			c->touchingFood = false;

		// TOUCH inputs and references -> find overlappings
			if ( c->body.mouths.size() > 0 )
			{
				btManifoldArray   manifoldArray;
				btBroadphasePairArray& pairArray = c->body.mouths[0]->ghostObject->getOverlappingPairCache()->getOverlappingPairArray();
				int numPairs = pairArray.size();

				for ( int i=0; i < numPairs; i++ )
				{
					manifoldArray.clear();

					const btBroadphasePair& pair = pairArray[i];

					//unless we manually perform collision detection on this pair, the contacts are in the dynamics world paircache:
					btBroadphasePair* collisionPair = m_dynamicsWorld->getPairCache()->findPair(pair.m_pProxy0,pair.m_pProxy1);
					if (!collisionPair)
						continue;

					if (collisionPair->m_algorithm)
						collisionPair->m_algorithm->getAllContactManifolds(manifoldArray);

					bool stop = false;
					for ( int j = 0; j < manifoldArray.size() && !stop; j++ )
					{
						btPersistentManifold* manifold = manifoldArray[j];
						
						btCollisionObject* object1 = static_cast<btCollisionObject*>(manifold->getBody0());
						btCollisionObject* object2 = static_cast<btCollisionObject*>(manifold->getBody1());

						if ( object1->getUserPointer() == c && object2->getUserPointer() == c )
							continue;

						for ( int p = 0; p < manifold->getNumContacts(); p++ )
						{
							const btManifoldPoint &pt = manifold->getContactPoint(p);
							if ( pt.getDistance() < 0.f )
							{
								void* Collidingobject;
								if ( object1->getUserPointer() != c && object1->getUserPointer() != 0 )
									Collidingobject = object1->getUserPointer();
								else
									Collidingobject = object2->getUserPointer();

								// Touching Food
								Food* f = static_cast<Food*>(Collidingobject);
								if ( f )
								{
									if ( f->type == 1 )
									{
										stop = true;
										c->touchingFood = true;
										c->touchedFoodID = f;
									}
								}
							}
						}
					}
				}
			}

		// process
		c->process();

		// process Output Neurons
			if ( c->eat )
			{
				if ( c->touchingFood )
				{
					Food* f = c->touchedFoodID;
					float eaten = *critter_maxenergy / 50.0f;
					if ( c->energyLevel + eaten > *critter_maxenergy )
						eaten -= (c->energyLevel + eaten) - *critter_maxenergy;
					if ( f->energyLevel - eaten < 0 )
						eaten = f->energyLevel;

					c->energyLevel += eaten;
					f->energyLevel -= eaten;
					
					// if a food unit has no more energy left, we have a winner, the race is over
					if ( f->energyLevel  == 0.0f )
						haveWinner = true;
				}
			}

		// count totals of neurons, synapses and adamdistances
			settings->info_totalNeurons		+= c->brain.totalNeurons;
			settings->info_totalSynapses		+= c->brain.totalSynapses;
			settings->info_totalAdamDistance	+= c->adamdist;
	}

	settings->info_critters = critters.size();
	settings->info_food = food.size();

	framecounter++;
	if ( (haveWinner || framecounter >= settings->getCVar("critter_maxlifetime")) )
	{
		if ( haveWinner )
			cerr << "we have a WINNER after " << framecounter << " frames" << endl;

		cerr << "Evaluating..." << endl;

			// measure their distances from their respective food targets
			for ( unsigned int i=0; i < critters.size(); i++  )
			{
				// fitness function 1: distance to food cube
					btDefaultMotionState* cmyMotionState = (btDefaultMotionState*)critters[i]->body.mouths[0]->body->getMotionState();
					btVector3 cposi = cmyMotionState->m_graphicsWorldTrans.getOrigin();

					btDefaultMotionState* fmyMotionState = (btDefaultMotionState*)food[i]->body.bodyparts[0]->body->getMotionState();
					btVector3 fposi = fmyMotionState->m_graphicsWorldTrans.getOrigin();

					critters[i]->fitness_index =  1.0f /(cposi.distance(fposi) + 0.0000001); 
				
				// fitness function 2: energy of food consumed
					critters[i]->fitness_index += ( 10.0f /(food[i]->energyLevel + 0.0000001));

			}

			// initialize sort indices for
			vector<int> indices ( critters.size(), 0 );
			for ( unsigned int i = 0; i < critters.size(); i++ )
				indices[i] = i;
	
			// sort results
// 			cerr << "sorting" << endl;
			for ( int i = critters.size(); i>0; i--  )
				for ( int j = 0; j < i-1; j++  )
					if ( critters[indices[j]]->fitness_index < critters[indices[j+1]]->fitness_index )
					{
						unsigned keepI	= indices[j];
						indices[j]	= indices[j+1];
						indices[j+1]	= keepI;
					}
// 			cerr << "done sorting" << endl;

			// display results
			for ( unsigned int i=0; i < critters.size(); i++  )
			{
				cerr << "c " << indices[i] << " : " << critters[indices[i]]->fitness_index << endl;
			}

		cerr << endl << "Initializing run " << ++testcounter << " ... " << endl;

			// backup the 50% best critters
				vector<CritterB*> best;

				unsigned int bestNum = critters.size()/2;
				if ( critters.size() == 1 )
					bestNum = 1;
				for ( unsigned int i=0; i < bestNum; i++  )
				{
					CritterB* b = new CritterB(*critters[indices[i]], currentCritterID++, btVector3( 0.0f, 0.0f, 0.0f ), false, false);
					best.push_back( b );
// 					cerr << " backing up " << indices[i] << endl;
				}

			// remove critters and food
				for ( unsigned int i=0; i < critters.size(); i++ )
				{
					if ( critters[i]->isPicked )
						mousepicker->detach();
					delete critters[i];
				}
				critters.clear();
				for ( unsigned int i=0; i < food.size(); i++ )
				{
					if ( food[i]->isPicked )
						mousepicker->detach();
					delete food[i];
				}
				food.clear();

			// clear floor and remake it
				makeFloor();

			// reinsert the best critters
				for ( unsigned int i=0; i < best.size() && i < settings->getCVar("mincritters"); i++  )
				{
					insMutatedCritter( *best[i], critters.size(), false, false );
				}

			// insert the mutants
// 				cerr << "inserting critters" << endl;

				unsigned int count = 0;
				while ( critters.size() < settings->getCVar("mincritters") )
				{
// 					cerr << " inserting " << critters.size() << endl;
					if ( best.size() > 0 )
					{
						bool brainmutant = false;
						bool bodymutant = false;
						if ( randgen->Instance()->get(1,100) <= settings->getCVar("brain_mutationrate") )
							brainmutant = true;

						if ( randgen->Instance()->get(1,100) <= settings->getCVar("body_mutationrate") )
							bodymutant = true;

// 						cerr << "1" << endl;
						insMutatedCritter( *best[count], critters.size(), brainmutant, bodymutant );
// 						cerr << "2" << endl;

						count++;
						if ( count == best.size() && count > 0 )
							count = 0;
					}
					else
						insCritter( critters.size() );
				}

// 				cerr << "done inserting critters" << endl;
// 				for ( unsigned int i=0; i < best.size(); i++  )
// 				{
// 					bool brainmutant = false;
// 					bool bodymutant = false;
// 					if ( randgen->Instance()->get(1,100) <= settings->getCVar("brain_mutationrate") )
// 						brainmutant = true;
// 
// 					if ( randgen->Instance()->get(1,100) <= settings->getCVar("body_mutationrate") )
// 						bodymutant = true;
// 
// 					insMutatedCritter( *best[i], critters.size(), brainmutant, bodymutant );
// 				}

			// remove best again
				for ( unsigned int i=0; i < best.size(); i++  )
					delete best[i];

			// reinsert respective food units
				for ( unsigned int i=0; i < settings->getCVar("mincritters"); i++  )
					insFood( i );

			framecounter = 0;
			haveWinner = false;

			cerr << "Running... " << endl;
	}
	clearFloor();
}

// FIXME: overwrite maxenergylevel
void WorldRace::insCritter(int nr)
{
	CritterB *c = new CritterB(m_dynamicsWorld, currentCritterID++, btVector3( (critterspacing/2)+(critterspacing*nr), 1.0f, settings->getCVar("worldsizeY")-1.0f ), retina);
	c->energyLevel = 500;
	critters.push_back( c );
	c->calcFramePos(critters.size()-1);
}

void WorldRace::insMutatedCritter(CritterB& other, int nr, bool mutateBrain, bool mutateBody)
{
	CritterB *nc;
	// give an edge to the one in lane 2
// 	if ( nr == 1 )
// 		nc = new CritterB(other, currentCritterID++, btVector3( (critterspacing/2)+(critterspacing*nr), 1.0f, settings->getCVar("worldsizeY")-3.0f ), mutateBrain, mutateBody);
// 	else
		nc = new CritterB(other, currentCritterID++, btVector3( (critterspacing/2)+(critterspacing*nr), 1.0f, settings->getCVar("worldsizeY")-1.0f ), mutateBrain, mutateBody);
	nc->energyLevel = 500;
	critters.push_back( nc );
	nc->calcFramePos(critters.size()-1);
}

void WorldRace::insFood(int nr)
{
	Food *f = new Food;
	f->energyLevel = 4000;

	f->createBody( m_dynamicsWorld, btVector3( (critterspacing/2)+(critterspacing*nr), 1.0f, 1.0f ) );

	food.push_back( f );
}

WorldRace::~WorldRace()
{
}
