#include "world.h"

// THREADED FUNC
extern "C" void *procCritters( void *ptr )
{

//	World *w = static_cast<World *>(ptr);
	World *w = (World *)ptr;

	for(;;)
	{
		pthread_cond_wait( &w->condition_startthreads, &w->condition_startthreads_mutex );

		pthread_mutex_lock( &w->cqueue_mutex );
		for ( unsigned int z = 0; z < w->cqueue.size(); z++ )
		{
			unsigned int i = w->cqueue[z];
			w->cqueue.erase(w->cqueue.begin()+z);
			pthread_mutex_unlock( &w->cqueue_mutex );

			w->processCritter(i);

// 			Critter *c = w->critters[i];
// 
// 			// over food input neuron
// 				c->touchingFood = false;
// 				for( unsigned int f=0; f < w->food.size() && !c->touchingFood; f++)
// 				{
// 					Food *fo = w->food[f];
// 					float avgSize = (c->size + fo->size) / 2;
// 					if ( fabs(c->position.x - fo->position.x) <= avgSize && fabs(c->position.z - fo->position.z) <= avgSize )
// 					{
// 						c->touchingFood = true;
// 						c->touchedFoodID = f;
// 					}
// 				}
// 
// 			// process
// 				c->process();
// 
// 			// record critter used energy
// 				pthread_mutex_lock( &w->freeEnergy_mutex );
// 				w->freeEnergy += w->critters[i]->energyUsed;
// 				pthread_mutex_unlock( &w->freeEnergy_mutex );
// 
// 			// move
// 				// wall crawler movement
// 					// left border
// 					if ( c->newposition.x - c->halfsize <= 0 )		c->newposition.x = c->halfsize;
// 					// right border
// 					else if ( c->newposition.x + c->halfsize >= w->size )	c->newposition.x = w->size - c->halfsize;
// 					// bottom border
// 					if ( c->newposition.z - c->halfsize <= 0 )		c->newposition.z = c->halfsize;
// 					// top border
// 					else if ( c->newposition.z + c->halfsize >= w->size )	c->newposition.z = w->size - c->halfsize;
// 
// 				// unless WILL TOUCH other creature, move
// 					bool touch = false;
// 					for ( unsigned int j=0; j < w->critters.size() && !touch; j++ )
// 					{
// 						if ( j != i )
// 						{
// 							Critter *c2 = w->critters[j];
// 
// 							float avgSize = (c->size + c2->size) / 2.0f;
// 							pthread_mutex_lock( &c2->position_mutex );
// 							if ( fabs( c->newposition.x - c2->position.x ) <= avgSize &&  fabs( c->newposition.z - c2->position.z ) <= avgSize )
// 							{
// 								touch = true;
// 							}
// 							pthread_mutex_unlock( &c2->position_mutex );
// 						}
// 					}
// 					pthread_mutex_lock( &c->position_mutex );
// 					if (!touch) c->moveToNewPoss();
// 					pthread_mutex_unlock( &c->position_mutex );
// 
// 				// eat
// 					if ( c->touchingFood && c->eat )
// 					{
// 						// increase energyLevel of critter, decrease of food
// 						//float eaten = ( c->maxEnergyLevel - c->energyLevel ) / 10.0f;
// 						float eaten = c->maxEnergyLevel / 20.0f;
// 		
// 						c->energyLevel				+= eaten;
// 
// 						pthread_mutex_lock( &w->food[c->touchedFoodID]->energy_mutex );
// 						w->food[c->touchedFoodID]->energy	-= eaten;
// 						pthread_mutex_unlock( &w->food[c->touchedFoodID]->energy_mutex );
// 
// 						//cerr << "post E: " << critters[i]->energyLevel << endl;
// 					}
// 
// 				// fire
// 					if ( c->fire && c->canFire )
// 					{
// 						//cerr << "critter " << i << "(ad:" << critters[i]->adamdist << ") FIRES\n";
// 						c->fireTimeCount	= 0;
// 						float used		= c->maxEnergyLevel * 0.05f;
// 						c->energyLevel		-= used;
// 						w->freeEnergy		+= used;
// 		
// 						Bullet *b = new Bullet;
// 		
// 						b->calcDirection(c->rotation);
// 						float reused = c->rotation * 0.0174532925f;
// 						b->position.x = c->position.x - sin(reused) * (c->halfsize + b->size+0.1);
// 						b->position.z = c->position.z - cos(reused) * (c->halfsize + b->size+0.1);
// 
// 						pthread_mutex_lock( &w->bulletsV_mutex );
// 						w->bullets.push_back( b );
// 						pthread_mutex_unlock( &w->bulletsV_mutex );
// 					}
// 
// 				// hit by bullet?
// 					pthread_mutex_lock( &w->bulletsV_mutex );
// 					for( unsigned int f=0; f < w->bullets.size(); f++)
// 					{
// 						Bullet *b = w->bullets[f];
// 						pthread_mutex_unlock( &w->bulletsV_mutex );
// 						float avgSize = (c->size + b->size) / 2;
// 
// 						if ( fabs(c->position.x - b->position.x) <= avgSize && fabs(c->position.z - b->position.z) <= avgSize )
// 						{
// 							c->totalFrames += (c->maxtotalFrames/3) ;
// 							c->wasShot = true;
// 							delete b;
// 							pthread_mutex_lock( &w->bulletsV_mutex );
// 							w->bullets.erase(w->bullets.begin()+f);
// 							pthread_mutex_unlock( &w->bulletsV_mutex );
// 						}
// 						pthread_mutex_lock( &w->bulletsV_mutex );
// 					}
// 					pthread_mutex_unlock( &w->bulletsV_mutex );
// 
// 				// procreate
// 		
// 					//procreation if procreation energy trigger is hit
// 					if ( c->procreateTimeCount > c->procreateTimeTrigger )
// 					{
// 						// if sufficient energy
// 						if ( c->energyLevel > c->minprocenergyLevel )
// 						{
// 							cerr << "critter " << i << "(ad:" << c->adamdist << ") PROCREATES";
// 							// reset procreation energy count
// 							c->procreateTimeCount = 0;
// 		
// 								unsigned int newcritter = w->copyCritter(i);
// 		
// 								// mutate or not
// 								if ( w->randgen.get(1,100) <= w->mutationRate )
// 								{
// 									cerr << ": MUTANT";
// 									w->critters[newcritter]->mutate();
// 								}
// 		
// 								w->critters[newcritter]->setup();
// 								w->positionCritter(newcritter);
// 
// 							cerr << endl;
// 						}
// 					}

			pthread_mutex_lock( &w->cqueue_mutex );
		}
		pthread_mutex_unlock( &w->cqueue_mutex );
	}

	return 0;
}


