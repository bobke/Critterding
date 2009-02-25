#include "worldb.h"

WorldB::WorldB()
{
	settings = Settings::Instance();

	currentCritterID	= 0;

	selectedCritter		= 0;
	isSelected		= false;

	doTimedInserts		= false;
	timedInsertsCounter	= 0;

	autosaveCounter		= 0.0f;

	// home & program directory
	createDirs();

	// vision retina allocation
	items = 4 * 800 * 600;
	retina = (unsigned char*)malloc(items);
	memset(retina, 0, items);

	generateList();
}

void WorldB::generateList()
{
	displayLists = glGenLists(4);

	// 1 = food, corpse, bullet : normal cube
	glNewList(displayLists,GL_COMPILE);

		glBegin(GL_QUADS);
		//Quad 1
		glVertex3f( 1.0f, 1.0f, 1.0f);   //V2
		glVertex3f( 1.0f,-1.0f, 1.0f);   //V1
		glVertex3f( 1.0f,-1.0f,-1.0f);   //V3
		glVertex3f( 1.0f, 1.0f,-1.0f);   //V4
		//Quad 2
		glVertex3f( 1.0f, 1.0f,-1.0f);   //V4
		glVertex3f( 1.0f,-1.0f,-1.0f);   //V3
		glVertex3f(-1.0f,-1.0f,-1.0f);   //V5
		glVertex3f(-1.0f, 1.0f,-1.0f);   //V6
		//Quad 3
		glVertex3f(-1.0f, 1.0f,-1.0f);   //V6
		glVertex3f(-1.0f,-1.0f,-1.0f);   //V5
		glVertex3f(-1.0f,-1.0f, 1.0f);   //V7
		glVertex3f(-1.0f, 1.0f, 1.0f);   //V8
		//Quad 4
		glVertex3f(-1.0f, 1.0f, 1.0f);   //V8
		glVertex3f(-1.0f,-1.0f, 1.0f);   //V7
		glVertex3f( 1.0f,-1.0f, 1.0f);   //V1
		glVertex3f( 1.0f, 1.0f, 1.0f);   //V2
		//Quad 5
		glVertex3f(-1.0f, 1.0f,-1.0f);   //V6
		glVertex3f(-1.0f, 1.0f, 1.0f);   //V8
		glVertex3f( 1.0f, 1.0f, 1.0f);   //V2
		glVertex3f( 1.0f, 1.0f,-1.0f);   //V4
		glEnd();

	glEndList();

	// 2 = critter
	glNewList(displayLists+1,GL_COMPILE);
		glBegin(GL_QUADS);
		//Quad 1
		glVertex3f( 1.0f, 1.0f, 1.0f);   //V2
		glVertex3f( 1.0f,-1.0f, 1.0f);   //V1
		glVertex3f( 1.0f,-1.0f,-1.0f);   //V3
		glVertex3f( 1.0f, 1.0f,-1.0f);   //V4
		//Quad 2
		glVertex3f( 1.0f, 1.0f,-1.0f);   //V4
		glVertex3f( 1.0f,-1.0f,-1.0f);   //V3
		glVertex3f(-1.0f,-1.0f,-1.0f);   //V5
		glVertex3f(-1.0f, 1.0f,-1.0f);   //V6
		//Quad 3
		glVertex3f(-1.0f, 1.0f,-1.0f);   //V6
		glVertex3f(-1.0f,-1.0f,-1.0f);   //V5
		glVertex3f(-1.0f,-1.0f, 1.0f);   //V7
		glVertex3f(-1.0f, 1.0f, 1.0f);   //V8
		//Quad 4
		glVertex3f(-1.0f, 1.0f, 1.0f);   //V8
		glVertex3f(-1.0f,-1.0f, 1.0f);   //V7
		glVertex3f( 1.0f,-1.0f, 1.0f);   //V1
		glVertex3f( 1.0f, 1.0f, 1.0f);   //V2
		//Quad 5
		glVertex3f(-1.0f, 1.0f,-1.0f);   //V6
		glVertex3f(-1.0f, 1.0f, 1.0f);   //V8
		glVertex3f( 1.0f, 1.0f, 1.0f);   //V2
		glVertex3f( 1.0f, 1.0f,-1.0f);   //V4
		glEnd();

	glEndList();

	// 3 = critter nose
	glNewList(displayLists+2,GL_COMPILE);

// 		glColor4f( 1.0f, 1.0f, 1.0f, 0.0f );

		glBegin(GL_TRIANGLES);
		// standard nose
// 		glVertex3f( -1.0f,  1.0f,  -1.0f );
// 		glVertex3f(  1.0f,  1.0f,  -1.0f );
// 		glVertex3f(  0.0f,  0.5f,  -1.3f );

		// owl nose
// 		glVertex3f( -1.0f,  0.3f,  -1.0f );
// 		glVertex3f(  1.0f,  0.3f,  -1.0f );
// 		glVertex3f(  0.0f,  0.3f,  -1.3f );
// 
// 		glVertex3f( -1.0f,  0.3f,  -1.0f );
// 		glVertex3f(  0.0f,  1.0f,  -1.0f );
// 		glVertex3f(  0.0f,  0.3f,  -1.3f );
// 
// 		glVertex3f(  0.0f,  1.0f,  -1.0f );
// 		glVertex3f(  1.0f,  0.3f,  -1.0f );
// 		glVertex3f(  0.0f,  0.3f,  -1.3f );

		// big nose
		glVertex3f(  0.0f,  1.0f,  -1.0f );
		glVertex3f(  1.0f,  0.0f,  -1.0f );
		glVertex3f(  0.0f,  0.0f,  -1.5f );

		glVertex3f(  0.0f,  1.0f,  -1.0f );
		glVertex3f(  0.0f,  0.0f,  -1.5f );
		glVertex3f( -1.0f,  0.0f,  -1.0f );

		glEnd();

	glEndList();

	// 4 = floor
	glNewList(displayLists+3,GL_COMPILE);

		glColor4f( 0.0f, 0.0f, 1.0f, 0.0f );
		glBegin(GL_QUADS);
		glVertex3f( 0.0f, 0.0f, 0.0f);
		glVertex3f( 0.0f, 0.0f, 1.0f);
		glVertex3f( 1.0f, 0.0f, 1.0f);
		glVertex3f( 1.0f, 0.0f, 0.0f);
		glEnd();

	glEndList();

}

