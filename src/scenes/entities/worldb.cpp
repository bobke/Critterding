#include "worldb.h"

extern "C" void *procCritters( void *ptr )
{

	WorldB *b = static_cast<WorldB *>(ptr);

	// register this thread
	unsigned int threadID;
	pthread_mutex_lock( &b->busyThreads_mutex );
		threadID = b->registeredThreads++;
		cerr << "registered thread " << threadID << endl;
	pthread_mutex_unlock( &b->busyThreads_mutex );

	while (1)
	{
		// thread stuff
				pthread_mutex_lock( &b->busyThreads_mutex );
					if ( --b->busyThreads == 0 )
					{
						pthread_mutex_lock( &b->condition_threadsdone_mutex );
							pthread_cond_signal( &b->condition_threadsdone );
						pthread_mutex_unlock( &b->condition_threadsdone_mutex );
					}
				pthread_mutex_unlock( &b->busyThreads_mutex );
	
					//cerr << "thread " << threadID << " initiated" << endl;

			pthread_mutex_lock( &b->condition_startthreads_mutex );
			pthread_cond_wait( &b->condition_startthreads, &b->condition_startthreads_mutex );
			pthread_mutex_unlock( &b->condition_startthreads_mutex );

		// process

			unsigned int csize = b->critters.size();
			unsigned int fsize = b->food.size();
			for ( unsigned int i=threadID; i < csize; i+=b->nthreads )
			{
					CritterB *c = b->critters[i];

					// over food input neuron
						c->touchingFood = false;
						for( unsigned int f=0; f < fsize && !c->touchingFood; f++)
						{
							Food *fo = b->food[f];
							float avgSize = (c->size + fo->size) / 2;
							if ( fabs(c->position.x - fo->position.x) <= avgSize && fabs(c->position.z - fo->position.z) <= avgSize )
							{
								c->touchingFood = true;
								c->touchedFoodID = f;
							}
						}

					c->process();

					// record critter used energy
					pthread_mutex_lock( &b->freeEnergy_mutex );
						b->freeEnergy += c->energyUsed;
					pthread_mutex_unlock( &b->freeEnergy_mutex );
				
					// move
					pthread_mutex_lock( &b->position_mutex );
						if (b->spotIsFree(c->newposition, c->size, i))
						{
							//pthread_mutex_lock( &c->position_mutex );
							c->moveToNewPoss();
							//pthread_mutex_unlock( &c->position_mutex );
						}
					pthread_mutex_unlock( &b->position_mutex );
	

			}

	}
	return 0;
}

WorldB::WorldB()
{
//	Infobar *infobar	= Infobar::instance();

	selectedCritter		= 0;
	isSelected		= false;

	doTimedInserts		= false;
	timedInsertsCounter	= 0;

	foodsize		= 0.1f;
	foodenergy		= 2500.0f;

	mincritters		= 10;

	mutationRate		= 10; // %
	maxMutateRuns		= 3;

	flipnewbornes		= false;

	// home & program directory
	createDirs();

	// vision retina allocation

	// register input/output neurons
	//items = 4* 1000 * (1 + (10*2));

	items = 10000 * 4 * (10+1) * 10;

	cerr << items << endl;

	retina = (unsigned char*)malloc(items);
	memset(retina, 0, items);

	// threads
	nthreads			= 1;
	registeredThreads		= 0;
	busyThreads			= nthreads;

	if ( nthreads > 1 )
	{

		pthread_mutex_init (&condition_startthreads_mutex, NULL);
		pthread_cond_init (&condition_startthreads, NULL);
	
		pthread_mutex_init (&condition_threadsdone_mutex, NULL);
		pthread_cond_init (&condition_threadsdone, NULL);
	
		pthread_mutex_init (&busyThreads_mutex, NULL);
		pthread_mutex_init (&freeEnergy_mutex, NULL);
		pthread_mutex_init (&position_mutex, NULL);
	
	
		// init threads
		for ( unsigned int i = 0; i < nthreads; i++ )
		{
			threads.push_back( pthread_t() );
			pthread_create( &threads[i], NULL, ::procCritters, (void *) this );
			pthread_detach( threads[i] );
		}
	
		// wait untill all threads are created before continuing
		pthread_mutex_lock( &busyThreads_mutex );
		while ( busyThreads > 0 )
		{
			pthread_mutex_unlock( &busyThreads_mutex );
				usleep (100);
			pthread_mutex_lock( &busyThreads_mutex );
		}
		pthread_mutex_unlock( &busyThreads_mutex );
	}

}