World::World()
{
//	Infobar *infobar	= Infobar::instance();

	size			= 3;
	foodsize		= 0.1f;
	foodenergy		= 5000.0f;

	freeEnergy		= 0.0f;

	maxcritters		= 1000;
	mincritters		= 0;

	mutationRate		= 20;

	grid.resize(size);
	floor.resize(size);

	insertRandomFood(27, foodenergy); // size^x = 

	// home & program directory
	createDirs();

	// threading prep
	nthreads		= 1;

	// init mutexes
	pthread_mutex_init (&freeEnergy_mutex, NULL);
	pthread_mutex_init (&bulletsV_mutex, NULL);

	pthread_mutex_init (&cqueue_mutex, NULL);

	pthread_mutex_init (&condition_startthreads_mutex, NULL);
	pthread_cond_init (&condition_startthreads, NULL);

	if ( nthreads > 0 )
	{
		for ( unsigned int i=0; i < nthreads; i++ )
		{
			bgthreads.push_back( pthread_t() );
			pthread_create( &bgthreads[i], NULL, ::procCritters, (void *) this);
			pthread_detach( bgthreads[i] );
		}
	}
}

void World::processCritter(unsigned int i)
{
	Critter *c = critters[i];

	// over food input neuron
		c->touchingFood = false;
		for( unsigned int f=0; f < food.size() && !c->touchingFood; f++)
		{
			Food *fo = food[f];
			float avgSize = (c->size + fo->size) / 2;
			if ( fabs(c->position.x - fo->position.x) <= avgSize && fabs(c->position.z - fo->position.z) <= avgSize )
			{
				c->touchingFood = true;
				c->touchedFoodID = f;
			}
		}

	// process
		c->process();

	// record critter used energy
		freeEnergy += c->energyUsed;

	// move
		// wall crawler movement
			// left border
			if ( c->newposition.x - c->halfsize <= 0 )		c->newposition.x = c->halfsize;
			// right border
			else if ( c->newposition.x + c->halfsize >= size )	c->newposition.x = size - c->halfsize;
			// bottom border
			if ( c->newposition.z - c->halfsize <= 0 )		c->newposition.z = c->halfsize;
			// top border
			else if ( c->newposition.z + c->halfsize >= size )	c->newposition.z = size - c->halfsize;

	// unless WILL TOUCH other creature, move
			bool touch = false;
			for ( unsigned int j=0; j < critters.size() && !touch; j++ )
			{
				if ( j != i )
				{
					float avgSize = (critters[i]->size + critters[j]->size) / 2.0f;
					if ( fabs( critters[i]->newposition.x - critters[j]->position.x ) <= avgSize &&  fabs( critters[i]->newposition.z - critters[j]->position.z ) <= avgSize )
					{
						touch = true;
					}
				}
			}
			if (!touch) critters[i]->moveToNewPoss();

	// eat
		if ( c->touchingFood && c->eat )
		{
			//cerr << "pre E: " << critters[i]->energyLevel << endl;
			// increase energyLevel of critter, decrease of food
			//float eaten = ( c->maxEnergyLevel - c->energyLevel ) / 10.0f;

			float eaten = c->maxEnergyLevel / 20.0f;
			if ( c->energyLevel + eaten > c->maxEnergyLevel ) eaten -= (c->energyLevel + eaten) - c->maxEnergyLevel;

			c->energyLevel			+= eaten;
			food[c->touchedFoodID]->energy	-= eaten;

			//cerr << "post E: " << critters[i]->energyLevel << endl;
		}

	// fire
		if ( c->fire && c->canFire )
		{
			//cerr << "critter " << i << "(ad:" << c->adamdist << ") FIRES\n";
			c->fireTimeCount = 0;
			float used = c->maxEnergyLevel * 0.05f;
			c->energyLevel	-= used;
			freeEnergy			+= used;

			Bullet *b = new Bullet;

			b->calcDirection(c->rotation);
			float reused = c->rotation * 0.0174532925f;
			b->position.x = c->position.x - sin(reused) * (c->halfsize + b->size+0.1);
			b->position.z = c->position.z - cos(reused) * (critters[i]->halfsize + b->size+0.1);

			bullets.push_back( b );
		}

	// hit by bullet?
		for( unsigned int f=0; f < bullets.size(); f++)
		{
			Bullet *b = bullets[f];
			float avgSize = (c->size + b->size) / 2;
			if ( fabs(c->position.x - b->position.x) <= avgSize && fabs(c->position.z - b->position.z) <= avgSize )
			{
				c->totalFrames += (c->maxtotalFrames/3) ;
				c->wasShot = true;
				delete b;
				bullets.erase(bullets.begin()+f);
			}
		}

	// procreate

		//procreation if procreation energy trigger is hit
		if ( c->procreateTimeCount > c->procreateTimeTrigger )
		{
			// if sufficient energy
			if ( c->energyLevel > c->minprocenergyLevel )
			{
				cerr << "critter " << i << "(ad:" << c->adamdist << ") PROCREATES";
				// reset procreation energy count
				c->procreateTimeCount = 0;

					unsigned int newcritter = copyCritter(i);

					// mutate or not
					if ( randgen.get(1,100) <= mutationRate )
					{
						cerr << ": MUTANT";
						critters[newcritter]->mutate();
					}

					critters[newcritter]->setup();
					positionCritter(newcritter);
				cerr << endl;
			}
		}

}