void WorldB::resize(unsigned int X, unsigned int Y)
{
//	size = X;
	sizeX = X;
	sizeY = Y;
	grid.resize(X, Y);
	floor.resize(X, Y);
}

void WorldB::startfoodamount(unsigned int amount)
{
	freeEnergy = settings->food_maxenergy * amount;
		settings->freeEnergyInfo = freeEnergy;
}

void WorldB::process()
{
	// Autosave Critters?
	if ( settings->critter_autosaveinterval > 0 )
	{
		autosaveCounter += Timer::Instance()->elapsed;
		if ( autosaveCounter > settings->critter_autosaveinterval )
		{
			autosaveCounter = 0.0f;
			saveAllCritters();
		}
	}

	// Bullet movement
	for( unsigned int i=0; i < bullets.size(); i++)
	{
		Bullet *b = bullets[i];

		// forward it fires
		b->moveForward();

		// die of age
		if ( b->totalSteps > 7 )
		{
			delete b;
			bullets.erase(bullets.begin()+i);
			i--;
		}
		else
		{
		// bullet hit wall
			bool hit = false;
			for( unsigned int j=0; j < walls.size() && !hit; j++)
			{
				Wall *w = walls[j];
				float avgSize = w->halfsize + b->halfsize;
				if ( fabs(w->position.x - b->position.x) <= avgSize && fabs(w->position.z - b->position.z) <= avgSize )
				{
					delete b;
					bullets.erase(bullets.begin()+i);
					i--;
					hit = true;
				}
			}
		}

	}

	// Insert Food
	while ( freeEnergy >= settings->food_maxenergy )
	{
		insertRandomFood(1, settings->food_maxenergy);
		freeEnergy -= settings->food_maxenergy;
		//cerr << "food: " << food.size() << endl;
	}

	// insert critter if < minimum
	if ( critters.size() < settings->mincritters ) insertCritter();

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
			else if ( ++food[i]->totalFrames >= settings->food_maxlifetime )
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
		if ( !corpses[i]->isCarried )
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
			else if ( ++corpses[i]->totalFrames >= settings->corpse_maxlifetime )
			{
				freeEnergy += corpses[i]->energy;
				delete corpses[i];
				corpses.erase(corpses.begin()+i);
				i--;
			}
		}
	}

	// remove all dead critters
	for( unsigned int i=0; i < critters.size(); i++)
	{
		// see if energy level isn't below 0 -> die, or die of old age
		if ( critters[i]->energyLevel <= 0.0f )
		{
//			if (!settings->noverbose) cerr << "< " << setw(3) << critters.size()-1 << " | " << setw(4) << critters[i]->critterID << " starved" << endl;
/*			if (!settings->noverbose)
			{*/
				stringstream buf;
				buf << setw(4) << critters[i]->critterID << " starved";
				Textverbosemessage::Instance()->addDeath(buf);
// 			}

			removeCritter(i);
			i--;
		}
		// see if died from bullet
		else if ( critters[i]->totalFrames > settings->critter_maxlifetime && critters[i]->wasShot )
		{
			//if (!settings->noverbose) cerr << "< " << setw(3) << critters.size()-1 << " | " << setw(4) << critters[i]->critterID << " killed" << endl;
/*			if (!settings->noverbose)
			{*/
				stringstream buf;
				buf << setw(4) << critters[i]->critterID << " killed";
				Textverbosemessage::Instance()->addDeath(buf);
// 			}
			removeCritter(i);
			i--;
		}
		// die of old age
		else if ( critters[i]->totalFrames > settings->critter_maxlifetime )
		{
//			if (!settings->noverbose) cerr << "< " << setw(3) << critters.size()-1 << " | " << setw(4) << critters[i]->critterID << " old" << endl;
/*			if (!settings->noverbose)
			{*/
				stringstream buf;
				buf << setw(4) << critters[i]->critterID << " old";
				Textverbosemessage::Instance()->addDeath(buf);
// 			}
			removeCritter(i);
			i--;
		}
	}

	// as approximation we take every c's halfsize*2: critter_size
	//float realSightRange = critter_sightrange + critter_size;

	// for all critters do
	for( unsigned int i=0; i < critters.size(); i++)
	{
		critters[i]->place();
		drawWithinCritterSight(i);
	}

	// Read pixels into retina
	if ( critters.size() > 0 )
	{
		// determine width
		unsigned int picwidth = (settings->retinasperrow * (settings->critter_retinasize+1));

		// determine height
		unsigned int picheight = settings->critter_retinasize;
		unsigned int rows = critters.size();
		while ( rows > settings->retinasperrow )
		{
			picheight += settings->critter_retinasize;
			rows -= settings->retinasperrow;
		}
		glReadPixels(0, 0, picwidth, picheight, GL_RGBA, GL_UNSIGNED_BYTE, retina);
	}

	settings->info_crittersH = 0;
	settings->info_totalNeuronsH = 0;
	settings->info_totalSynapsesH = 0;
	settings->info_totalAdamDistanceH = 0;
	settings->info_crittersC = 0;
	settings->info_totalNeuronsC = 0;
	settings->info_totalSynapsesC = 0;
	settings->info_totalAdamDistanceC = 0;

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
					float avgSize = c->halfsize + fo->halfsize;
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
				Corpse *fo = corpses[f];
				if ( !fo->isCarried )
				{
					float avgSize = c->halfsize + fo->halfsize;
					if ( fabs(c->position.x - fo->position.x) <= avgSize && fabs(c->position.z - fo->position.z) <= avgSize )
					{
						c->touchingCorpse = true;
						c->touchedCorpseID = f;
					}
				}
			}
	
		// process
			c->process();

		// record critter used energy
			freeEnergy += c->energyUsed;
	
		// move
			if (c->moved)
			{
				if (spotIsFree(c->newposition, c->halfsize, i))
				{
					c->moveToNewPoss();
				}
			}

		// eat
			if ( c->eat )
			{
				// herbivore
				if ( c->crittertype == 0 )
				{
					// is food
					if ( c->touchingFood )
					{
						float eaten = settings->critter_maxenergy / 50.0f;
						if ( c->energyLevel + eaten > settings->critter_maxenergy ) eaten -= (c->energyLevel + eaten) - settings->critter_maxenergy;
						if ( food[c->touchedFoodID]->energy - eaten < 0 ) eaten = food[c->touchedFoodID]->energy;
			
						c->energyLevel += eaten;
						food[c->touchedFoodID]->energy -= eaten;
						food[c->touchedFoodID]->resize();
					}
					// is poison
					if ( c->touchingCorpse )
					{
						float eaten = settings->critter_maxenergy / 50.0f;
						if ( c->energyLevel - eaten < 0.0f ) eaten = c->energyLevel;
						if ( corpses[c->touchedCorpseID]->energy - eaten < 0.0f ) eaten = corpses[c->touchedCorpseID]->energy;
			
						c->energyLevel -= eaten;
						corpses[c->touchedCorpseID]->energy -= eaten;
						corpses[c->touchedCorpseID]->resize();

						// free the energy
						freeEnergy += 2.0f*eaten;
					}
				}

				// carnivore
				else
				{
					// is food
					if ( c->touchingCorpse )
					{
						float eaten = settings->critter_maxenergy / 50.0f;
						if ( c->energyLevel + eaten > settings->critter_maxenergy ) eaten -= (c->energyLevel + eaten) - settings->critter_maxenergy;
						if ( corpses[c->touchedCorpseID]->energy - eaten < 0.0f ) eaten = corpses[c->touchedCorpseID]->energy;
			
						c->energyLevel += eaten;
						corpses[c->touchedCorpseID]->energy -= eaten;
						corpses[c->touchedCorpseID]->resize();
					}
					// is poison
					if ( c->touchingFood )
					{
						float eaten = settings->critter_maxenergy / 50.0f;
						if ( c->energyLevel - eaten < 0.0f ) eaten = c->energyLevel;
						if ( food[c->touchedFoodID]->energy - eaten < 0.0f ) eaten = food[c->touchedFoodID]->energy;
			
						c->energyLevel -= eaten;
						food[c->touchedFoodID]->energy -= eaten;
						food[c->touchedFoodID]->resize();

						// free the energy
						freeEnergy += 2.0f*eaten;
					}
				}
			}

		// carry / drop
			if ( settings->critter_enablecarrying && c->carrydrop )
			{
				// food
				if ( c->touchingFood )
				{
					if ( !c->carriesCorpse && !c->carriesFood )
					{
						if ( !food[c->touchedFoodID]->isCarried && !c->carriesCorpse )
						{
							c->foodBeingCarried = food[c->touchedFoodID];
							c->carriesFood = true;

							// calculate a new speedfactor depending on food energy
							float halfcrspeed = (settings->critter_speed / 2.0f);
							c->speedfactor = halfcrspeed + (halfcrspeed - ((c->foodBeingCarried->energy/settings->food_maxenergy)*halfcrspeed) );

							c->foodBeingCarried->isCarried = true;
							c->foodBeingCarried->position.x = c->position.x;
							c->foodBeingCarried->position.y += c->size;
							c->foodBeingCarried->position.z = c->position.z;
							//cerr << "LIFTING" << endl;
						}
					}
/*					else // we must do an exchange here
					{
					}*/
				}
				else if ( c->carriesFood ) // ! else
				{
					c->carriesFood = false;
					c->speedfactor = settings->critter_speed;
					c->foodBeingCarried->isCarried = false;
					c->foodBeingCarried->position.y -= c->size;
					//cerr << "DROPPING" << endl;
				}

				// corpse
				if ( c->touchingCorpse )
				{
					if ( !c->carriesCorpse && !c->carriesFood )
					{
						if ( !corpses[c->touchedCorpseID]->isCarried )
						{
							c->corpseBeingCarried = corpses[c->touchedCorpseID];
							c->carriesCorpse = true;

							// calculate a new speedfactor depending on corpse energy
							float halfcrspeed = (settings->critter_speed / 2.0f);
							c->speedfactor = halfcrspeed + (halfcrspeed - ((c->corpseBeingCarried->energy/settings->corpse_maxenergy)*halfcrspeed) );

							c->corpseBeingCarried->isCarried = true;
							c->corpseBeingCarried->position.x = c->position.x;
							c->corpseBeingCarried->position.y += c->size;
							c->corpseBeingCarried->position.z = c->position.z;
							//cerr << "LIFTING" << endl;
						}
					}
/*					else // we must do an exchange here FIXME
					{
					}*/
				}
				else if ( c->carriesCorpse ) // ! else
				{
					c->carriesCorpse = false;
					c->speedfactor = settings->critter_speed;
					c->corpseBeingCarried->isCarried = false;
					c->corpseBeingCarried->position.y -= c->size;
					//cerr << "DROPPING" << endl;
				}
			}

		// fire
			if ( c->fire && c->canFire )
			{
				//cerr << "critter " << i << "(ad:" << c->adamdist << ") FIRES\n";
				c->fireTimeCount = 0;
				//float used = settings->critter_maxenergy * 0.01f;
				c->energyLevel -= settings->critter_firecost;
				freeEnergy += settings->critter_firecost;
	
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
				float avgSize = c->halfsize + b->halfsize;
				if ( fabs(c->position.x - b->position.x) <= avgSize && fabs(c->position.z - b->position.z) <= avgSize )
				{
					c->totalFrames += (settings->critter_maxlifetime/2) ;
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
				c->prepNewPoss();
				c->newposition.x -= c->reuseRotSinY * c->halfsize;
				c->newposition.z -= c->reuseRotCosY * c->halfsize;
	
				if (spotIsFree(c->newposition, c->halfsize, i))
				{
					// move new critter to the right by sum of halfsizes
					Vector3f newpos = c->position;
					newpos.x += c->reuseRotSinY * (2.0f*c->halfsize + 0.01);
					newpos.z += c->reuseRotCosY * (2.0f*c->halfsize + 0.01);

					if (spotIsFree(newpos, c->halfsize, i))
					{

						CritterB *nc = new CritterB(*c);

						// mutate or not
						bool mutant = false;
						if ( randgen->Instance()->get(1,100) <= settings->critter_mutationrate )
						{
							mutant = true;
							nc->mutate();
						}

						// same positions / rotation
						nc->position = newpos;

						// optional rotate 180 of new borne
						if ( settings->critter_flipnewborns )
						{
							nc->setRotation(c->rotation + 180.0f);
						}
						else if ( settings->critter_randomrotatenewborns )
						{
							nc->setRotation( randgen->Instance()->get(0,360) );
						}
						else
						{
							nc->setRotation(c->rotation);
						}

						nc->prepNewPoss();

						nc->brain.wireArch();
						nc->retina = retina;

						nc->critterID = currentCritterID++;

// 						if (!settings->noverbose)
// 						{
// 							cerr << "> " << setw(3) << critters.size()+1 << " | " << setw(4) << c->critterID << " procreates: " << setw(4) << nc->critterID << " (";
// 							cerr << "ad: " << setw(4) << nc->adamdist;
// 							cerr << ", N: " << setw(4) << nc->brain.totalNeurons << ", C: " << setw(5) << nc->brain.totalSynapses;
// 							if ( nc->crittertype == 1 ) cerr << ", carnivore";
// 							else cerr << ", herbivore";
// 							if ( mutant ) cerr << ", mutant";
// 							cerr << ")" << endl;

							stringstream buf;
							buf << setw(4) << c->critterID << " : " << setw(4) << nc->critterID;
							buf << " ad: " << setw(4) << nc->adamdist;
							buf << " n: " << setw(4) << nc->brain.totalNeurons << " s: " << setw(5) << nc->brain.totalSynapses;
							if ( nc->crittertype == 1 )
								buf << " carnivore";
							else
								buf << " herbivore";
							if ( mutant ) buf << " mutant";
							Textverbosemessage::Instance()->addBirth(buf);
// 						}

						// split energies in half
						nc->energyLevel = c->energyLevel/2.0f;
						c->energyLevel = nc->energyLevel;

						// reset procreation energy count
						c->procreateTimeCount = 0;
	
						nc->calcFramePos(critters.size());

						c->moveToNewPoss();
						nc->moveToNewPoss();

						if ( nc->crittertype == 0 )
						{
							settings->info_crittersH++;
							settings->info_totalNeuronsH += nc->brain.totalNeurons;
							settings->info_totalSynapsesH += nc->brain.totalSynapses;
							settings->info_totalAdamDistanceH += nc->adamdist;
						}
						else
						{
							settings->info_crittersC++;
							settings->info_totalNeuronsC += nc->brain.totalNeurons;
							settings->info_totalSynapsesC += nc->brain.totalSynapses;
							settings->info_totalAdamDistanceC += nc->adamdist;
						}

						critters.push_back( nc );
					}
				}
			}

		if ( c->crittertype == 0 )
		{
			settings->info_crittersH++;
			settings->info_totalNeuronsH += c->brain.totalNeurons;
			settings->info_totalSynapsesH += c->brain.totalSynapses;
			settings->info_totalAdamDistanceH += c->adamdist;
		}
		else
		{
			settings->info_crittersC++;
			settings->info_totalNeuronsC += c->brain.totalNeurons;
			settings->info_totalSynapsesC += c->brain.totalSynapses;
			settings->info_totalAdamDistanceC += c->adamdist;
		}
	}

	settings->info_critters = critters.size();
	settings->info_food = food.size();
	settings->info_corpses = corpses.size();
	settings->info_bullets = bullets.size();