void WorldB::resize(unsigned int newsize)
{
	size = newsize;
	grid.resize(size);
	floor.resize(size);
}

void WorldB::startfoodamount(unsigned int amount)
{
	freeEnergy		= foodenergy * amount;
	freeEnergyInfo		= freeEnergy;
}

void WorldB::process()
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
				i--;
			}
		
	}

	// Remove food
	for( unsigned int i=0; i < food.size(); i++)
	{
		// food was eaten
		if ( food[i]->energy < 0 )
		{
			freeEnergy += food[i]->energy;
			delete food[i];
			food.erase(food.begin()+i);
			i--;
		}

		// old food, this should remove stuff from corners
		else if ( ++food[i]->totalFrames >= food[i]->maxtotalFrames )
		{
			freeEnergy += food[i]->energy;
			delete food[i];
			food.erase(food.begin()+i);
			i--;
		}
	}

	// Insert Food
	while ( freeEnergy >= foodenergy )
	{
		insertRandomFood(1, foodenergy);
		freeEnergy -= foodenergy;
		//cerr << "food: " << food.size() << endl;
	}

	// insert critter if < minimum
	if ( critters.size() < mincritters ) insertCritter();

	// remove all dead critters
	for( unsigned int i=0; i < critters.size(); i++)
	{
		// see if energy level isn't below 0 -> die, or die of old age
		if ( critters[i]->energyLevel < 0.0f )
		{
			cerr << setw(3) << i << "/" << setw(3) << critters.size()-1 << " DIES: starvation" << endl;
			removeCritter(i);
			i--;
		}
		// see if died from bullet
		else if ( critters[i]->totalFrames > critters[i]->maxtotalFrames && critters[i]->wasShot )
		{
			cerr << setw(3) << i << "/" << setw(3) << critters.size()-1 << " DIES: killed" << endl;
			removeCritter(i);
			i--;
		}
		// die of old age
		else if ( critters[i]->totalFrames > critters[i]->maxtotalFrames )
		{
			cerr << setw(3) << i << "/" << setw(3) << critters.size()-1 << " DIES: old age" << endl;
			removeCritter(i);
			i--;
		}
	}

	// for all critters do
	for( unsigned int i=0; i < critters.size(); i++)
	{
		CritterB *c = critters[i];

		c->place();

		float preppedSize = 5.0f + c->halfsize;

		// draw everything in it's sight
			floor.draw();
		
			for( unsigned int j=0; j < critters.size(); j++)
			{
				CritterB *oc = critters[j];
				float avgSize = preppedSize - oc->halfsize;
				if ( fabs( c->position.x - oc->position.x ) <= avgSize && fabs( c->position.z - oc->position.z ) <= avgSize )
				{
					oc->draw();
				}
			}
		
			for( unsigned int j=0; j < food.size(); j++)
			{
				Food *f = food[j];
				float avgSize = preppedSize - f->halfsize;
				if ( fabs( c->position.x - f->position.x ) <= avgSize && fabs( c->position.z - f->position.z ) <= avgSize )
				{
					f->draw();
				}
			}
		
			for( unsigned int j=0; j < walls.size(); j++)
			{
				Wall *w = walls[j];
				float avgSize = preppedSize - w->halfsize;
				if ( fabs( c->position.x - w->position.x ) <= avgSize && fabs( c->position.z - w->position.z ) <= avgSize )
				{
					w->draw();
				}
			}
		
			for( unsigned int j=0; j < bullets.size(); j++)
			{
				Bullet *b = bullets[j];
				float avgSize = preppedSize - b->halfsize;
				if ( fabs( c->position.x - b->position.x ) <= avgSize && fabs( c->position.z - b->position.z ) <= avgSize )
				{
					b->draw();
				}
			}
	}

	if ( critters.size() > 0 )
	{
		unsigned int itemsperrow = 10;

		// determine width
		unsigned int picwidth = (itemsperrow * (10+1));

		// determine height
		unsigned int picheight = 10;
		unsigned int rows = critters.size();
		while ( rows > itemsperrow )
		{
			picheight += 10;
			rows -= itemsperrow;
		}

		glReadPixels(0, 0, picwidth, picheight, GL_RGBA, GL_UNSIGNED_BYTE, retina);
	}


	if ( nthreads > 1 && critters.size()>1 )
	{
		// tell threads to start & wait for end
			busyThreads = nthreads;
	
			pthread_mutex_lock( &condition_threadsdone_mutex );
			// start the threads
				pthread_mutex_lock( &condition_startthreads_mutex );
					//cerr << "signaling start threads" << endl;
					pthread_cond_broadcast( &condition_startthreads );
				pthread_mutex_unlock( &condition_startthreads_mutex );
	
			// wait for threads to end
				pthread_cond_wait( &condition_threadsdone, &condition_threadsdone_mutex );

			pthread_mutex_unlock( &condition_threadsdone_mutex );
	}
	else
	{
		for( unsigned int i=0; i < critters.size(); i++)
		{
			CritterB *c = critters[i];
	
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
				if (spotIsFree(c->newposition, c->size, i))
				{
					c->moveToNewPoss();
				}
		}
	}

	// seems to go faster in 3 loops, caching wise
	unsigned int lmax = critters.size();
	for( unsigned int i=0; i < lmax; i++)
	{
		CritterB *c = critters[i];

		// eat
			if ( c->touchingFood && c->eat )
			{
				//cerr << "pre E: " << critters[i]->energyLevel << endl;
				// increase energyLevel of critter, decrease of food
				//float eaten = ( c->maxEnergyLevel - c->energyLevel ) / 10.0f;
	
				float eaten = c->maxEnergyLevel / 50.0f;
				if ( c->energyLevel + eaten > c->maxEnergyLevel ) eaten -= (c->energyLevel + eaten) - c->maxEnergyLevel;
	
				c->energyLevel		+= eaten;
	
				Food *fo = food[c->touchedFoodID];
	
				fo->energy		-= eaten;
	
				fo->resize();
			}
	
		// fire
			if ( c->fire && c->canFire )
			{
				//cerr << "critter " << i << "(ad:" << c->adamdist << ") FIRES\n";
				c->fireTimeCount = 0;
				float used = c->maxEnergyLevel * 0.01f;
				c->energyLevel	-= used;
				freeEnergy			+= used;
	
				Bullet *b = new Bullet;
	
				b->calcDirection(c->rotation);
				float reused = c->rotation * 0.0174532925f;
				b->position.x = c->position.x - sin(reused) * (c->halfsize + b->size+0.1);
				b->position.z = c->position.z - cos(reused) * (c->halfsize + b->size+0.1);
	
				bullets.push_back( b );
			}
	
		// hit by bullet?
			for( unsigned int f=0; f < bullets.size() && !c->wasShot; f++)
			{
				Bullet *b = bullets[f];
				float avgSize = (c->size + b->size) / 2;
				if ( fabs(c->position.x - b->position.x) <= avgSize && fabs(c->position.z - b->position.z) <= avgSize )
				{
					c->totalFrames += (c->maxtotalFrames/10) ;
					c->wasShot = true;
					delete b;
					bullets.erase(bullets.begin()+f);
				}
			}
	
		// procreate
			//procreation if procreation energy trigger is hit
			if ( c->procreate && c->canProcreate )
			{
	
				// move critter it's half size to the left
				float reused = (90.0f+c->rotation) * 0.0174532925f;
				c->prepNewPoss();
				c->newposition.x -= sin(reused) * c->halfsize;
				c->newposition.z -= cos(reused) * c->halfsize;
	
				if (spotIsFree(c->newposition, c->size, i))
				{
					CritterB *nc = new CritterB(*c);

					// mutate or not
					bool mutant = false;
					if ( randgen.get(1,100) <= mutationRate )
					{
						mutant = true;
						nc->mutate(maxMutateRuns);
					}

					// same positions / rotation
					nc->position = c->position;
					nc->rotation = c->rotation;

					nc->setup();
					nc->retina = retina;

					// move new critter to the right by sum of halfsizes
					float reused = (270.0f+nc->rotation) * 0.0174532925f;
					Vector3f newpos;
					nc->prepNewPoss();
					nc->newposition.x -= sin(reused) * (c->halfsize + nc->halfsize + 0.01);
					nc->newposition.z -= cos(reused) * (c->halfsize + nc->halfsize + 0.01);

					if (spotIsFree(nc->newposition, nc->size, i))
					{
						cerr << setw(3) << i << "/" << setw(3) << critters.size()-1 << " PROC: (ad: " << setw(4) << c->adamdist << ")";

						cerr << " N: " << setw(4) << nc->brain.totalNeurons << " C: " << setw(5) << nc->brain.totalSynapses;
						if ( mutant ) cerr << " (m)";

						// optional rotate 180 of new borne
						if ( flipnewbornes ) nc->rotation = nc->rotation + 180.0f;

						// split energies in half
						nc->energyLevel = c->energyLevel/2.0f;
						c->energyLevel = nc->energyLevel;

						// reset procreation energy count
						c->procreateTimeCount = 0;
	
						nc->calcFramePos(critters.size());

						critters.push_back( nc );

						c->moveToNewPoss();
						nc->moveToNewPoss();

						cerr << endl;
					}
					else
					{
						delete nc;
					}
				}
			}
	}


