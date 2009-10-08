#ifdef _WIN32
	#include <windows.h>
	#include <shlobj.h>
#endif
#include "worldb.h"

WorldB::WorldB()
{
	// settings and pointers
	settings = Settings::Instance();
		retinasperrow = settings->getCVarPtr("retinasperrow");
		critter_maxlifetime = settings->getCVarPtr("critter_maxlifetime");
		critter_maxenergy = settings->getCVarPtr("critter_maxenergy");
		critter_autosaveinterval = settings->getCVarPtr("critter_autosaveinterval");
		critter_killhalfat = settings->getCVarPtr("critter_killhalfat");
		critter_retinasize = settings->getCVarPtr("critter_retinasize");
		critter_sightrange = settings->getCVarPtr("critter_sightrange");
		food_maxlifetime = settings->getCVarPtr("food_maxlifetime");
		food_maxenergy = settings->getCVarPtr("food_maxenergy");

	statsBuffer = Statsbuffer::Instance();

	freeEnergy = *food_maxenergy * settings->getCVar("energy");
	settings->freeEnergyInfo = freeEnergy;
		
	currentCritterID	= 1;
	insertCritterCounter	= 0;
	autosaveCounter		= 0.0f;
	insertHight		= 1.0f;
	
	// vision retina allocation
	items = 4 * 800 * 600;
	retina = (unsigned char*)malloc(items);
	memset(retina, 0, items);

	// home & program directory
	createDirs();

	m_collisionConfiguration = new btDefaultCollisionConfiguration();

	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
	//m_dispatcher = new SpuGatheringCollisionDispatcher(m_collisionConfiguration);

	btVector3 worldAabbMin(-10000,-10000,-10000);
	btVector3 worldAabbMax(10000,10000,10000);
	m_broadphase = new btAxisSweep3 (worldAabbMin, worldAabbMax);
	m_broadphase->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
	m_solver = new btSequentialImpulseConstraintSolver;

	m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher,m_broadphase,m_solver,m_collisionConfiguration);

// 	m_dynamicsWorld->getSolverInfo().m_solverMode = SOLVER_USE_WARMSTARTING + SOLVER_SIMD;
	m_dynamicsWorld->getSolverInfo().m_solverMode = SOLVER_SIMD + SOLVER_USE_WARMSTARTING + SOLVER_CACHE_FRIENDLY;
	
	m_dynamicsWorld->getSolverInfo().m_numIterations = 10;
	// raycast
	raycast = new Raycast(m_dynamicsWorld);

	// mousepicker
	mousepicker = new Mousepicker(m_dynamicsWorld);

	// determine vision width
	picwidth = *retinasperrow * (*critter_retinasize+1);

	// reset cam
		resetCamera();

	
// 	debugDrawer.setDebugMode(btIDebugDraw::DBG_DrawWireframe|btIDebugDraw::DBG_DrawConstraints+btIDebugDraw::DBG_DrawConstraintLimits);
// 	debugDrawer.setDebugMode(btIDebugDraw::DBG_DrawConstraints+btIDebugDraw::DBG_DrawConstraintLimits);
// 	debugDrawer.setDebugMode(btIDebugDraw::DBG_DrawConstraints);
// 	debugDrawer.setDebugMode(btIDebugDraw::DBG_DrawConstraintLimits);
// 	m_dynamicsWorld->setDebugDrawer(&debugDrawer);
}

void WorldB::init()
{
	makeFloor();

// 	// reset cam
// 		resetCamera();

	if ( settings->getCVar("autoload") )
		loadAllCritters();
}