void World::process()
{

	// Bullets
	for( unsigned int i=0; i < bullets.size(); i++)
	{
		// forward it fires
		bullets[i]->moveForward();

		// check if outside world
			// left border
			if ( bullets[i]->totalSteps > bullets[i]->maxSteps ) //bullets[i]->position.x - bullets[i]->halfsize <= 0 || bullets[i]->position.x + bullets[i]->halfsize >= size || bullets[i]->position.z - bullets[i]->halfsize <= 0 || bullets[i]->position.z + bullets[i]->halfsize >= size || 
			{
				delete bullets[i];
				bullets.erase(bullets.begin()+i);
			}
	}

	// Remove food
	for( unsigned int i=0; i < food.size(); i++)
	{

		// check if outside world
			// left border
			if ( food[i]->energy < 0 ) //bullets[i]->position.x - bullets[i]->halfsize <= 0 || bullets[i]->position.x + bullets[i]->halfsize >= size || bullets[i]->position.z - bullets[i]->halfsize <= 0 || bullets[i]->position.z + bullets[i]->halfsize >= size || 
			{
				freeEnergy += food[i]->energy;
				delete food[i];
				food.erase(food.begin()+i);
			}
	}

	// Insert Food
	if ( freeEnergy > foodenergy )
	{
		insertRandomFood(1, foodenergy);
		freeEnergy -= foodenergy;
		cerr << "food: " << food.size() << endl;
	}

	// insert critter if < minimum
	if ( critters.size() < mincritters ) insertCritter();

	// remove all dead critters
	for( unsigned int i=0; i < critters.size(); i++)
	{
		// see if energy level isn't below 0 -> die, or die of old age
		if ( critters[i]->energyLevel < 0 )
		{
			cerr << "critter " << i << " DIES: starvation" << endl;
			removeCritter(i);
			i--;
		}
		// see if died from bullet
		else if ( critters[i]->totalFrames > critters[i]->maxtotalFrames && critters[i]->wasShot )
		{
			cerr << "critter " << i << " DIES: KILLED" << endl;
			removeCritter(i);
			i--;
		}
		// die of old age
		else if ( critters[i]->totalFrames > critters[i]->maxtotalFrames )
		{
			cerr << "critter " << i << " DIES: old age" << endl;
			removeCritter(i);
			i--;
		}
	}

	// threads or no threads

	unsigned int lmax = critters.size();

 	if ( nthreads > 0 )
 	{

//		unsigned int bccounter = 0;

		// for all critters do
		for( unsigned int i=0; i < lmax; i++)
		{
			Critter *c = critters[i];

			// vision preparation

				if ( c->drawedAgo == c->drawEvery )
				{
					c->place();
					drawWithFloor();
					c->procFrame();
					c->drawedAgo = 0;
				}
				else c->drawedAgo++;

				pthread_mutex_lock( &cqueue_mutex );
					cqueue.push_back( i );
				pthread_mutex_unlock( &cqueue_mutex );

//				bccounter++;
//				if ( bccounter == nthreads )
//				{
					pthread_mutex_lock( &condition_startthreads_mutex );
						for( unsigned int t=0; t < nthreads; t++) pthread_cond_signal( &condition_startthreads );
					pthread_mutex_unlock( &condition_startthreads_mutex );

//					bccounter=0;
//				}

		}

		// broadcast until cqueue is empty
		pthread_mutex_lock( &cqueue_mutex );
		while ( cqueue.size() > 0 )
		{
			pthread_mutex_unlock( &cqueue_mutex );
				pthread_mutex_lock( &condition_startthreads_mutex );
					for( unsigned int t=0; t < nthreads; t++) pthread_cond_signal( &condition_startthreads );
//					pthread_cond_broadcast( &condition_startthreads );
			//		cerr << "queue at end: " << cqueue.size() << "while critters: " << critters.size() << endl;
				pthread_mutex_unlock( &condition_startthreads_mutex );
			pthread_mutex_lock( &cqueue_mutex );
		}
		pthread_mutex_unlock( &cqueue_mutex );
	}

	// exec without threads
	else
	{
		// for all critters do
		for( unsigned int i=0; i < lmax; i++)
		{
			Critter *c = critters[i];

			// vision preparation
				if ( c->drawedAgo == c->drawEvery )
				{
					c->place();
					drawWithFloor();
					c->procFrame();
					c->drawedAgo = 0;
				}
				else c->drawedAgo++;
// 		}
// 
// 		// for all critters do
// 		for( unsigned int i=0; i < lmax; i++)
// 		{
// 			Critter *c = critters[i];

			processCritter(i);
		}
	}

// 	// remove oldest critter if > maxcritters
// 	if ( critters.size() > maxcritters )
// 	{
// 		cerr << "critter 0" << " DIES: pushed out" << endl;
// 		removeCritter(0);
// 	}


	//critters[0].printVision();

/*	cerr << "b: " << *critters[0]->Neurons[0]->inputs[0]->ref << endl;
	usleep (1000000);*/
}