/*	cerr << "b: " << *critters[0]->Neurons[0]->inputs[0]->ref << endl;
	usleep (1000000);*/

	if ( doTimedInserts )
	{
		timedInsertsCounter++;

		if ( timedInsertsCounter == 6000 )
		{
			cerr << "inserting 100 food" << endl;

			freeEnergyInfo += foodenergy * 200.0f;
			freeEnergy += foodenergy * 200.0f;
		}
		else if ( timedInsertsCounter == 6001 )
		{
			cerr << "removing 100 food" << endl;

			freeEnergyInfo -= foodenergy * 200.0f;
			freeEnergy -= foodenergy * 200.0f;

			timedInsertsCounter = 0;
		}
	}
}

void WorldB::toggleTimedInserts()
{
	 if ( doTimedInserts ) doTimedInserts = false;
	 else
	 {
		 doTimedInserts = true;
		 timedInsertsCounter = 0;
	 }
}

void WorldB::insertRandomFood(int amount, float energy)
{
	for ( int i=0; i < amount; i++ )
	{
		Food *f = new Food;
		f->position	= findEmptySpace(foodsize);
		f->energy	= energy;

		f->resize();
		//f->resize((foodsize/foodenergy) * energy);
		food.push_back( f );
	}
}

void WorldB::insertCritter()
{
	CritterB *c = new CritterB;

	c->brain.buildArch();
	c->setup();
	c->retina = retina;

	// record it's energy
	freeEnergy -= c->energyLevel;

	critters.push_back( c );
	positionCritterB(critters.size()-1);
}