void WorldB::castMouseRay()
{
// 	cerr << "casting" << endl;
	mouseRay = raycast->cast( -camera.position, mouseRayTo );

	mouseRayHit = false;
	if ( mouseRay.hit )
	{
		if ( !( mouseRay.hitBody->isStaticObject() || mouseRay.hitBody->isKinematicObject() ) )
		{
			Food* f = static_cast<Food*>(mouseRay.hitBody->getUserPointer());
			if ( f->type == 1 )
			{
				mouseRayHit = true;
				mouseRayHitF = f;
				mouseRayHitType = f->type;
			}
			else
			{
				CritterB* b = static_cast<CritterB*>(mouseRay.hitBody->getUserPointer());
				if ( b->type == 0 )
				{
					mouseRayHit = true;
					mouseRayHitC = b;
					mouseRayHitType = b->type;
				}
			}
		}
	}
}

void WorldB::calcMouseDirection(const int& x, const int& y)
{
// 	cerr << "updating mouserayto" << endl;
	mouseRayTo = camera.getScreenDirection(x, y);
}

void WorldB::pickBody(const int& x, const int& y)
{
// 	castMouseRay();
	if ( mouseRayHit )
	{
		mousepicker->attach( mouseRay.hitBody, mouseRay.hitPosition, -camera.position, mouseRayTo );

		if ( mouseRayHitType == 1 )
			mousepicker->pickedBool = &mouseRayHitF->isPicked;
		else if ( mouseRayHitType == 0 )
			mousepicker->pickedBool = &mouseRayHitC->isPicked;

		*mousepicker->pickedBool = true;
	}
}

void WorldB::movePickedBodyTo()
{
	if ( mousepicker->active )
		mousepicker->moveTo( camera.position, mouseRayTo );
}

void WorldB::movePickedBodyFrom()
{
	if ( mousepicker->active )
		mousepicker->moveFrom( camera.position );
}

void WorldB::process()
{
	// kill half?
		killHalf();

	// Remove food
		expireFood();

	// Autoinsert Food
		autoinsertFood();

	// remove all dead critters
		expireCritters();

	// Autosave Critters?
		autosaveCritters();

	// Autoinsert Critters?
		autoinsertCritters();

	// do a bullet step
		m_dynamicsWorld->stepSimulation(Timer::Instance()->bullet_ms / 1000.f);

	renderVision();
	grabVision();

	// process all critters
	unsigned int lmax = critters.size();
	for( unsigned int i=0; i < lmax; i++)
	{
		CritterB *c = critters[i];

		// TOUCH inputs and references -> find overlappings
			checkCollisions(  c );

		// process
			c->process();

		// record critter used energy
			freeEnergy += c->energyUsed;

		// process Output Neurons
			eat(c);

		// procreation if procreation energy trigger is hit
			procreate(c);
	}


}

void WorldB::procreate( CritterB* c )
{
	if ( c->procreate && c->canProcreate )
	{
		bool brainmutant = false;
		bool bodymutant = false;
		if ( randgen->Instance()->get(1,100) <= settings->getCVar("brain_mutationrate") )
			brainmutant = true;

		if ( randgen->Instance()->get(1,100) <= settings->getCVar("body_mutationrate") )
			bodymutant = true;

		btDefaultMotionState* myMotionState = (btDefaultMotionState*)c->body.bodyparts[0]->body->getMotionState();
		btVector3 np = myMotionState->m_graphicsWorldTrans.getOrigin();
		np.setY(insertHight);
		np.setX(np.getX()+0.6f);
		CritterB *nc = new CritterB(*c, currentCritterID++, np, brainmutant, bodymutant);
		//CritterB *nc = new CritterB(*c, currentCritterID++, findPosition(), mutant);

		// display message of birth
			stringstream buf;
			buf << setw(4) << c->critterID << " : " << setw(4) << nc->critterID;
			buf << " ad: " << setw(4) << nc->adamdist;
			buf << " n: " << setw(4) << nc->brain.totalNeurons << " s: " << setw(5) << nc->brain.totalSynapses;

			if ( brainmutant ) buf << " brain mutant";
			if ( bodymutant ) buf << " body mutant";
			Textverbosemessage::Instance()->addBirth(buf);

		// split energies in half
			nc->energyLevel = c->energyLevel/2.0f;
			c->energyLevel = nc->energyLevel;

		// reset procreation energy count
			critters.push_back( nc );
			nc->calcFramePos(critters.size()-1);
	}
}

