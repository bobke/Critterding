#include "race.h"

WorldRace::WorldRace()
{
}

void WorldRace::init()
{
	testcounter = 1;

	cerr << endl << "Initializing run " << testcounter << " ... " << endl;

	// insert Floor
		makeFloor();

	// autoload critters
	if ( settings->getCVar("autoload") )
		loadAllCritters();

	// insert first batch of critters
		for ( unsigned int i=critters.size(); i < settings->getCVar("mincritters"); i++  )
			insRandomCritter( i );

	// insert food
		for ( unsigned int i=0; i < settings->getCVar("mincritters"); i++  )
			insFood( i );
		
		framecounter = 0;
		haveWinner = false;

	cerr<< "Running" << " ... " << endl;
}

void WorldRace::process()
{
	autosaveCritters();

	// do a bullet step
		m_dynamicsWorld->stepSimulation(0.016667f, 0, 0.016667f);
// 		m_dynamicsWorld->stepSimulation(0.016667f);
// 		m_dynamicsWorld->stepSimulation(Timer::Instance()->bullet_ms / 1000.f);

	// render critter vision, optimized for this sim
		renderVision();
	// Read pixels into retina
		grabVision();

	// process all critters
	for( unsigned int i=0; i < critters.size(); i++)
	{
		CritterB *c = critters[i];

		// TOUCH inputs and references -> find overlappings
			checkCollisions(  c );

		// process
			c->process();

		// process Output Neurons
			if ( c->eat && c->touchingFood )
			{
				Food* f = static_cast<Food*>(c->touchedEntity);
				float eaten = *critter_maxenergy / 100.0f;
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
						critters[i]->fitness_index += ( (float)settings->getCVar("food_maxenergy") /(food[i]->energyLevel + 0.0000001));

				}

			// initialize sort indices
				vector<int> indices ( critters.size(), 0 );
				for ( unsigned int i = 0; i < critters.size(); i++ )
					indices[i] = i;
	
			// sort results
				for ( int i = critters.size(); i>0; i--  )
					for ( int j = 0; j < i-1; j++  )
						if ( critters[indices[j]]->fitness_index < critters[indices[j+1]]->fitness_index )
						{
							unsigned keepI	= indices[j];
							indices[j]	= indices[j+1];
							indices[j+1]	= keepI;
						}

			// display results
				for ( unsigned int i=0; i < critters.size(); i++  )
					cerr << "c " << indices[i] << " : " << critters[indices[i]]->fitness_index << endl;

		cerr << endl << "Initializing run " << ++testcounter << " ... " << endl;

			// backup the 50% best critters
				vector<CritterB*> best;
				unsigned int bestNum = critters.size()/2;
				if ( critters.size() == 1 )
					bestNum = 1;
				for ( unsigned int i=0; i < bestNum; i++  )
					best.push_back( new CritterB(*critters[indices[i]], critters[indices[i]]->critterID, btVector3( 0.0f, 0.0f, 0.0f ), false, false) );
			// remove critters and food
				for ( unsigned int i=0; i < critters.size(); i++ )
				{
					stringstream buf;
					buf << setw(4) << critters[i]->critterID << " old";
					Textverbosemessage::Instance()->addDeath(buf);

					if ( critters[i]->isPicked )
						mousepicker->detach();
// FIXME on windows, we segfault here 1/10 after the first run
					critterselection->unregisterCritterID(critters[i]->critterID);
					critterselection->deselectCritter(critters[i]->critterID);
					delete critters[i];
// FIXME
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
					insMutatedCritter( *best[i], critters.size(), best[i]->critterID, false, false );

			// insert the mutants
				unsigned int count = 0;
				while ( critters.size() < settings->getCVar("mincritters") )
				{
					if ( best.size() > 0 )
					{
						bool brainmutant = false;
						bool bodymutant = false;
						if ( randgen->Instance()->get(1,100) <= settings->getCVar("brain_mutationrate") )
							brainmutant = true;

						if ( randgen->Instance()->get(1,100) <= settings->getCVar("body_mutationrate") )
							bodymutant = true;

						insMutatedCritter( *best[count], critters.size(), currentCritterID++, brainmutant, bodymutant );

						CritterB* c = best[count];
						CritterB* nc = critters[critters.size()-1];
						stringstream buf;
						buf << setw(4) << c->critterID << " : " << setw(4) << nc->critterID;
						buf << " ad: " << setw(4) << nc->genotype->adamdist;
						buf << " n: " << setw(4) << nc->brain.totalNeurons << " s: " << setw(5) << nc->brain.totalSynapses;

						count++;
						if ( count == best.size() && count > 0 )
							count = 0;

						if ( brainmutant || bodymutant )
						{
							buf << " ";
							if ( brainmutant ) buf << "brain";
							if ( brainmutant && bodymutant ) buf << "+";
							if ( bodymutant ) buf << "body";
							buf << " mutant";
						}

						Textverbosemessage::Instance()->addBirth(buf);
					}
					else
						insRandomCritter( critters.size() );
				}

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
}

void WorldRace::makeFloor()
{
	for ( unsigned int i=0; i < walls.size(); i++ )	
		delete walls[i];
	walls.clear();

	critterspacing = (float)settings->getCVar("worldsizeX") / settings->getCVar("mincritters");

	makeDefaultFloor();

	// seperator walls
		float WallWidth = 0.2f;
		float WallHalfWidth = WallWidth/2.0f;
		float WallHeight = 1.0f;
		float WallHalfHeight = WallHeight/2.0f;

		for ( unsigned int i=1; i < settings->getCVar("mincritters"); i++  )
		{
			btVector3 position = btVector3 ( 0.0f-WallHalfWidth + (critterspacing*i), WallHalfHeight-WallWidth, settings->getCVar("worldsizeY")/2.0f );
			Wall* w = new Wall( WallWidth, WallHeight, settings->getCVar("worldsizeY"), position, m_dynamicsWorld );
			w->color.r = 0.34f; w->color.g = 0.25f; w->color.b = 0.11f;
			walls.push_back(w);
		}
}

void WorldRace::insRandomCritter(int nr)
{
	CritterB *c = new CritterB(m_dynamicsWorld, currentCritterID++, btVector3( (critterspacing/2)+(critterspacing*nr), 1.0f, settings->getCVar("worldsizeY")-2.0f ), retina);
	c->energyLevel = settings->getCVar("critter_maxenergy") / 2;
	critters.push_back( c );
	c->calcFramePos(critters.size()-1);
}

void WorldRace::insMutatedCritter(CritterB& other, int nr, unsigned int id, bool mutateBrain, bool mutateBody)
{
	CritterB *nc = new CritterB(other, id, btVector3( (critterspacing/2)+(critterspacing*nr), 1.0f, settings->getCVar("worldsizeY")-2.0f ), mutateBrain, mutateBody);
	nc->energyLevel = settings->getCVar("critter_maxenergy") / 2;
	critters.push_back( nc );
	nc->calcFramePos(critters.size()-1);
}

void WorldRace::insFood(int nr)
{
	Food *f = new Food;
	f->energyLevel = settings->getCVar("food_maxenergy");
	f->createBody( m_dynamicsWorld, btVector3( (critterspacing/2)+(critterspacing*nr), 1.0f, 2.0f ) );
	food.push_back( f );
}

void WorldRace::insertCritter()
{
	cerr << "inserting critters is disabled during race" << endl;
}

void WorldRace::loadAllCritters()
{
	if ( critters.size() > 0 )
	{
		stringstream buf;
		buf << "use --autoload 1 at commandline to autoload critters into a race";
		Logbuffer::Instance()->add(buf);
		cerr << "use --autoload 1 at commandline to autoload critters into a race" << endl;
	}
	else
	{
		vector<string> files;
		dirH.listContentsFull(dirlayout->loaddir, files);

		unsigned int inserted = 0;
		for ( unsigned int i = 0; i < files.size() && inserted < settings->getCVar("mincritters"); i++ )
		{
			if ( parseH->Instance()->endMatches( ".cr", files[i] ) )
			{
				stringstream buf;
				buf << "loading " << files[i];
				Logbuffer::Instance()->add(buf);

				string content;
				fileH.open( files[i], content ); 

				critterspacing = (float)settings->getCVar("worldsizeX") / settings->getCVar("mincritters");
				CritterB *c = new CritterB(content, m_dynamicsWorld, btVector3( (critterspacing/2)+(critterspacing*critters.size()), 1.0f, settings->getCVar("worldsizeY")-(settings->getCVar("worldsizeY")/4) ), retina);

				unsigned int error = 0;
				if ( c->genotype->bodyArch->retinasize != *critter_retinasize ) error = 1;

				if ( !error)
				{
					critters.push_back( c );

					c->critterID = currentCritterID++;
					c->calcFramePos(critters.size()-1);
					c->energyLevel = settings->getCVar("critter_maxenergy") / 2;
					inserted++;
				}
				else
				{
					delete c;
					if ( error == 1 )
					{
						stringstream buf;
						buf << "ERROR: critter retinasize (" << c->genotype->bodyArch->retinasize << ") doesn't fit world retinasize (" << *critter_retinasize << ")" << files[i];
						Logbuffer::Instance()->add(buf);

						cerr << "ERROR: critter retinasize (" << c->genotype->bodyArch->retinasize << ") doesn't fit world retinasize (" << *critter_retinasize << ")" << endl;
					}
				}
			}
		}
		stringstream buf;
		buf << "Loaded critters from " << dirlayout->loaddir;
		Logbuffer::Instance()->add(buf);
		//cerr << endl << "Loaded critters from " << loaddir << endl << endl;
	}
}

WorldRace::~WorldRace()
{
}
