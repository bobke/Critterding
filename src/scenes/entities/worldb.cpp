#include "worldb.h"

WorldB::WorldB()
{
//	Infobar *infobar	= Infobar::instance();

	selectedCritter		= 0;
	isSelected		= false;

	doTimedInserts		= false;
	timedInsertsCounter	= 0;

	crittersize		= 0.0f;
	foodsize		= 0.0f;

	foodenergy		= 0.0f;

	retinasperrow		= 0;

	mincritters		= 10;

	mutationRate		= 10; // %
	maxMutateRuns		= 1;

	flipnewbornes		= false;

	critterspeed		= 0.0f;
	critterenergy		= 0.0f;

	critterlifetime		= 0;
	foodlifetime		= 0;

	critterSightRange	= 0.0f;

	// home & program directory
	createDirs();

	// vision retina allocation
	items = 10000 * 4 * (10+1) * 10;
	retina = (unsigned char*)malloc(items);
	memset(retina, 0, items);

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

	// as approximation we take every c's halfsize*2: crittersize
	float realSightRange = critterSightRange + crittersize;

	// for all critters do
	for( unsigned int i=0; i < critters.size(); i++)
	{
		CritterB *c = critters[i];

		c->place();

		// draw everything in it's sight
			floor.draw();
		
			for( unsigned int j=0; j < critters.size(); j++)
			{
				CritterB *oc = critters[j];
				if ( fabs( c->position.x - oc->position.x ) <= realSightRange && fabs( c->position.z - oc->position.z ) <= realSightRange )
				{
					oc->draw();
				}
			}
		
			for( unsigned int j=0; j < food.size(); j++)
			{
				Food *f = food[j];
				if ( fabs( c->position.x - f->position.x ) <= realSightRange && fabs( c->position.z - f->position.z ) <= realSightRange )
				{
					f->draw();
				}
			}
		
			for( unsigned int j=0; j < walls.size(); j++)
			{
				Wall *w = walls[j];
				if ( fabs( c->position.x - w->position.x ) <= realSightRange && fabs( c->position.z - w->position.z ) <= realSightRange )
				{
					w->draw();
				}
			}
		
			for( unsigned int j=0; j < bullets.size(); j++)
			{
				Bullet *b = bullets[j];
				if ( fabs( c->position.x - b->position.x ) <= realSightRange && fabs( c->position.z - b->position.z ) <= realSightRange )
				{
					b->draw();
				}
			}
	}

	// Read pixels into retina
	if ( critters.size() > 0 )
	{
		// determine width
		unsigned int picwidth = (retinasperrow * (10+1));

		// determine height
		unsigned int picheight = 10;
		unsigned int rows = critters.size();
		while ( rows > retinasperrow )
		{
			picheight += 10;
			rows -= retinasperrow;
		}
		glReadPixels(0, 0, picwidth, picheight, GL_RGBA, GL_UNSIGNED_BYTE, retina);
	}

	// process all critters
	unsigned int lmax = critters.size();
	for( unsigned int i=0; i < lmax; i++)
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
			if (c->moved)
			{
				if (spotIsFree(c->newposition, c->size, i))
				{
					c->moveToNewPoss();
				}
			}

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

					nc->speedfactor = critterspeed;
					nc->maxEnergyLevel = critterenergy;
					nc->maxtotalFrames = critterlifetime;
					nc->resize(crittersize);
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
	
						nc->calcFramePos(critters.size(), retinasperrow);

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

		if ( timedInsertsCounter == 3*critterlifetime )
		{
			cerr << "inserting 100 food" << endl;

			freeEnergyInfo += foodenergy * 100.0f;
			freeEnergy += foodenergy * 100.0f;
		}
		else if ( timedInsertsCounter == (3*critterlifetime)+1 )
		{
			cerr << "removing 100 food" << endl;

			freeEnergyInfo -= foodenergy * 100.0f;
			freeEnergy -= foodenergy * 100.0f;

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
		f->maxenergy = foodenergy;
		f->energy = energy;
		f->maxtotalFrames = foodlifetime;
		f->maxsize = foodsize;
		f->position = findEmptySpace(f->size);

		f->resize();
		food.push_back( f );
	}
}

void WorldB::insertCritter()
{
	CritterB *c = new CritterB;

	critters.push_back( c );

	c->brain.buildArch();
	c->speedfactor = critterspeed;
	c->maxEnergyLevel = critterenergy;
	c->maxtotalFrames = critterlifetime;
	c->rotation = randgen.get( 0, 360 );
	c->resize(crittersize);
	c->setup();
	c->retina = retina;

	// record it's energy
	freeEnergy -= c->energyLevel;

	positionCritterB(critters.size()-1);
}

void WorldB::positionCritterB(unsigned int cid)
{
	critters[cid]->position	= findEmptySpace(critters[cid]->size);
	critters[cid]->position.y = critters[cid]->halfsize;
	critters[cid]->calcFramePos(cid, retinasperrow);
	critters[cid]->calcCamPos();
}

void WorldB::removeCritter(unsigned int cid)
{
	if ( critters[cid]->energyLevel > 0.0f )
	{
		Food *f = new Food;
		f->maxenergy = foodenergy;
		f->maxsize = foodsize;
		f->maxtotalFrames = foodlifetime;
		f->position = critters[cid]->position;

		if ( critters[cid]->energyLevel > foodenergy )
		{
			f->energy = foodenergy;
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
		critters[c]->calcFramePos(c, retinasperrow);
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
		if ( parseH.endMatches( ".cr", files[i] ) )
		{
			cout << "loading " << files[i] << endl;
			string content;
			fileH.open( files[i], content );

			CritterB *c = new CritterB(content);

			critters.push_back( c );

			c->speedfactor = critterspeed;
			c->maxEnergyLevel = critterenergy;
			c->maxtotalFrames = critterlifetime;
			c->rotation = randgen.get( 0, 360 );
			c->resize(crittersize);
			c->setup();
			c->retina = retina;
			// record it's energy
			freeEnergy -= c->energyLevel;
			positionCritterB(critters.size()-1);
		}
	}
	cerr << endl << "Loaded critters from " << loaddir << endl << endl;
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
	cerr << endl << "Saved critters to " << subsavedir << endl << endl;
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
	free(retina);
}