void WorldB::positionCritterB(unsigned int cid)
{
	critters[cid]->position	= findEmptySpace(critters[cid]->size);
	critters[cid]->position.y = critters[cid]->halfsize;
	critters[cid]->rotation	= randgen.get( 0, 360 );
	critters[cid]->calcFramePos(cid);
	critters[cid]->calcCamPos();
}

void WorldB::removeCritter(unsigned int cid)
{
	if ( critters[cid]->energyLevel > 0.0f )
	{
		Food *f = new Food;
		f->position = critters[cid]->position;

		if ( critters[cid]->energyLevel > 2500.0f )
		{
			f->energy = 2500.0f;
		}
		else
		{
			f->energy = critters[cid]->energyLevel;
		}


		freeEnergy += critters[cid]->energyLevel;
		freeEnergy -= f->energy;

		// put 50% of energy in food, rest back in space

		//f->resize(foodsize);
		f->resize();
		food.push_back( f );
	}
	else freeEnergy += critters[cid]->energyLevel;

	// adapt selection
	if ( isSelected )
	{
		if ( selectedCritter == cid )
		{
			selectedCritter = critters.size()-1;
//			selectedCritter = 0;
//			isSelected = false;
		}
		else if ( selectedCritter > cid )
		{
			selectedCritter--;
		}
	}

	delete critters[cid];
	critters.erase(critters.begin()+cid);

	for ( unsigned int c = cid; c < critters.size(); c++ )
	{
		critters[c]->calcFramePos(c);
	}
}

void WorldB::createWall()
{
	walls.clear();
	for ( unsigned int i=0; i < (unsigned int)(4.0f*size); i++ )
	{
		Wall *w = new Wall();
		walls.push_back( w );
		walls[i]->resize(0.25f);
		walls[i]->position.x = 0.125 + ((float)i*0.25);
		walls[i]->position.z = size/2.0f;
	}
}

void WorldB::destroyWall()
{
	while ( !walls.empty() )
	{
		delete walls[0];
		walls.erase( walls.begin() );
	}
}

void WorldB::toggleGate(unsigned int wid)
{
	if ( wid < walls.size() ) walls[wid]->toggle();
}


void WorldB::drawWithGrid()
{
	// draw floor
	grid.draw();

	for( unsigned int i=0; i < food.size(); i++) food[i]->draw();
	for( unsigned int i=0; i < walls.size(); i++) walls[i]->draw();
	for( unsigned int i=0; i < bullets.size(); i++) bullets[i]->draw();
	for( unsigned int i=0; i < critters.size(); i++) critters[i]->draw();
}

