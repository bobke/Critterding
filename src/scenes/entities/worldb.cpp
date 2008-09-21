#include "worldb.h"

WorldB::WorldB()
{
	critter_flipnewborns = false;

	brain_mutate_minsynapsesatbuildtime = false;
	brain_mutate_maxsynapsesatbuildtime = false;
	brain_mutate_percentchanceinhibitoryneuron = false;
	brain_mutate_percentchanceconsistentsynapses = false;

	brain_mutate_percentchanceinhibitorysynapses = false;
	brain_mutate_percentchancemotorneuron = false;
	brain_mutate_percentchanceplasticneuron = false;
	brain_mutate_plasticityfactors = false;

	brain_mutate_percentchancesensorysynapse = false;
	brain_mutate_minfiringthreshold = false;
	brain_mutate_maxfiringthreshold = false;
	brain_mutate_maxdendridicbranches = false;
	brain_mutate_mutateeffects = false;

	selectedCritter		= 0;
	isSelected		= false;

	doTimedInserts		= false;
	timedInsertsCounter	= 0;

	// home & program directory
	createDirs();

	// vision retina allocation
	items = 4 * 800 * 600;
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
	freeEnergy		= food_maxenergy * amount;
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
		if ( !food[i]->isCarried )
		{
			// food was eaten
			if ( food[i]->energy <= 0 )
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
	}

	// Remove corpses
	for( unsigned int i=0; i < corpses.size(); i++)
	{
		// corpse was eaten
		if ( corpses[i]->energy <= 0 )
		{
			freeEnergy += corpses[i]->energy;
			delete corpses[i];
			corpses.erase(corpses.begin()+i);
			i--;
		}

		// old corpse
		else if ( ++corpses[i]->totalFrames >= corpses[i]->maxtotalFrames )
		{
			freeEnergy += corpses[i]->energy;
			delete corpses[i];
			corpses.erase(corpses.begin()+i);
			i--;
		}
	}

	// Insert Food
	while ( freeEnergy >= food_maxenergy )
	{
		insertRandomFood(1, food_maxenergy);
		freeEnergy -= food_maxenergy;
		//cerr << "food: " << food.size() << endl;
	}

	// insert critter if < minimum
	if ( critters.size() < mincritters ) insertCritter();

	// remove all dead critters
	for( unsigned int i=0; i < critters.size(); i++)
	{
		// see if energy level isn't below 0 -> die, or die of old age
		if ( critters[i]->energyLevel <= 0.0f )
		{
			cerr << setw(3) << i+1 << "/" << setw(3) << critters.size() << " DIES: starvation" << endl;
			removeCritter(i);
			i--;
		}
		// see if died from bullet
		else if ( critters[i]->totalFrames > critters[i]->maxtotalFrames && critters[i]->wasShot )
		{
			cerr << setw(3) << i+1 << "/" << setw(3) << critters.size() << " DIES: killed" << endl;
			removeCritter(i);
			i--;
		}
		// die of old age
		else if ( critters[i]->totalFrames > critters[i]->maxtotalFrames )
		{
			cerr << setw(3) << i+1 << "/" << setw(3) << critters.size() << " DIES: old age" << endl;
			removeCritter(i);
			i--;
		}
	}

	// as approximation we take every c's halfsize*2: critter_size
	float realSightRange = critter_sightrange + critter_size;

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
		
			for( unsigned int j=0; j < corpses.size(); j++)
			{
				Corpse *co = corpses[j];
				if ( fabs( c->position.x - co->position.x ) <= realSightRange && fabs( c->position.z - co->position.z ) <= realSightRange )
				{
					co->draw();
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
		unsigned int picwidth = (retinasperrow * (critter_retinasize+1));

		// determine height
		unsigned int picheight = critter_retinasize;
		unsigned int rows = critters.size();
		while ( rows > retinasperrow )
		{
			picheight += critter_retinasize;
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
				if ( !fo->isCarried )
				{
					float avgSize = (c->size + fo->size) / 2;
					if ( fabs(c->position.x - fo->position.x) <= avgSize && fabs(c->position.z - fo->position.z) <= avgSize )
					{
						c->touchingFood = true;
						c->touchedFoodID = f;
					}
				}
			}

		// over corpse input neuron
			c->touchingCorpse = false;
			for( unsigned int f=0; f < corpses.size() && !c->touchingCorpse; f++)
			{
				Corpse *co = corpses[f];
				float avgSize = (c->size + co->size) / 2;
				if ( fabs(c->position.x - co->position.x) <= avgSize && fabs(c->position.z - co->position.z) <= avgSize )
				{
					c->touchingCorpse = true;
					c->touchedCorpseID = f;
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
				if ( c->energyLevel + eaten > critter_maxenergy ) eaten -= (c->energyLevel + eaten) - critter_maxenergy;
				if ( food[c->touchedFoodID]->energy - eaten < 0 ) eaten = food[c->touchedFoodID]->energy;
	
				c->energyLevel		+= eaten;
	
				food[c->touchedFoodID]->energy		-= eaten;
				food[c->touchedFoodID]->resize();
			}

		// eat corpse
			if ( c->touchingCorpse && c->eatCorpse )
			{
				float eaten = c->maxEnergyLevel / 50.0f;
				if ( c->energyLevel + eaten > c->maxEnergyLevel ) eaten -= (c->energyLevel + eaten) - c->maxEnergyLevel;
	
				c->energyLevel		+= eaten;
	
				Corpse *co = corpses[c->touchedCorpseID];
				co->energy		-= eaten;
				co->resize();
			}

		// carry / drop
			if ( c->touchingFood && c->carrydrop )
			{
				if ( !c->carriesFood )
				{
					c->foodBeingCarried = food[c->touchedFoodID];
					c->carriesFood = true;

					// calculate a new speedfactor depending on food energy
					float halfcrspeed = (critter_speed / 2.0f);
					c->speedfactor = halfcrspeed + (halfcrspeed - ((c->foodBeingCarried->energy/food_maxenergy)*halfcrspeed) );

					c->foodBeingCarried->isCarried = true;
					c->foodBeingCarried->position.x = c->position.x;
					c->foodBeingCarried->position.y += c->size;
					c->foodBeingCarried->position.z = c->position.z;
					//cerr << "LIFTING" << endl;
				}
				else // we must do an exchange here
				{
				}
			}

			else if ( c->carrydrop && c->carriesFood ) // ! else
			{
				c->carriesFood = false;
				c->speedfactor = critter_speed;
				c->foodBeingCarried->isCarried = false;
				c->foodBeingCarried->position.y -= c->size;
				//cerr << "DROPPING" << endl;
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
					c->totalFrames += (c->maxtotalFrames/2) ;
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
					if ( randgen.get(1,100) <= critter_mutationrate )
					{
						mutant = true;
						nc->mutate(critter_maxmutations);
					}

					// same positions / rotation
					nc->position = c->position;
					nc->rotation = c->rotation;

					nc->speedfactor = critter_speed;
					nc->maxEnergyLevel = critter_maxenergy;
					nc->maxtotalFrames = critter_maxlifetime;
					nc->resize(critter_size);
					nc->procreateTimeTrigger = critter_maxlifetime / critter_maxchildren;
					nc->fireTimeTrigger = critter_maxlifetime / critter_maxbullets;
					nc->minprocenergyLevel = critter_minenergyproc;
					nc->minfireenergyLevel = critter_minenergyfire;

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
						cerr << setw(3) << i+1 << "/" << setw(3) << critters.size() << " PROC: (ad: " << setw(4) << c->adamdist << ")";

						cerr << " N: " << setw(4) << nc->brain.totalNeurons << " C: " << setw(5) << nc->brain.totalSynapses;
						if ( mutant ) cerr << " (m)";

						// optional rotate 180 of new borne
						if ( critter_flipnewborns ) nc->rotation = nc->rotation + 180.0f;

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

		if ( timedInsertsCounter == 3*critter_maxlifetime )
		{
			cerr << "inserting 100 food" << endl;

			freeEnergyInfo += food_maxenergy * 100.0f;
			freeEnergy += food_maxenergy * 100.0f;
		}
		else if ( timedInsertsCounter == (3*critter_maxlifetime)+1 )
		{
			cerr << "removing 100 food" << endl;

			freeEnergyInfo -= food_maxenergy * 100.0f;
			freeEnergy -= food_maxenergy * 100.0f;

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
		f->maxenergy = food_maxenergy;
		f->energy = energy;
		f->maxtotalFrames = food_maxlifetime;
		f->maxsize = food_size;
		f->position = findEmptySpace(f->size);

		f->resize();
		food.push_back( f );
	}
}

void WorldB::insertCritter()
{
	CritterB *c = new CritterB;

	critters.push_back( c );

	c->brain.maxNeurons					= brain_maxneurons;
	c->brain.minSynapses					= brain_minsynapses;
	c->brain.maxSynapses					= brain_maxsynapses;

	c->brain.minNeuronsAtBuildtime				= brain_minneuronsatbuildtime;
	c->brain.maxNeuronsAtBuildtime				= brain_maxneuronsatbuildtime;

	c->brain.minSynapsesAtBuildtime				= brain_minsynapsesatbuildtime;
		c->brain.mutate_minSynapsesAtBuildtime		= brain_mutate_minsynapsesatbuildtime;

	c->brain.maxSynapsesAtBuildtime				= brain_maxsynapsesatbuildtime;
		c->brain.mutate_maxSynapsesAtBuildtime		= brain_mutate_maxsynapsesatbuildtime;

	c->brain.percentChanceInhibitoryNeuron			= brain_percentchanceinhibitoryneuron;
		c->brain.mutate_percentChanceInhibitoryNeuron	= brain_mutate_percentchanceinhibitoryneuron;

	c->brain.percentChanceConsistentSynapses		= brain_percentchanceconsistentsynapses;
		c->brain.mutate_percentChanceConsistentSynapses	= brain_mutate_percentchanceconsistentsynapses;

	c->brain.percentChanceInhibitorySynapses		= brain_percentchanceinhibitorysynapses;
		c->brain.mutate_percentChanceInhibitorySynapses	= brain_mutate_percentchanceinhibitorysynapses;

	c->brain.percentChanceMotorNeuron			= brain_percentchancemotorneuron;
		c->brain.mutate_percentChanceMotorNeuron	= brain_mutate_percentchancemotorneuron;

	c->brain.percentChancePlasticNeuron			= brain_percentchanceplasticneuron;
		c->brain.mutate_percentChancePlasticNeuron	= brain_mutate_percentchanceplasticneuron;

	c->brain.minPlasticityStrengthen			= brain_minplasticitystrengthen;
	c->brain.maxPlasticityStrengthen			= brain_maxplasticitystrengthen;
	c->brain.minPlasticityWeaken				= brain_minplasticityweaken;
	c->brain.maxPlasticityWeaken				= brain_maxplasticityweaken;
		c->brain.mutate_PlasticityFactors		= brain_mutate_plasticityfactors;

	c->brain.percentChanceSensorySynapse			= brain_percentchancesensorysynapse;
		c->brain.mutate_percentChanceSensorySynapse	= brain_mutate_percentchancesensorysynapse;

	c->brain.minFiringThreshold				= brain_minfiringthreshold;
		c->brain.mutate_minFiringThreshold		= brain_mutate_minfiringthreshold;

	c->brain.maxFiringThreshold				= brain_maxfiringthreshold;
		c->brain.mutate_maxFiringThreshold		= brain_mutate_maxfiringthreshold;

	c->brain.maxDendridicBranches				= brain_maxdendridicbranches;
		c->brain.mutate_maxDendridicBranches		= brain_mutate_maxdendridicbranches;

	c->brain.percentMutateEffectAddNeuron			= brain_percentmutateeffectaddneuron;
	c->brain.percentMutateEffectRemoveNeuron		= brain_percentmutateeffectremoveneuron;
	c->brain.percentMutateEffectAlterNeuron			= brain_percentmutateeffectalterneuron;
	c->brain.percentMutateEffectAddSynapse			= brain_percentmutateeffectaddsynapse;
	c->brain.percentMutateEffectRemoveSynapse		= brain_percentmutateeffectremovesynapse;
		c->brain.mutate_MutateEffects			= brain_mutate_mutateeffects;


	c->colorNeurons = critter_colorneurons;
	c->retinasize = critter_retinasize;
	c->calcInputOutputNeurons();

	c->brain.buildArch();
	c->speedfactor = critter_speed;
	c->maxEnergyLevel = critter_maxenergy;
	c->maxtotalFrames = critter_maxlifetime;
	c->rotation = randgen.get( 0, 360 );
	c->resize(critter_size);

	c->energyLevel		= critter_startenergy;
	c->procreateTimeTrigger = critter_maxlifetime / critter_maxchildren;
	c->fireTimeTrigger = critter_maxlifetime / critter_maxbullets;
	c->minprocenergyLevel	= critter_minenergyproc;
	c->minfireenergyLevel	= critter_minenergyfire;

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
	bool hasCorpse = false;
	if ( critters[cid]->energyLevel > 0.0f )
	{
		hasCorpse = true;

		Corpse *c = new Corpse;
		c->maxenergy = food_maxenergy;
		c->maxsize = food_size;
		c->maxtotalFrames = food_maxlifetime;
		c->position = critters[cid]->position;

		// put max energy allowed in food
		if ( critters[cid]->energyLevel > food_maxenergy )
		{
			c->energy = food_maxenergy;
		}
		else
		{
			c->energy = critters[cid]->energyLevel;
		}

		// put rest back in space
		freeEnergy += critters[cid]->energyLevel;
		freeEnergy -= c->energy;

		//f->resize(food_size);
		c->resize();
		corpses.push_back( c );
	}
	else freeEnergy += critters[cid]->energyLevel;

// 	if ( critters[cid]->energyLevel > 0.0f )
// 	{
// 		Food *f = new Food;
// 		f->maxenergy = food_maxenergy;
// 		f->maxsize = food_size;
// 		f->maxtotalFrames = food_maxlifetime;
// 		f->position = critters[cid]->position;
// 
// 		if ( critters[cid]->energyLevel > food_maxenergy )
// 		{
// 			f->energy = food_maxenergy;
// 		}
// 		else
// 		{
// 			f->energy = critters[cid]->energyLevel;
// 		}
// 
// 
// 		freeEnergy += critters[cid]->energyLevel;
// 		freeEnergy -= f->energy;
// 
// 		// put 50% of energy in food, rest back in space
// 
// 		//f->resize(food_size);
// 		f->resize();
// 		food.push_back( f );
// 	}
// 	else freeEnergy += critters[cid]->energyLevel;

	// adapt selection
	if ( isSelected )
	{
		if ( selectedCritter == cid )
		{
			selectedCritter = critters.size()-1;
		}
		else if ( selectedCritter > cid )
		{
			selectedCritter--;
		}
	}

	if ( critters[cid]->carriesFood )
	{
		critters[cid]->foodBeingCarried->isCarried = false;

		// drop the food back down
		critters[cid]->foodBeingCarried->position.y -= critters[cid]->size;
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
	for( unsigned int i=0; i < corpses.size(); i++) corpses[i]->draw();
	for( unsigned int i=0; i < walls.size(); i++) walls[i]->draw();
	for( unsigned int i=0; i < bullets.size(); i++) bullets[i]->draw();
	for( unsigned int i=0; i < critters.size(); i++) critters[i]->draw();
}

// min critter control
void WorldB::increaseMincritters()
{
	mincritters++;
}

void WorldB::decreaseMincritters()
{
	if ( mincritters > 0 ) mincritters--;
}

void WorldB::setMincritters(unsigned int c)
{
	mincritters = c;
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

			unsigned int error = 0;

			if ( c->retinasize != critter_retinasize ) error = 1;

			if ( !error)
			{
				critters.push_back( c );

				c->speedfactor = critter_speed;
				c->maxEnergyLevel = critter_maxenergy;
				c->maxtotalFrames = critter_maxlifetime;
				c->rotation = randgen.get( 0, 360 );
				c->resize(critter_size);

				c->energyLevel		= critter_startenergy;
				c->procreateTimeTrigger = critter_maxlifetime / critter_maxchildren;
				c->fireTimeTrigger = critter_maxlifetime / critter_maxbullets;
				c->minprocenergyLevel	= critter_minenergyproc;
				c->minfireenergyLevel	= critter_minenergyfire;
				c->setup();
				c->retina = retina;
				// record it's energy
				freeEnergy -= c->energyLevel;
				positionCritterB(critters.size()-1);
			}

			if ( error == 1 )
			{
				cerr << "ERROR: critter retinasize (" << c->retinasize << ") doesn't fit world retinasize (" << critter_retinasize << ")" << endl;
			}
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

//	cerr << progdir << endl;

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
	// touches corpse?
		for( unsigned int i=0; i < corpses.size(); i++)
		{
			float avgSize = (size + corpses[i]->size) / 2;
			if ( fabs(x - corpses[i]->position.x) <= avgSize && fabs(z - corpses[i]->position.z) <= avgSize )
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

void WorldB::printSettings()
{

	cout << endl << "BUTTONS" << endl << endl;
	cout << "Engine / World Operations" << endl;
	cout << "  F1            : print settings and toggle pause program" << endl;
	cout << "  F2            : show fps (10 frames average)" << endl << endl;
	cout << "  F3            : decrease Minimum Critters" << endl;
	cout << "  F4            : increase Minimum Critters" << endl << endl;
	cout << "  F5            : decrease energy in the system by the energy amount of 25 food" << endl;
	cout << "  F6            : increase energy in the system by the energy amount of 25 food" << endl << endl;
	cout << "  F7            : insert new critter (adam)" << endl << endl;
	cout << "  F8            : toggle Timed Food Inserts" << endl;
	cout << "                  inserts 100 food every 3 generations, driving the population up and down." << endl << endl;
	cout << "  F9            : decrease max mutations per mutant" << endl;
	cout << "  F10           : increase max mutations per mutant" << endl << endl;
	cout << "  F11           : decrease mutation rate (%)" << endl;
	cout << "  F12           : increase mutation rate (%)" << endl << endl;
	cout << "  Insert        : toggle hide critter retinas." << endl << endl;
	cout << "  w             : create a horizontal wall" << endl;
	cout << "  x             : destroy the wall" << endl;
	cout << "  c             : toggle gate in wall center" << endl << endl;
	cout << "  f             : toggle follow the youngest critter untill it dies." << endl << endl;
	cout << "  Page Up       : load all critters from \"~/.critterding/load\" directory" << endl;
	cout << "  Page Down     : save all critters into \"~/.critterding/save/(timestamp)\" directory" << endl << endl;
	cout << "  keypad -      : decrease energy in the system by the energy amount of 1 food" << endl;
	cout << "  keypad +      : increase energy in the system by the energy amount of 1 food" << endl << endl;

	cout << "Camera Operations" << endl;
	cout << "  Arrow Up      : move forward" << endl;
	cout << "  Arrow Down    : move backward" << endl;
	cout << "  Arrow Left    : strafe left" << endl;
	cout << "  Arrow Right   : strafe right" << endl;
	cout << "  Home          : move up" << endl;
	cout << "  End           : move down" << endl;
	cout << "  NumKey 2      : look up" << endl;
	cout << "  NumKey 8      : look down" << endl;
	cout << "  NumKey 4      : look left" << endl;
	cout << "  NumKey 6      : look right" << endl;

	// report settings
	cout << endl << "CURRENT SETTINGS" << endl << endl;
	cout << "Global Settings" << endl;
	cout << "  World size                  = " << size << "x" << size << endl;
	cout << "  Energy in system            = " << freeEnergyInfo/food_maxenergy << "*" << food_maxenergy << " = " << freeEnergyInfo << endl;
	cout << "  Minimal amount of critters  = " << mincritters << endl;
	cout << "  Retinas per row             = " << retinasperrow << endl;

	cout << endl << "Critter Settings" << endl;
	cout << "  max Lifetime                = " << critter_maxlifetime << endl;
	cout << "  max Energy                  = " << critter_maxenergy << endl;
	cout << "  Energy at start             = " << critter_startenergy << endl;
	cout << "  max Children                = " << critter_maxchildren << endl;
	cout << "  max Bullets                 = " << critter_maxbullets << endl;
	cout << "  min Energy for procreation  = " << critter_minenergyproc << endl;
	cout << "  max Energy for firing       = " << critter_minenergyfire << endl;

	cout << "  Size                        = " << critter_size*100.0f << endl;
	cout << "  Speed                       = " << critter_speed*1000.0f << endl;
	cout << "  Sight range                 = " << critter_sightrange*10.0f << endl;
	cout << "  Retina size                 = " << critter_retinasize << endl;
	cout << "  Color neurons               = " << critter_colorneurons << endl;
	cout << "  Mutationrate                = " << critter_mutationrate << endl;
	cout << "  max Mutations / mutant      = " << critter_maxmutations << endl;
	cout << "  Flip newborns               = " << critter_flipnewborns << endl;

	cout << endl << "Food Settings" << endl;
	cout << "  max Lifetime                = " << food_maxlifetime << endl;
	cout << "  max Energy                  = " << food_maxenergy << endl;
	cout << "  Size                        = " << food_size*100.0f << endl;

	cout << endl << "Brain Settings" << endl;
	cout << "  max Neurons per critter     = " << brain_maxneurons << endl;
	cout << "  min Synapses per neuron     = " << brain_minsynapses << endl;
	cout << "  max Synapses per neuron     = " << brain_maxsynapses << endl;
	cout << "  min Neurons at build time   = " << brain_minneuronsatbuildtime << endl;
	cout << "  max Neurons at build time   = " << brain_maxneuronsatbuildtime << endl;
	cout << "  min Synapses at build time  = " << brain_minsynapsesatbuildtime << endl;
	cout << "    mutate                    = " << brain_mutate_minsynapsesatbuildtime << endl;
	cout << "  max Synapses at build time  = " << brain_maxsynapsesatbuildtime << endl;
	cout << "    mutate                    = " << brain_mutate_maxsynapsesatbuildtime << endl;
	cout << "  % Inhibitory neuron         = " << brain_percentchanceinhibitoryneuron << endl;
	cout << "    mutate                    = " << brain_mutate_percentchanceinhibitoryneuron << endl;
	cout << "  % Motor neuron              = " << brain_percentchancemotorneuron << endl;
	cout << "    mutate                    = " << brain_mutate_percentchancemotorneuron << endl;
	cout << "  % Plastic neuron            = " << brain_percentchanceplasticneuron << endl;
	cout << "    mutate                    = " << brain_mutate_percentchanceplasticneuron << endl;
	cout << "  min Plasticity strengthen   = " << brain_minplasticitystrengthen << endl;
	cout << "  max Plasticity strengthen   = " << brain_maxplasticitystrengthen << endl;
	cout << "  min Plasticity weaken       = " << brain_minplasticityweaken << endl;
	cout << "  max Plasticity weaken       = " << brain_maxplasticityweaken << endl;
	cout << "    mutate plasticityfactors  = " << brain_mutate_plasticityfactors << endl;
	cout << "  min Firing threshold        = " << brain_minfiringthreshold << endl;
	cout << "    mutate                    = " << brain_mutate_minfiringthreshold << endl;
	cout << "  max Firing threshold        = " << brain_maxfiringthreshold << endl;
	cout << "    mutate                    = " << brain_mutate_maxfiringthreshold << endl;
	cout << "  max Dendridic branches      = " << brain_maxdendridicbranches << endl;
	cout << "    mutate                    = " << brain_mutate_maxdendridicbranches << endl;
	cout << "  % Consistent synapses       = " << brain_percentchanceconsistentsynapses << endl;
	cout << "    mutate                    = " << brain_mutate_percentchanceconsistentsynapses << endl;
	cout << "  % Inhibitory synapses       = " << brain_percentchanceinhibitorysynapses << endl;
	cout << "    mutate                    = " << brain_mutate_percentchanceinhibitorysynapses << endl;
	cout << "  % Sensory Synapse           = " << brain_percentchancesensorysynapse << endl;
	cout << "    mutate                    = " << brain_mutate_percentchancesensorysynapse << endl;
	cout << "  % Effect: add neuron        = " << brain_percentmutateeffectaddneuron << endl;
	cout << "  % Effect: remove neuron     = " << brain_percentmutateeffectremoveneuron << endl;
	cout << "  % Effect: alter neuron      = " << brain_percentmutateeffectalterneuron << endl;
	cout << "  % Effect: add synapse       = " << brain_percentmutateeffectaddsynapse << endl;
	cout << "  % Effect: remove synapse    = " << brain_percentmutateeffectremovesynapse << endl;
	cout << "    mutate effects            = " << brain_mutate_mutateeffects << endl;

	cout << endl;
}

WorldB::~WorldB()
{
	for ( unsigned int i=0; i < food.size(); i++ )		delete food[i];
	for ( unsigned int i=0; i < bullets.size(); i++ )	delete bullets[i];
	for ( unsigned int i=0; i < critters.size(); i++ )	delete critters[i];
	free(retina);
}