void WorldB::eat( CritterB* c )
{
	if ( c->eat )
	{
		if ( c->touchingFood )
		{
			Food* f = c->touchedFoodID;
			float eaten = *critter_maxenergy / 100.0f;
			if ( c->energyLevel + eaten > *critter_maxenergy )
				eaten -= (c->energyLevel + eaten) - *critter_maxenergy;
			if ( f->energyLevel - eaten < 0 )
				eaten = f->energyLevel;

			c->energyLevel += eaten;
			f->energyLevel -= eaten;
		}
		else if ( settings->getCVar("critter_enableomnivores") && c->touchingCritter )
		{
			CritterB* ct = c->touchedCritterID;
			float eaten = *critter_maxenergy / 100.0f;
			if ( c->energyLevel + eaten > *critter_maxenergy )
				eaten -= (c->energyLevel + eaten) - *critter_maxenergy;
			if ( ct->energyLevel - eaten < 0 )
				eaten = ct->energyLevel;

			c->energyLevel += eaten;
			ct->energyLevel -= eaten;
			ct->eaten = true;
		}
	}
}

void WorldB::killHalf()
{
	if ( critters.size() >= *critter_killhalfat )
	{
		killHalfOfCritters();
		
		// reduce energy :)
		if ( settings->getCVar("killhalfdecreaseenergybypct") > 0 )
		{
			if ( (settings->freeEnergyInfo - *food_maxenergy) / *food_maxenergy >= 0.0f )
			{
				int dec = ((settings->freeEnergyInfo / settings->getCVar("food_maxenergy")) / 100) * settings->getCVar("killhalfdecreaseenergybypct");
				settings->freeEnergyInfo -= dec * settings->getCVar("food_maxenergy");
				freeEnergy -= dec * settings->getCVar("food_maxenergy");
			}
		}
	}
}

void WorldB::autoinsertCritters()
{
	// insert critter if < minimum
	if ( critters.size() < settings->getCVar("mincritters") )
		insertCritter();

	// insert critter if insertcritterevery is reached
	if ( settings->getCVar("insertcritterevery") > 0 )
	{
		if ( insertCritterCounter >= settings->getCVar("insertcritterevery") )
		{
			insertCritter();
			insertCritterCounter = 0;
		}
		else
		{
			insertCritterCounter++;
		}
	}
}

void WorldB::autosaveCritters()
{
	if ( *critter_autosaveinterval > 0 )
	{
		autosaveCounter += ((float)Timer::Instance()->elapsed/1000);
		if ( autosaveCounter > *critter_autosaveinterval )
		{
			autosaveCounter = 0.0f;
			saveAllCritters();
		}
	}
}

void WorldB::autoinsertFood()
{
	if ( freeEnergy >= *food_maxenergy )
	{
		insertRandomFood(1, *food_maxenergy);
		freeEnergy -= *food_maxenergy;
		//cerr << "food: " << food.size() << endl;
	}
}

void WorldB::expireCritters()
{
	for( unsigned int i=0; i < critters.size(); i++)
	{
		// see if energy level isn't below 0 -> die, or die of old age
		if ( critters[i]->energyLevel <= 0.0f )
		{
			stringstream buf;
			if ( critters[i]->eaten )
				buf << setw(4) << critters[i]->critterID << " eaten";
			else
				buf << setw(4) << critters[i]->critterID << " starved";
			Textverbosemessage::Instance()->addDeath(buf);

			removeCritter(i);
			i--;
		}
		// die of old age
		else if ( critters[i]->totalFrames > *critter_maxlifetime )
		{
			stringstream buf;
			buf << setw(4) << critters[i]->critterID << " old";
			Textverbosemessage::Instance()->addDeath(buf);

			removeCritter(i);
			i--;
		}
		// die if y < 100
		else
		{
			btDefaultMotionState* myMotionState = (btDefaultMotionState*)critters[i]->body.bodyparts[0]->body->getMotionState();
			btVector3 pos = myMotionState->m_graphicsWorldTrans.getOrigin();
			
			if ( pos.getY() < -100.0f )
			{
				stringstream buf;
				buf << setw(4) << critters[i]->critterID << " went offworld";
				Textverbosemessage::Instance()->addDeath(buf);

				removeCritter(i);
				i--;
			}
		}
	}
}