// min critter control
void WorldB::increaseMincritters()
{
	mincritters++;
	cerr << "min c: " << mincritters << endl;
}

void WorldB::decreaseMincritters()
{
	if ( mincritters > 0 ) mincritters--;
	cerr << "min c: " << mincritters << endl;
}

void WorldB::setMincritters(unsigned int c)
{
	mincritters = c;
	cerr << "min c: " << mincritters << endl;
}

void WorldB::loadAllCritters()
{
	vector<string> files;
	dirH.listContentsFull(loaddir, files);

	for ( unsigned int i = 0; i < files.size(); i++ )
	{
		cout << "loading " << files[i] << endl;
		string content;
		fileH.open( files[i], content );

		CritterB *c = new CritterB(content);
		c->setup();
		c->retina = retina;
		// record it's energy
		freeEnergy -= c->energyLevel;
		critters.push_back( c );
		positionCritterB(critters.size()-1);
	}
}

void WorldB::saveAllCritters()
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
			string content = critters[i]->saveCritterB();
		
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

void WorldB::createDirs()
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

bool WorldB::spotIsFree(Vector3f &position, float osize, unsigned int exclude)
{

	float halfsize = osize/2.0f;

// within world borders?

	// left border
	if ( position.x - halfsize <= 0 )		return false;
	// right border
	else if ( position.x + halfsize >= size )	return false;
	// bottom border
	if ( position.z - halfsize <= 0 )		return false;
	// top border
	else if ( position.z + halfsize >= size )	return false;

// check for touch walls

	for ( unsigned int j=0; j < walls.size(); j++ )
	{
		Wall *w = walls[j];

		if ( !w->disabled )
		{
			float avgSize = (osize + w->size) / 2.0f;
			if ( fabs( position.x - w->position.x ) <= avgSize && fabs( position.z - w->position.z ) <= avgSize )
			{
				return false;
			}
		}
	}

// check for touch other creatures

	for ( unsigned int j=0; j < critters.size(); j++ )
	{
		if ( j != exclude )
		{
			CritterB *cj = critters[j];
			float avgSize = (osize + cj->size) / 2.0f;
			if ( fabs( position.x - cj->position.x ) <= avgSize &&  fabs( position.z - cj->position.z ) <= avgSize )
			{
				return false;
			}
		}
	}

	return true;
}

bool WorldB::spotIsFree(Vector3f &position, float osize)
{

	float halfsize = osize/2.0f;

// within world borders?

	// left border
	if ( position.x - halfsize <= 0 )		return false;
	// right border
	else if ( position.x + halfsize >= size )	return false;
	// bottom border
	if ( position.z - halfsize <= 0 )		return false;
	// top border
	else if ( position.z + halfsize >= size )	return false;

// check for touch walls

	for ( unsigned int j=0; j < walls.size(); j++ )
	{
		Wall *w = walls[j];

		if ( !w->disabled )
		{
			float avgSize = (osize + w->size) / 2.0f;
			if ( fabs( position.x - w->position.x ) <= avgSize &&  fabs( position.z - w->position.z ) <= avgSize )
			{
				return false;
			}
		}
	}

// check for touch other creatures

	for ( unsigned int j=0; j < critters.size(); j++ )
	{
		CritterB *cj = critters[j];
		float avgSize = (osize + cj->size) / 2.0f;
		if ( fabs( position.x - cj->position.x ) <= avgSize &&  fabs( position.z - cj->position.z ) <= avgSize )
		{
			return false;
		}
	}

	return true;
}

bool WorldB::isTouchingAnything(float size, float x, float z)
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

Vector3f WorldB::findEmptySpace(float objectsize)
{
	Vector3f pos;
	pos.x = (float)randgen.get( 0, 100*size ) / 100;
	pos.z = (float)randgen.get( 0, 100*size ) / 100;

	while ( !spotIsFree(pos, objectsize) )
	{
		pos.x = (float)randgen.get( 0, 100*size ) / 100;
		pos.z = (float)randgen.get( 0, 100*size ) / 100;
	}
	return pos;
}


WorldB::~WorldB()
{
	for ( unsigned int i=0; i < food.size(); i++ )		delete food[i];
	for ( unsigned int i=0; i < bullets.size(); i++ )	delete bullets[i];
	for ( unsigned int i=0; i < critters.size(); i++ )	delete critters[i];
}