void World::insertRandomFood(int amount, float energy)
{
	for ( int i=0; i < amount; i++ )
	{
		Food *f = new Food;
		f->position	= findEmptySpace(foodsize);
		f->energy	= energy;
		f->resize(foodsize);
		food.push_back( f );
	}
}

void World::insertCritter()
{
	Critter *c = new Critter;

	c->color[0] = (float)randgen.get( 0,1000 ) / 1000;
	c->color[1] = (float)randgen.get( 0,1000 ) / 1000;
	c->color[2] = (float)randgen.get( 0,1000 ) / 1000;
	c->color[3] = 0.0f;

	c->randomArchitecture();
	c->setup();

	// record it's energy
	freeEnergy -= c->energyLevel;

	critters.push_back( c );
	positionCritter(critters.size()-1);

}

void World::positionCritter(unsigned int cid)
{
	critters[cid]->position	= findEmptySpace(critters[cid]->size);
	critters[cid]->position.y = critters[cid]->halfsize;
	critters[cid]->rotation	= randgen.get( 0, 360 );
	critters[cid]->calcFramePos(cid);
	critters[cid]->calcCamPos();
}

void World::removeCritter(unsigned int cid)
{

	if ( critters[cid]->energyLevel > 0 )
	{
		Food *f = new Food;
		f->position	= critters[cid]->position;
		f->energy	= critters[cid]->energyLevel;
		f->resize(foodsize);
		food.push_back( f );
	}
	else freeEnergy += critters[cid]->energyLevel;

	delete critters[cid];
	critters.erase(critters.begin()+cid);

	for ( unsigned int c = 0; c < critters.size(); c++ )
	{
		critters[c]->calcFramePos(c);
	}
}