void WorldB::expireFood()
{
	for( unsigned int i=0; i < food.size(); i++)
	{
		// food was eaten
		if ( food[i]->energyLevel <= 0 )
		{
			freeEnergy += food[i]->energyLevel;
			if ( food[i]->isPicked )
				mousepicker->detach();
			delete food[i];
			food.erase(food.begin()+i);
			i--;
		}
		// old food, this should remove stuff from corners
		else if ( ++food[i]->totalFrames >= *food_maxlifetime )
		{
			freeEnergy += food[i]->energyLevel;
			if ( food[i]->isPicked )
				mousepicker->detach();
			delete food[i];
			food.erase(food.begin()+i);
			i--;
		}
/*		// die if y < 100
		else
		{
			btDefaultMotionState* myMotionState = (btDefaultMotionState*)food[i]->body.bodyparts[0]->body->getMotionState();
			btVector3 pos = myMotionState->m_graphicsWorldTrans.getOrigin();

			if ( pos.getY() < -100.0f )
			{
				freeEnergy += food[i]->energyLevel;
				if ( food[i]->isPicked )
					mousepicker->detach();
				delete food[i];
				food.erase(food.begin()+i);
				i--;
			}
		}*/
	}
}

void WorldB::getGeneralStats()
{
	settings->info_totalNeurons = 0;
	settings->info_totalSynapses = 0;
	settings->info_totalAdamDistance = 0;
	settings->info_totalBodyparts = 0;
	settings->info_totalWeight = 0;

	settings->info_critters = critters.size();
	settings->info_food = food.size();

	for( unsigned int i=0; i < critters.size(); i++)
	{
		settings->info_totalNeurons		+= critters[i]->brain.totalNeurons;
		settings->info_totalSynapses		+= critters[i]->brain.totalSynapses;
		settings->info_totalAdamDistance	+= critters[i]->adamdist;
		settings->info_totalBodyparts		+= critters[i]->body.bodyparts.size();
		settings->info_totalWeight		+= critters[i]->body.totalWeight;
	}

	statsBuffer->add();

}

void WorldB::checkCollisions( CritterB* c )
{
	// set inputs to false and recheck
		c->touchingFood = false;
		c->touchingCritter = false;

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
							else
							{
								// Touching Critter
								CritterB* b = static_cast<CritterB*>(Collidingobject);
								if ( b->type == 0 )
								{
									stop = true;
									c->touchingCritter = true;
									c->touchedCritterID = b;
								}
							}
						}
					}
				}
			}
		}
	}
}

void WorldB::insertRandomFood(int amount, float energy)
{
	for ( int i=0; i < amount; i++ )
	{
		Food *f = new Food;
		f->energyLevel = energy;
		//f->resize();
		f->createBody( m_dynamicsWorld, findPosition() );
		
		food.push_back( f );
	}
}

void WorldB::insertCritter()
{
	CritterB *c = new CritterB(m_dynamicsWorld, currentCritterID++, findPosition(), retina);
	critters.push_back( c );
	c->calcFramePos(critters.size()-1);

	// start energy
	freeEnergy -= c->energyLevel;
}

btVector3 WorldB::findPosition()
{
	return btVector3( (float)randgen->Instance()->get( 0, 100*settings->getCVar("worldsizeX") ) / 100, insertHight, (float)randgen->Instance()->get( 0, 100*settings->getCVar("worldsizeY") ) / 100 );
}