/*	cerr << "b: " << *critters[0]->Neurons[0]->inputs[0]->ref << endl;
	usleep (1000000);*/

	if ( doTimedInserts )
	{
		timedInsertsCounter++;

		if ( timedInsertsCounter == 3*settings->critter_maxlifetime )
		{
			if (!settings->noverbose) cerr << "inserting 100 food" << endl;

			settings->freeEnergyInfo += settings->food_maxenergy * 100.0f;
			freeEnergy += settings->food_maxenergy * 100.0f;
		}
		else if ( timedInsertsCounter == (3*settings->critter_maxlifetime)+1 )
		{
			if (!settings->noverbose) cerr << "removing 100 food" << endl;

			settings->freeEnergyInfo -= settings->food_maxenergy * 100.0f;
			freeEnergy -= settings->food_maxenergy * 100.0f;

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
		f->energy = energy;
		f->resize();
		f->position = findEmptySpace(f->halfsize);
		food.push_back( f );
	}
}

void WorldB::insertCritter()
{
	CritterB *c = new CritterB;

	critters.push_back( c );

	c->critterID = currentCritterID++;

	// start energy
	c->energyLevel = settings->critter_startenergy;
	freeEnergy -= c->energyLevel;

	positionCritterB(critters.size()-1);
	c->setRotation( randgen->Instance()->get(0,360) );

	c->brain.wireArch();
	c->retina = retina;
}