unsigned int World::copyCritter(unsigned int cid)
{

	unsigned int newcritterid = critters.size();
	Critter *c = new Critter(*critters[cid]);

	// split energies in half
	c->energyLevel = critters[cid]->energyLevel/2.0f;
	critters[cid]->energyLevel = c->energyLevel;

	critters.push_back( c );
	return newcritterid;
}




bool World::isTouchingAnything(float size, float x, float z)
{
	// touches food?
		for( unsigned int i=0; i < food.size(); i++)
		{
			float avgSize = (size + food[i]->size) / 2;
			if ( fabs(x - food[i]->position.x) <= avgSize && fabs(z - food[i]->position.z) <= avgSize )
			{
				return true;
			}
		}
	// touches critter?
		for( unsigned int i=0; i < critters.size(); i++)
		{
			float avgSize = (size + critters[i]->size) / 2;
			if ( fabs(x - critters[i]->position.x) <= avgSize && fabs(z - critters[i]->position.z) <= avgSize )
			{
				return true;
			}
		}

	return false;
}

Vector3f World::findEmptySpace(float objectsize)
{
	Vector3f pos;
	pos.x = (float)randgen.get( 0, 100*size ) / 100;
	pos.z = (float)randgen.get( 0, 100*size ) / 100;

	float halfsize = objectsize/2;
	while ( isTouchingAnything( objectsize, pos.x, pos.z )
	|| 	(
			// left border
			pos.x - halfsize <= 0 ||
			// right border
			pos.x + halfsize >= size ||
			// bottom border
			pos.z - halfsize <= 0 ||
			// top border
			pos.z + halfsize >= size
		)
	)

	{
		pos.x = (float)randgen.get( 0, 100*size ) / 100;
		pos.z = (float)randgen.get( 0, 100*size ) / 100;
	}
	return pos;
}

void World::drawWithGrid()
{
	// draw floor
	grid.draw();

	// draw food
	for( unsigned int i=0; i < food.size(); i++) food[i]->draw();
	for( unsigned int i=0; i < bullets.size(); i++) bullets[i]->draw();
	for( unsigned int i=0; i < critters.size(); i++) critters[i]->draw();
}