void WorldB::removeCritter(unsigned int cid)
{
	freeEnergy += critters[cid]->energyLevel;

	if ( critters[cid]->isPicked )
		mousepicker->detach();

	delete critters[cid];
	critters.erase(critters.begin()+cid);

	// update higher retina frame positions
	for ( unsigned int c = cid; c < critters.size(); c++ )
		critters[c]->calcFramePos(c);
}

void WorldB::killHalfOfCritters()
{
// 	unsigned int c = 0;
// 	unsigned int halfc = critters.size()/2;
// 	while ( c < halfc )
// 	{
// 		freeEnergy += critters[0]->energyLevel;
// 
// 		delete critters[0];
// 		critters.erase(critters.begin());
// 		c++;
// 	}

	for ( unsigned int c = 0; c < critters.size(); c++ )
	{
		freeEnergy += critters[c]->energyLevel;

		if ( critters[c]->isPicked )
			mousepicker->detach();

		delete critters[c];
		critters.erase(critters.begin()+c);
	}

	// update higher retina frame positions
	for ( unsigned int c = 0; c < critters.size(); c++ )
		critters[c]->calcFramePos(c);
}

void WorldB::drawWithGrid()
{
	for( unsigned int i=0; i < critters.size(); i++)
		critters[i]->draw(true);

	for( unsigned int i=0; i < food.size(); i++)
		food[i]->draw();

	for( unsigned int i=0; i < walls.size(); i++)
		walls[i]->draw();

	m_dynamicsWorld->debugDrawWorld();

	// draw floor
// 	grid.draw();
}

void WorldB::drawWithoutFaces()
{
	for( unsigned int i=0; i < critters.size(); i++)
		critters[i]->draw(false);

	for( unsigned int i=0; i < food.size(); i++)
		food[i]->draw();

	for( unsigned int i=0; i < walls.size(); i++)
		walls[i]->draw();

	// draw floor
// 	grid.draw();
}