void WorldB::positionCritterB(unsigned int cid)
{
	critters[cid]->newposition = findEmptySpace(critters[cid]->halfsize);
	critters[cid]->newposition.y = critters[cid]->halfsize;
	critters[cid]->moveToNewPoss();

	critters[cid]->calcFramePos(cid);
	critters[cid]->calcCamPos();
}

void WorldB::removeCritter(unsigned int cid)
{
	bool hasCorpse = false;
	if ( critters[cid]->energyLevel > 0.0f && !settings->corpse_disable && critters[cid]->crittertype==0 )
	{
		hasCorpse = true;

		Corpse *c = new Corpse;
		c->position = critters[cid]->position;

		// put max energy allowed in corpse
		if ( critters[cid]->energyLevel > settings->corpse_maxenergy )
			c->energy = settings->corpse_maxenergy;
		else
			c->energy = critters[cid]->energyLevel;

		// put rest back in space
		freeEnergy += critters[cid]->energyLevel;
		freeEnergy -= c->energy;

		c->resize();
		corpses.push_back( c );
	}
	else freeEnergy += critters[cid]->energyLevel;

// 	if ( critters[cid]->energyLevel > 0.0f )
// 	{
// 		Food *f = new Food;
// 		f->maxenergy = settings->food_maxenergy;
// 		f->maxsize = settings->food_size;
// 		f->maxtotalFrames = settings->food_maxlifetime;
// 		f->position = critters[cid]->position;
// 
// 		if ( critters[cid]->energyLevel > settings->food_maxenergy )
// 		{
// 			f->energy = settings->food_maxenergy;
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
// 		//f->resize(settings->food_size);
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

	if ( critters[cid]->carriesCorpse )
	{
		critters[cid]->corpseBeingCarried->isCarried = false;

		// drop the food back down
		critters[cid]->corpseBeingCarried->position.y -= critters[cid]->size;
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
	destroyWall();

	stringstream buf;
	buf << "Wall type: " << settings->walltype;

	if ( settings->walltype == 1 )
	{
		for ( unsigned int i=0; i < 4*sizeY; i++ )
		{
			Wall *w = new Wall();
			walls.push_back( w );
			walls[i]->resize(0.25f);
			walls[i]->position.x = sizeX/2.0f;
			walls[i]->position.z = 0.125 + ((float)i*0.25);
		}
		Textmessage::Instance()->add(buf);
	}

	else if ( settings->walltype == 2 )
	{
		for ( unsigned int i=0; i < (4*sizeY); i++ )
		{
			Wall *w = new Wall();
			walls.push_back( w );
			walls[i]->resize(0.25f);
			walls[i]->position.x = sizeX/2.0f;
			walls[i]->position.z = 0.125 + ((float)i*0.25);
		}
		walls[ (unsigned int)(sizeY*2.0f)-2 ]->toggle();
		walls[ (unsigned int)(sizeY*2.0f)-1 ]->toggle();
		walls[ (unsigned int)(sizeY*2.0f)   ]->toggle();
		walls[ (unsigned int)(sizeY*2.0f)+1 ]->toggle();

		Textmessage::Instance()->add(buf);
	}

	else if ( settings->walltype == 3 )
	{
		for ( unsigned int i=0; i < 4*sizeX; i++ )
		{
			Wall *w = new Wall();
			walls.push_back( w );
			walls[i]->resize(0.25f);
			walls[i]->position.x = 0.125 + ((float)i*0.25);
			walls[i]->position.z = sizeY/2.0f;
		}
		Textmessage::Instance()->add(buf);
	}

	else if ( settings->walltype == 4 )
	{
		for ( unsigned int i=0; i < 4*sizeX; i++ )
		{
			Wall *w = new Wall();
			walls.push_back( w );
			walls[i]->resize(0.25f);
			walls[i]->position.x = 0.125 + ((float)i*0.25);
			walls[i]->position.z = sizeY/2.0f;
		}
		walls[ (unsigned int)(sizeX*2.0f)-2 ]->toggle();
		walls[ (unsigned int)(sizeX*2.0f)-1 ]->toggle();
		walls[ (unsigned int)(sizeX*2.0f)   ]->toggle();
		walls[ (unsigned int)(sizeX*2.0f)+1 ]->toggle();

		Textmessage::Instance()->add(buf);
	}

	else if ( settings->walltype == 5 )
	{
		unsigned int wcount = 0;
		for ( unsigned int i = 0; i < (unsigned int)(3.5f*sizeY); i++ )
		{
			Wall *w = new Wall();
			walls.push_back( w );
			walls[wcount]->resize(0.25f);
			walls[wcount]->position.x = 2*sizeX/3.0f;
			walls[wcount]->position.z = 0.125f + ((float)i*0.25);
			wcount++;
		}
		for ( unsigned int i = 0; i < (unsigned int)(3.5f*sizeY); i++ )
		{
			Wall *w = new Wall();
			walls.push_back( w );
			walls[wcount]->resize(0.25f);
			walls[wcount]->position.x = sizeX/3.0f;
			walls[wcount]->position.z = sizeY - 0.125f - ((float)i*0.25);
			wcount++;
		}

		Textmessage::Instance()->add(buf);
	}

	else if ( settings->walltype == 6 )
	{
		unsigned int wcount = 0;
		for ( unsigned int i = 0; i < (unsigned int)(3.5f*sizeY); i++ )
		{
			Wall *w = new Wall();
			walls.push_back( w );
			walls[wcount]->resize(0.25f);
			walls[wcount]->position.x = sizeX/3.0f;
			walls[wcount]->position.z = 0.125 + ((float)i*0.25);
			wcount++;
		}
		for ( unsigned int i = 0; i < (unsigned int)(3.5f*sizeY); i++ )
		{
			Wall *w = new Wall();
			walls.push_back( w );
			walls[wcount]->resize(0.25f);
			walls[wcount]->position.x = 2*sizeX/3.0f;
			walls[wcount]->position.z = sizeY - 0.125 - ((float)i*0.25);
			wcount++;
		}

		Textmessage::Instance()->add(buf);
	}

	else if ( settings->walltype == 7 )
	{
		unsigned int wcount = 0;
		for ( unsigned int i = 0; i < (unsigned int)(3.5f*sizeX); i++ )
		{
			Wall *w = new Wall();
			walls.push_back( w );
			walls[wcount]->resize(0.25f);
			walls[wcount]->position.x = 0.125f + ((float)i*0.25);
			walls[wcount]->position.z = 2*sizeY/3.0f;
			wcount++;
		}
		for ( unsigned int i = 0; i < (unsigned int)(3.5f*sizeX); i++ )
		{
			Wall *w = new Wall();
			walls.push_back( w );
			walls[wcount]->resize(0.25f);
			walls[wcount]->position.x = sizeX - 0.125f - ((float)i*0.25);
			walls[wcount]->position.z = sizeY/3.0f;
			wcount++;
		}

		Textmessage::Instance()->add(buf);
	}

	else if ( settings->walltype == 8 )
	{
		unsigned int wcount = 0;
		for ( unsigned int i = 0; i < (unsigned int)(3.5f*sizeX); i++ )
		{
			Wall *w = new Wall();
			walls.push_back( w );
			walls[wcount]->resize(0.25f);
			walls[wcount]->position.x = 0.125 + ((float)i*0.25);
			walls[wcount]->position.z = sizeY/3.0f;
			wcount++;
		}
		for ( unsigned int i = 0; i < (unsigned int)(3.5f*sizeX); i++ )
		{
			Wall *w = new Wall();
			walls.push_back( w );
			walls[wcount]->resize(0.25f);
			walls[wcount]->position.x = sizeX - 0.125 - ((float)i*0.25);
			walls[wcount]->position.z = 2*sizeY/3.0f;
			wcount++;
		}

		Textmessage::Instance()->add(buf);
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

void WorldB::drawWithinCritterSight(unsigned int cid)
{
	CritterB *c = critters[cid];
	//c->place();

	// draw everything in it's sight

//	draw floor;
	glPushMatrix();
		glScalef( floor.gridsizeX, 0.0f, floor.gridsizeY );
		glCallList(displayLists+3);
	glPopMatrix();

	for( unsigned int j=0; j < critters.size(); j++)
	{
		if ( cid != j )
		{
			CritterB *f = critters[j];
			if ( c->isWithinSight(f->position) )
			{
				glPushMatrix();
					glTranslatef( f->position.x, f->position.y, f->position.z );
					glRotatef( f->rotation, 0.0f, 1.0f, 0.0f );
					glScalef( f->halfsize, f->halfsize, f->halfsize );

					// body
					glColor4f( f->color[0], f->color[1], f->color[2], 0.0f );
					glCallList(displayLists+1);

					// nose
					glColor4f( f->nosecolor[0], f->nosecolor[1], f->nosecolor[2], 0.0f );
					glCallList(displayLists+2);

				glPopMatrix();
			}
		}
	}

	glColor4f( 0.0f, 1.0f, 0.0f, 1.0f );
	for( unsigned int j=0; j < food.size(); j++)
	{
		Food *f = food[j];
		if ( c->isWithinSight(f->position) )
		{
			glPushMatrix();
				glTranslatef( f->position.x, f->position.y, f->position.z );
				glScalef( f->halfsize, f->halfsize, f->halfsize );
				glCallList(displayLists);
			glPopMatrix();
		}
	}

	glColor4f( 0.5f, 0.0f, 0.0f, 0.5f );
	for( unsigned int j=0; j < corpses.size(); j++)
	{
		Corpse *f = corpses[j];
		if ( c->isWithinSight(f->position) )
		{
			glPushMatrix();
				glTranslatef( f->position.x, f->position.y, f->position.z );
				glScalef( f->halfsize, f->halfsize, f->halfsize );
				glCallList(displayLists);
			glPopMatrix();
		}
	}

	glColor4f( 0.5f, 0.5f, 0.0f, 0.0f );
	for( unsigned int j=0; j < walls.size(); j++)
	{
		Wall *f = walls[j];
		if ( !f->disabled && c->isWithinSight(f->position) )
		{
			glPushMatrix();
				glTranslatef( f->position.x, f->position.y, f->position.z );
				glScalef( f->halfsize, f->halfsize, f->halfsize );
				glCallList(displayLists);
			glPopMatrix();
		}
	}

	glColor4f( 1.0f, 0.0f, 0.0f, 0.0f );
	for( unsigned int j=0; j < bullets.size(); j++)
	{
		Bullet *f = bullets[j];
		if ( c->isWithinSight(f->position) )
		{
			glPushMatrix();
				glTranslatef( f->position.x, f->position.y, f->position.z );
				glScalef( f->halfsize, f->halfsize, f->halfsize );
				glCallList(displayLists);
			glPopMatrix();
		}
	}
}

void WorldB::drawWithGrid()
{
	// draw floor
	grid.draw();

	glColor4f( 0.0f, 1.0f, 0.0f, 1.0f );
	for( unsigned int i=0; i < food.size(); i++)
	{
		Food *f = food[i];
		glPushMatrix();
			glTranslatef( f->position.x, f->position.y, f->position.z );
			glScalef( f->halfsize, f->halfsize, f->halfsize );
			glCallList(displayLists);
		glPopMatrix();
	}

	glColor4f( 0.5f, 0.0f, 0.0f, 0.5f );
	for( unsigned int i=0; i < corpses.size(); i++)
	{
		Corpse *f = corpses[i];
		glPushMatrix();
			glTranslatef( f->position.x, f->position.y, f->position.z );
			glScalef( f->halfsize, f->halfsize, f->halfsize );
			glCallList(displayLists);
		glPopMatrix();
	}

	glColor4f( 0.5f, 0.5f, 0.0f, 0.0f );
	for( unsigned int i=0; i < walls.size(); i++)
	{
		Wall *f = walls[i];
		if ( !f->disabled )
		{
			glPushMatrix();
				glTranslatef( f->position.x, f->position.y, f->position.z );
				glScalef( f->halfsize, f->halfsize, f->halfsize );
				glCallList(displayLists);
			glPopMatrix();
		}
	}

	glColor4f( 1.0f, 0.0f, 0.0f, 0.0f );
	for( unsigned int i=0; i < bullets.size(); i++)
	{
		Bullet *f = bullets[i];
		glPushMatrix();
			glTranslatef( f->position.x, f->position.y, f->position.z );
			glScalef( f->halfsize, f->halfsize, f->halfsize );
			glCallList(displayLists);
		glPopMatrix();
	}

	for( unsigned int i=0; i < critters.size(); i++)
	{
		CritterB *f = critters[i];
		glPushMatrix();
			glTranslatef( f->position.x, f->position.y, f->position.z );
			glRotatef( f->rotation, 0.0f, 1.0f, 0.0f );
			glScalef( f->halfsize, f->halfsize, f->halfsize );

				// body
				glColor4f( f->color[0], f->color[1], f->color[2], 0.0f );
				glCallList(displayLists+1);

				// nose
				glColor4f( f->nosecolor[0], f->nosecolor[1], f->nosecolor[2], 0.0f );
				glCallList(displayLists+2);

		glPopMatrix();

// 		// draw visual field
// 		glPushMatrix();
// 			glBegin(GL_TRIANGLES);
// 				glVertex3f(f->frustCullTriangle1.x, f->frustCullTriangle1.y, f->frustCullTriangle1.z);
// 				glVertex3f(f->frustCullTriangle2.x, f->frustCullTriangle2.y, f->frustCullTriangle2.z);
// 				glVertex3f(f->frustCullTriangle3.x, f->frustCullTriangle3.y, f->frustCullTriangle3.z);
// 			glEnd();
// 		glPopMatrix();

	}
}

void WorldB::loadAllCritters()
{
	vector<string> files;
	dirH.listContentsFull(loaddir, files);

	for ( unsigned int i = 0; i < files.size(); i++ )
	{
		if ( parseH->Instance()->endMatches( ".cr", files[i] ) )
		{

			string content;
			fileH.open( files[i], content );

			CritterB *c = new CritterB(content);

			unsigned int error = 0;

			if ( c->retinasize != settings->critter_retinasize ) error = 1;

			if ( !error)
			{
				critters.push_back( c );

				c->critterID = currentCritterID++;

				// start energy
				c->energyLevel = settings->critter_startenergy;
				freeEnergy -= c->energyLevel;

				positionCritterB(critters.size()-1);
				c->setRotation( randgen->Instance()->get(0,360) );

				c->brain.wireArch();
				c->retina = retina;
			}
			else if ( error == 1 )
			{
				stringstream buf;
				buf << "ERROR: critter retinasize (" << c->retinasize << ") doesn't fit world retinasize (" << settings->critter_retinasize << ")" << files[i];
				Textmessage::Instance()->add(buf);

//				cerr << "ERROR: critter retinasize (" << c->retinasize << ") doesn't fit world retinasize (" << settings->critter_retinasize << ")" << endl;
			}
		}
	}
	stringstream buf;
	buf << "Loaded critters from " << loaddir;
	Textmessage::Instance()->add(buf);
	//cerr << endl << "Loaded critters from " << loaddir << endl << endl;
}

void WorldB::saveAllCritters()
{
	// determine save directory
	stringstream buf;
	buf << savedir << "/" << settings->profileName;
	string subprofiledir = buf.str();
	
	buf << "/" << time(0);
	string subsavedir = buf.str();

	// makde dirs
	if ( !dirH.exists(savedir) )		dirH.make(savedir);
	if ( !dirH.exists(subprofiledir) )	dirH.make(subprofiledir);
	if ( !dirH.exists(subsavedir) )		dirH.make(subsavedir);

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
 	//cerr << endl << "Saved critters to " << subsavedir << endl << endl;
	stringstream buf2;
	buf2 << "Saved critters to " << subsavedir;
	Textmessage::Instance()->add(buf2);

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

bool WorldB::spotIsFree(Vector3f &position, float halfsize, unsigned int exclude)
{

// within world borders?

	// left border
	if ( position.x - halfsize <= 0 )		return false;
	// right border
	else if ( position.x + halfsize >= sizeX )	return false;
	// bottom border
	if ( position.z - halfsize <= 0 )		return false;
	// top border
	else if ( position.z + halfsize >= sizeY )	return false;

// check for touch walls

	for ( unsigned int j=0; j < walls.size(); j++ )
	{
		Wall *w = walls[j];

		if ( !w->disabled )
		{
			float avgSize = halfsize + w->halfsize;
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
			float avgSize = halfsize + cj->halfsize;
			if ( fabs( position.x - cj->position.x ) <= avgSize &&  fabs( position.z - cj->position.z ) <= avgSize )
			{
				return false;
			}
		}
	}

	return true;
}

bool WorldB::spotIsFree(Vector3f &position, float halfsize)
{

// within world borders?

	// left border
	if ( position.x - halfsize <= 0 )		return false;
	// right border
	else if ( position.x + halfsize >= sizeX )	return false;
	// bottom border
	if ( position.z - halfsize <= 0 )		return false;
	// top border
	else if ( position.z + halfsize >= sizeY )	return false;

// check if touching walls

	for ( unsigned int j=0; j < walls.size(); j++ )
	{
		Wall *w = walls[j];

		if ( !w->disabled )
		{
			float avgSize = halfsize + w->halfsize;
			if ( fabs( position.x - w->position.x ) <= avgSize &&  fabs( position.z - w->position.z ) <= avgSize )
			{
				return false;
			}
		}
	}

// check if touching other creatures

	for ( unsigned int j=0; j < critters.size(); j++ )
	{
		CritterB *cj = critters[j];
		float avgSize = halfsize + cj->halfsize;
		if ( fabs( position.x - cj->position.x ) <= avgSize &&  fabs( position.z - cj->position.z ) <= avgSize )
		{
			return false;
		}
	}

	return true;
}

Vector3f WorldB::findEmptySpace(float halfsize)
{
	Vector3f pos;
	pos.x = (float)randgen->Instance()->get( 0, 100*sizeX ) / 100;
	pos.y = halfsize;
	pos.z = (float)randgen->Instance()->get( 0, 100*sizeY ) / 100;

	while ( !spotIsFree(pos, halfsize) )
	{
		pos.x = (float)randgen->Instance()->get( 0, 100*sizeX ) / 100;
		pos.y = halfsize;
		pos.z = (float)randgen->Instance()->get( 0, 100*sizeY ) / 100;
	}
	return pos;
}

WorldB::~WorldB()
{
	for ( unsigned int i=0; i < food.size(); i++ )		delete food[i];
	for ( unsigned int i=0; i < corpses.size(); i++ )	delete corpses[i];
	for ( unsigned int i=0; i < bullets.size(); i++ )	delete bullets[i];
	for ( unsigned int i=0; i < critters.size(); i++ )	delete critters[i];
	free(retina);
}