void World::drawWithFloor()
{
	// draw floor
	floor.draw();

	// draw food
	for( unsigned int i=0; i < food.size(); i++) food[i]->draw();
	for( unsigned int i=0; i < bullets.size(); i++) bullets[i]->draw();
	for( unsigned int i=0; i < critters.size(); i++) critters[i]->draw();
}

// min/max critter control

void World::increaseMincritters()
{
	if ( mincritters < maxcritters ) mincritters++;
	cerr << "min c: " << mincritters << "max c: " << maxcritters << endl;
}

void World::decreaseMincritters()
{
	if ( mincritters > 0 ) mincritters--;
	cerr << "min c: " << mincritters << "max c: " << maxcritters << endl;
}

void World::increaseMaxcritters()
{
	maxcritters++;
	cerr << "min c: " << mincritters << "max c: " << maxcritters << endl;
}

void World::decreaseMaxcritters()
{
	if ( maxcritters > mincritters ) maxcritters--;
	cerr << "min c: " << mincritters << "max c: " << maxcritters << endl;
}

void World::increaseBGthreads()
{
	nthreads++;

	if ( nthreads > bgthreads.size() && nthreads < 20 )
	{
		unsigned int i = bgthreads.size();
		bgthreads.push_back( pthread_t() );
		pthread_create( &bgthreads[i], NULL, ::procCritters, (void *) this );
		pthread_detach( bgthreads[i] );
	}
	cerr << "THREADS: " << nthreads << " :-: "<< bgthreads.size() << endl;
}

void World::decreaseBGthreads()
{
	if ( nthreads > 0 )
	{
/*		unsigned int i = bgthreads.size() - 1;

		cerr << "oingk to cancel t " << i << "    " << nthreads << " :-: "<< bgthreads.size() << endl;
		pthread_exit( bgthreads[i] );
		cerr << "cancelled " << nthreads << " :-: "<< bgthreads.size() << endl;

		bgthreads.erase( bgthreads.end()+i );*/
		nthreads--;
	}
	cerr << "THREADS: " << nthreads << " :-: "<< bgthreads.size() << endl;
}

void World::loadAllCritters()
{
	vector<string> files;
	dirH.listContentsFull(loaddir, files);

	for ( unsigned int i = 0; i < files.size(); i++ )
	{
		cout << "loading " << files[i] << endl;
		string content;
		fileH.open( files[i], content );

		Critter *c = new Critter;
		c->setArch(content);
		c->setup();
		// record it's energy
		freeEnergy -= c->energyLevel;
		critters.push_back( c );
		positionCritter(critters.size()-1);
	}
}

void World::saveAllCritters()
{
	// determine save directory
	stringstream buf;
	buf << savedir << "/" << time(0);
	string subsavedir = buf.str();

	// makde dirs
	if ( !dirH.exists(savedir) )	dirH.make(savedir);
	if ( !dirH.exists(subsavedir) )	dirH.make(subsavedir);

	// save each critter
	if ( dirH.exists(subsavedir) )
	{
		for ( unsigned int i = 0; i < critters.size(); i++ )
		{
			string content = critters[i]->getArch();
		
			// determine filename
			stringstream filename;
			filename << subsavedir << "/" << "critter" << i << ".cr";
			string sfilename = filename.str();
		
			// save critters
			fileH.save(sfilename, content);
		}
	}
	else cerr << "cannot save, directory already exists";
}

void World::createDirs()
{
 	homedir = getenv("HOME");
 	if ( homedir.empty() ) {
		cout << "environment variable HOME not defined/detected" << endl;
		exit(0);
	}
	progdir = homedir;	progdir.append("/.critterding");
	savedir = progdir;	savedir.append("/save");
	loaddir = progdir;	loaddir.append("/load");

	cerr << progdir << endl;

	if ( !dirH.exists(progdir) ) dirH.make(progdir);
	if ( !dirH.exists(loaddir) ) dirH.make(loaddir);
}


World::~World()
{
	for ( unsigned int i=0; i < food.size(); i++ )		delete food[i];
	for ( unsigned int i=0; i < bullets.size(); i++ )	delete bullets[i];
	for ( unsigned int i=0; i < critters.size(); i++ )	delete critters[i];
}