void WorldB::drawWithinCritterSight(unsigned int cid)
{
	CritterB *c = critters[cid];

	if ( c->body.mouths.size() > 0 )
	{
		btDefaultMotionState* cmyMotionState = (btDefaultMotionState*)c->body.mouths[0]->body->getMotionState();
		btVector3 cposi = cmyMotionState->m_graphicsWorldTrans.getOrigin();

		// draw everything in it's sight
		float sightrange = (float)*critter_sightrange/10;

		btScalar position[16];

		for( unsigned int i=0; i < walls.size(); i++)
			walls[i]->draw();

		for( unsigned int i=0; i < food.size(); i++)
		{
			Food *f = food[i];
			btDefaultMotionState* fmyMotionState = (btDefaultMotionState*)f->body.bodyparts[0]->body->getMotionState();
			btVector3 fposi = fmyMotionState->m_graphicsWorldTrans.getOrigin();
			if ( cposi.distance(fposi) < sightrange )
				f->draw();
		}

		for( unsigned int j=0; j < critters.size(); j++)
		{
			if ( cid != j )
			{
				CritterB *f = critters[j];
				for( unsigned int b=0; b < f->body.bodyparts.size(); b++)
				{
					btDefaultMotionState* fmyMotionState = (btDefaultMotionState*)f->body.bodyparts[b]->body->getMotionState();
					btVector3 fposi = fmyMotionState->m_graphicsWorldTrans.getOrigin();
					if ( cposi.distance(fposi) < sightrange )
					{
						fmyMotionState->m_graphicsWorldTrans.getOpenGLMatrix(position);
						glPushMatrix(); 
						glMultMatrixf(position);

								glColor4f( f->color[0], f->color[1], f->color[2], 0.0f );

								const btBoxShape* boxShape = static_cast<const btBoxShape*>(f->body.bodyparts[b]->shape);
								btVector3 halfExtent = boxShape->getHalfExtentsWithMargin();
								glScaled(halfExtent[0], halfExtent[1], halfExtent[2]);

								Displaylists::Instance()->call(0);

						glPopMatrix();
					}
				}
			}
		}
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
			stringstream buf;
			buf << "loading " << files[i];
			Textmessage::Instance()->add(buf);

			string content;
			fileH.open( files[i], content ); 

			CritterB *c = new CritterB(content, m_dynamicsWorld, findPosition(), retina);

			unsigned int error = 0;
			if ( c->retinasize != *critter_retinasize ) error = 1;

			if ( !error)
			{
				critters.push_back( c );

				c->critterID = currentCritterID++;
				c->calcFramePos(critters.size()-1);

				// start energy
				freeEnergy -= c->energyLevel;
			}
			else
			{
				delete c;
				if ( error == 1 )
				{
					stringstream buf;
					buf << "ERROR: critter retinasize (" << c->retinasize << ") doesn't fit world retinasize (" << *critter_retinasize << ")" << files[i];
					Textmessage::Instance()->add(buf);

					cerr << "ERROR: critter retinasize (" << c->retinasize << ") doesn't fit world retinasize (" << *critter_retinasize << ")" << endl;
				}
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
		// determine filename
		stringstream filename;
		filename << subsavedir << "/" << "critter" << i << ".cr";
	
		// save critters
		fileH.save(filename.str(), critters[i]->saveCritterB());
	}
 	//cerr << endl << "Saved critters to " << subsavedir << endl << endl;
	stringstream buf2;
	buf2 << "Saved critters to " << subsavedir;
	Textmessage::Instance()->add(buf2);

}

void WorldB::createDirs()
{
#ifndef _WIN32
 	homedir = getenv("HOME");
 	if ( homedir.empty() ) {
		cout << "environment variable HOME not defined/detected" << endl;
		exit(0);
	}
	progdir = homedir;	progdir.append("/.critterding");
	savedir = progdir;	savedir.append("/save");
	loaddir = progdir;	loaddir.append("/load");
#else
	char mydoc[256];
	memset(mydoc, 0, sizeof(mydoc));

	SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, mydoc);
	homedir.assign(mydoc);
	progdir = homedir;	progdir.append("\\critterding");
	savedir = progdir;	savedir.append("\\save");
	loaddir = progdir;	loaddir.append("\\load");
#endif

//	cerr << progdir << endl;

	if ( !dirH.exists(progdir) ) dirH.make(progdir);
	if ( !dirH.exists(loaddir) ) dirH.make(loaddir);
}

void WorldB::resetCamera()
{
	unsigned int biggest = settings->getCVar("worldsizeX");
	if ( settings->getCVar("worldsizeY") > biggest )
		biggest = 1.4f*settings->getCVar("worldsizeY");

	camera.position = btVector3( -0.5f*settings->getCVar("worldsizeX"), -1.3f*biggest, -0.5f*settings->getCVar("worldsizeY"));
	camera.rotation = Vector3f( 90.0f,  0.0f, 0.0f);
}

void WorldB::makeFloor()
{
	for ( unsigned int i=0; i < walls.size(); i++ )	
		delete walls[i];
	walls.clear();

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
	
	if ( settings->getCVar("worldwalls") )
	{
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
	}
}


WorldB::~WorldB()
{
	for ( unsigned int i=0; i < food.size(); i++ )		delete food[i];
// 	for ( unsigned int i=0; i < corpses.size(); i++ )	delete corpses[i];
// 	for ( unsigned int i=0; i < bullets.size(); i++ )	delete bullets[i];
	for ( unsigned int i=0; i < critters.size(); i++ )	delete critters[i];
	for ( unsigned int i=0; i < walls.size(); i++ )		delete walls[i];

	free(retina);

	delete m_collisionConfiguration;
	delete m_dispatcher;
	delete m_broadphase;
	delete m_solver;
	delete m_dynamicsWorld;
	
	delete raycast;
	delete mousepicker;
}
