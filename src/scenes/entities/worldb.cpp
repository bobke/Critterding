/*#ifdef _WIN32
	#include <windows.h>
	#include <shlobj.h>
#endif*/
#include "worldb.h"

WorldB::WorldB()
{
	// settings and pointers
	settings = Settings::Instance();
		retinasperrow = settings->getCVarPtr("retinasperrow");
		critter_maxlifetime = settings->getCVarPtr("critter_maxlifetime");
		critter_maxenergy = settings->getCVarPtr("critter_maxenergy");
		critter_autosaveinterval = settings->getCVarPtr("critter_autosaveinterval");
		critter_autoexchangeinterval = settings->getCVarPtr("critter_autoexchangeinterval");
		critter_killhalfat = settings->getCVarPtr("critter_killhalfat");
		critter_retinasize = settings->getCVarPtr("critter_retinasize");
		critter_sightrange = settings->getCVarPtr("critter_sightrange");
		critter_raycastvision = settings->getCVarPtr("critter_raycastvision");
		critter_enableomnivores = settings->getCVarPtr("critter_enableomnivores");
		critter_startenergy = settings->getCVarPtr("critter_startenergy");

		killhalf_decrenergypct = settings->getCVarPtr("killhalf_decrenergypct");
		killhalf_incrworldsizeX = settings->getCVarPtr("killhalf_incrworldsizeX");
		killhalf_incrworldsizeY = settings->getCVarPtr("killhalf_incrworldsizeY");
		killhalf_decrmaxlifetimepct = settings->getCVarPtr("killhalf_decrmaxlifetimepct");
		
		brain_mutationrate = settings->getCVarPtr("brain_mutationrate");
		body_mutationrate = settings->getCVarPtr("body_mutationrate");

		food_maxlifetime = settings->getCVarPtr("food_maxlifetime");
		food_maxenergy = settings->getCVarPtr("food_maxenergy");
		energy = settings->getCVarPtr("energy");
		headless = settings->getCVarPtr("headless");
		threads = settings->getCVarPtr("threads");
		mincritters = settings->getCVarPtr("mincritters");
		insertcritterevery = settings->getCVarPtr("critter_insertevery");
		worldsizeX = settings->getCVarPtr("worldsizeX");
		worldsizeY = settings->getCVarPtr("worldsizeY");

	statsBuffer = Statsbuffer::Instance();
	critterselection = Critterselection::Instance();
	// home & program directory
	dirlayout = Dirlayout::Instance();

	freeEnergy = *food_maxenergy * *energy;
		
	currentCritterID	= 1;
	insertCritterCounter	= 0;
	autosaveCounter		= 0.0f;
	autoexchangeCounter	= 0.0f;
	insertHight		= 1.0f;
	
	// vision retina allocation
	items = 4 * 800 * 600;
	retina = (unsigned char*)malloc(items);
	memset(retina, 0, items);

	// THREADED BULLET
/*	int maxNumOutstandingTasks = 4;
	m_collisionConfiguration = new btDefaultCollisionConfiguration();
	PosixThreadSupport::ThreadConstructionInfo constructionInfo("collision", processCollisionTask, createCollisionLocalStoreMemory, maxNumOutstandingTasks);
	m_threadSupportCollision = new PosixThreadSupport(constructionInfo);
	m_dispatcher = new SpuGatheringCollisionDispatcher(m_threadSupportCollision,maxNumOutstandingTasks,m_collisionConfiguration);
	
	btVector3 worldAabbMin(-10000,-10000,-10000);
	btVector3 worldAabbMax(10000,10000,10000);
	m_broadphase = new btAxisSweep3 (worldAabbMin, worldAabbMax);
	m_broadphase->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
	m_solver = new btSequentialImpulseConstraintSolver;
// 	m_solver = new SpuMinkowskiPenetrationDepthSolver();
	m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher,m_broadphase,m_solver,m_collisionConfiguration);

		m_dynamicsWorld->getSolverInfo().m_numIterations = 10;
		m_dynamicsWorld->getSolverInfo().m_solverMode = SOLVER_SIMD+SOLVER_USE_WARMSTARTING;

		m_dynamicsWorld->getDispatchInfo().m_enableSPU = true;*/
	// stop threaded bullet

	// NOT THREADED
	m_collisionConfiguration = new btDefaultCollisionConfiguration();
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
	btVector3 worldAabbMin(-10000,-10000,-10000);
	btVector3 worldAabbMax(10000,10000,10000);
	m_broadphase = new btAxisSweep3 (worldAabbMin, worldAabbMax);
	m_broadphase->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
	m_solver = new btSequentialImpulseConstraintSolver;
	m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher,m_broadphase,m_solver,m_collisionConfiguration);
	// END NOT THREADED
	
// 	btVector3 v = m_dynamicsWorld->getGravity();
// 	cerr << v.y() << endl;
// 	m_dynamicsWorld->setGravity( btVector3(0.0f, -50.0f, 0.0f) );

	m_dynamicsWorld->getSolverInfo().m_solverMode = SOLVER_USE_WARMSTARTING + SOLVER_SIMD;
	
	m_dynamicsWorld->getSolverInfo().m_numIterations = 8;
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

	// threading locks
	omp_init_lock(&my_lock1);
// 	omp_init_lock(&my_lock2);
}

void WorldB::init()
{
	makeFloor();

	if ( settings->getCVar("autoload") )
		loadAllCritters();
	if ( settings->getCVar("autoloadlastsaved") )
		loadAllLastSavedCritters();
}

void WorldB::castMouseRay()
{
// 	cerr << "casting" << endl;
	mouseRay = raycast->cast( camera.position.getOrigin(), mouseRayTo );

	mouseRayHit = false;
	if ( mouseRay.hit )
	{
// 		if ( !( mouseRay.hitBody->isStaticObject() || mouseRay.hitBody->isKinematicObject() ) )
// 		{
			Entity* e = static_cast<Entity*>(mouseRay.hitBody->getUserPointer());
			if ( e->type == 1 || e->type == 0 )
			{
				mouseRayHit = true;
				mouseRayHitEntity = e;
			}
// 		}
	}
}

void WorldB::calcMouseDirection()
{
// 	cerr << "updating mouserayto" << endl;
	mouseRayTo = camera.getScreenDirection(*mousex, *mousey);
}

void WorldB::moveInMouseDirection(bool towards)
{
// 	cerr << "updating mouserayto" << endl;
	if ( towards )
		camera.moveTowards(mouseRayTo.normalized());
	else
		camera.moveAwayFrom(mouseRayTo.normalized());
}

void WorldB::pickBody(const int& x, const int& y)
{
	if ( mouseRayHit )
	{
		if ( mouseRayHitEntity->type == 0 || mouseRayHitEntity->type == 1 )
		{
			btRigidBody* b = static_cast<btRigidBody*>(mouseRay.hitBody);

			// if critter, and it's the head's ghostobject we touch, overwrite with head's body
			if ( mouseRayHitEntity->type == 0 )
			{
				btCollisionObject* co = static_cast<btCollisionObject*>(mouseRay.hitBody);
				CritterB* c = static_cast<CritterB*>(mouseRayHitEntity);
				if ( co == c->body.mouths[0]->ghostObject )
					b = c->body.mouths[0]->body;
			}
			
			mousepicker->attach( b, mouseRay.hitPosition, camera.position.getOrigin(), mouseRayTo );
			mousepicker->pickedBool = &mouseRayHitEntity->isPicked;
			*mousepicker->pickedBool = true;
		}
	}
}

void WorldB::selectBody(const int& x, const int& y)
{
	if ( mouseRayHit )
		if ( mouseRayHitEntity->type == 0 )
			critterselection->registerCritter(static_cast<CritterB*>(mouseRayHitEntity));
}

void WorldB::movePickedBodyTo()
{
	if ( mousepicker->active )
		mousepicker->moveTo( camera.position.getOrigin(), mouseRayTo );
}

void WorldB::movePickedBodyFrom()
{
	if ( mousepicker->active )
		mousepicker->moveFrom( camera.position.getOrigin() );
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

	// Autoexchange Critters?
		autoexchangeCritters();

	// Autoinsert Critters?
		autoinsertCritters();

	  if ( *critter_raycastvision == 0 )
	  {
		  renderVision();
		  grabVision();
	  }

	// do a bullet step
		m_dynamicsWorld->stepSimulation(0.016667f, 0, 0.016667f);
// 		m_dynamicsWorld->stepSimulation(0.016667f);
// 		m_dynamicsWorld->stepSimulation(Timer::Instance()->bullet_ms / 1000.f);
// cerr << Timer::Instance()->bullet_ms << " : " << Timer::Instance()->bullet_ms / 1000.f << endl;

	// process all critters
	int lmax = (int)critters.size();
// 	int i;
	CritterB* c;
	float freeEnergyc = 0.0f;

	omp_set_num_threads( *threads );
	#pragma omp parallel for ordered shared(freeEnergyc, lmax) private(c) // ordered 
	for( int i=0; i < lmax; i++)
	{
// 			omp_set_lock(&my_lock1);
				c = critters[i];
// 			omp_unset_lock(&my_lock1);
			
			omp_set_lock(&my_lock1);
// 			#pragma omp critical
				checkCollisions(  c );
			omp_unset_lock(&my_lock1);

			// process
// 			omp_set_lock(&my_lock1);
				c->process();
// 			omp_unset_lock(&my_lock1);

			// record critter used energy
// 			omp_set_lock(&my_lock1);
				freeEnergyc += c->energyUsed;
// 			omp_unset_lock(&my_lock1);

			// process Output Neurons
// 			omp_set_lock(&my_lock1);
				eat(c);
// 			omp_unset_lock(&my_lock1);

			// procreation if procreation energy trigger is hit
			omp_set_lock(&my_lock1);
// 			#pragma omp critical
				procreate(c);
			omp_unset_lock(&my_lock1);
// 		}
	}

	freeEnergy += freeEnergyc;
}

void WorldB::childPositionOffset(btVector3* v)
{
	v->setY(insertHight);
}

void WorldB::procreate( CritterB* c )
{
	if ( c->procreate && c->canProcreate )
	{
		bool brainmutant = false;
		bool bodymutant = false;
		if ( randgen->Instance()->get(1,100) <= *brain_mutationrate )
			brainmutant = true;

		if ( randgen->Instance()->get(1,100) <= *body_mutationrate )
			bodymutant = true;

		btVector3 np = c->body.bodyparts[0]->myMotionState->m_graphicsWorldTrans.getOrigin();

		// position offset
		childPositionOffset(&np);
// 		np.setY(insertHight);


// 		if ( np.getX() > *worldsizeX/2 )
// 			np.setX(np.getX()-1.0f);
// 		else
// 			np.setX(np.getX()+1.0f);

		CritterB *nc = new CritterB(*c, currentCritterID++, np, brainmutant, bodymutant);
		//CritterB *nc = new CritterB(*c, currentCritterID++, findPosition(), mutant);

		// display message of birth
			stringstream buf;
			buf << setw(4) << c->critterID << " : " << setw(4) << nc->critterID;
			buf << " ad: " << setw(4) << nc->genotype->adamdist;
			buf << " n: " << setw(4) << nc->brain.totalNeurons << " s: " << setw(5) << nc->brain.totalSynapses;

			if ( brainmutant || bodymutant )
			{
				buf << " ";
				if ( brainmutant ) buf << "brain";
				if ( brainmutant && bodymutant ) buf << "+";
				if ( bodymutant ) buf << "body";
				buf << " mutant";
			}

			Textverbosemessage::Instance()->addBirth(buf);
			if (*headless)
				cerr << buf.str()<< endl;

		// split energies in half
			nc->energyLevel = c->energyLevel/2.0f;
			c->energyLevel -= nc->energyLevel;

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
			Food* f = static_cast<Food*>(c->touchedEntity);
			float eaten = *critter_maxenergy / 100.0f;
			if ( c->energyLevel + eaten > *critter_maxenergy )
				eaten -= (c->energyLevel + eaten) - *critter_maxenergy;
			if ( f->energyLevel - eaten < 0 )
				eaten = f->energyLevel;

			c->energyLevel += eaten;
			f->energyLevel -= eaten;
		}
		else if ( c->touchingCritter && *critter_enableomnivores )
		{
			CritterB* ct = static_cast<CritterB*>(c->touchedEntity);
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
		
		// reduce energy
		if ( *killhalf_decrenergypct > 0 )
		{
			float dec_amount = ((*food_maxenergy * *energy) - *food_maxenergy) / *food_maxenergy;
			if ( dec_amount >= 0.0f )
			{
				int dec = (dec_amount / 100) * *killhalf_decrenergypct;
				settings->setCVar("energy", *energy-dec );
				//*energy -= dec;
				freeEnergy -= dec * *food_maxenergy;
			}
		}

		// increase worldsizes
		if ( *killhalf_incrworldsizeX > 0 )
		{
			settings->increaseCVar("worldsizeX", *killhalf_incrworldsizeX);
			makeFloor();
		}
		if ( *killhalf_incrworldsizeY > 0 )
		{
			settings->increaseCVar("worldsizeY", *killhalf_incrworldsizeY);
			makeFloor();
		}
		
		// decrease critter_maxlifetime
		if ( *killhalf_decrmaxlifetimepct > 0 )
		{
			int dec = (*critter_maxlifetime / 100) * *killhalf_decrmaxlifetimepct;
			settings->setCVar("critter_maxlifetime", *critter_maxlifetime-dec );
		}
	}
}

void WorldB::autoinsertCritters()
{
	// insert critter if < minimum
	if ( critters.size() < *mincritters )
		insertCritter();

	// insert critter if insertcritterevery is reached
	if ( *insertcritterevery > 0 )
	{
		if ( insertCritterCounter >= *insertcritterevery )
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

void WorldB::autoexchangeCritters()
{
	if ( *critter_autoexchangeinterval > 0 )
	{
		autoexchangeCounter += ((float)Timer::Instance()->elapsed/1000);
		if ( autoexchangeCounter > *critter_autoexchangeinterval )
		{
			autoexchangeCounter = 0.0f;

			// determine exchange directory
			stringstream buf;
			buf << dirlayout->savedir << "/exchange";
			string exchangedir = buf.str();
			
			// save or load? :)
			unsigned int mode = randgen->Instance()->get( 0, 1 );
			
			// always load if critters == 0
			if ( critters.size() == 0 || mode )
			{
				vector<string> files;
				dirH.listContentsFull(exchangedir, files);

				// FIXME same routine as load all critters
				for ( unsigned int i = 0; i < files.size(); i++ )
				{
					if ( parseH->Instance()->endMatches( ".cr", files[i] ) )
					{
						stringstream buf;
						
						buf << "loading " << files[i];
						if ( !*headless )
						{
							Logbuffer::Instance()->add(buf);
						}

						string content;
						fileH.open( files[i], content ); 
						fileH.rm( files[i] );

						CritterB *c = new CritterB(content, m_dynamicsWorld, findPosition(), retina);

						if ( !c->loadError)
						{
							critters.push_back( c );

							c->critterID = currentCritterID++;
							c->calcFramePos(critters.size()-1);

							// start energy
							freeEnergy -= c->energyLevel;
						}
						else
							delete c;
					}
				}
				stringstream buf;
				buf << "Loaded critters from " << exchangedir;
				if ( !*headless )
				{
					Logbuffer::Instance()->add(buf);
				}
				else
					cerr << buf.str()<< endl;
			}
			else
			{
				// pick one to save
				unsigned int savec = randgen->Instance()->get( 0, critters.size()-1 );

				buf << "/" << time(0) << ".cr";
				string filename = buf.str();

				// makde dirs
				if ( !dirH.exists(dirlayout->savedir) )		dirH.make(dirlayout->savedir);
				if ( !dirH.exists(exchangedir) )	dirH.make(exchangedir);

				// save critter
				fileH.save(filename, critters[savec]->genotype->saveGenotype());

				//cerr << endl << "Saved critters to " << subsavedir << endl << endl;
				stringstream buf2;
				buf2 << "Autoexchange: Saved critter to " << filename;
				if ( !*headless )
					Logbuffer::Instance()->add(buf2);
				else
					cerr << buf2.str()<< endl;
			}
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
				buf << setw(4) << critters[i]->critterID << " got eaten";
			else
				buf << setw(4) << critters[i]->critterID << " starved";
			Textverbosemessage::Instance()->addDeath(buf);
			if (*headless)
				cerr << buf.str()<< endl;

			removeCritter(i);
			i--;
		}
		// die of old age
		else if ( critters[i]->totalFrames > *critter_maxlifetime )
		{
			stringstream buf;
			buf << setw(4) << critters[i]->critterID << " died of age";
			Textverbosemessage::Instance()->addDeath(buf);
			if (*headless)
				cerr << buf.str()<< endl;

			removeCritter(i);
			i--;
		}
		// die if y < 100
		else
		{
			btVector3 pos = critters[i]->body.bodyparts[0]->myMotionState->m_graphicsWorldTrans.getOrigin();
			
			if ( pos.getY() < -100.0f )
			{
				stringstream buf;
				buf << setw(4) << critters[i]->critterID << " fell in the pit";
				Textverbosemessage::Instance()->addDeath(buf);
				if (*headless)
					cerr << buf.str()<< endl;

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
			btVector3 pos = food[i]->body.bodyparts[0]->myMotionState->m_graphicsWorldTrans.getOrigin();

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
// 	settings->info_totalNeurons = 0;
// 	settings->info_totalSynapses = 0;
// 	settings->info_totalAdamDistance = 0;
// 	settings->info_totalBodyparts = 0;
// 	settings->info_totalWeight = 0;

// 	settings->info_critters = critters.size();
// 	settings->info_food = food.size();

// 	int info_totalNeurons = 0;
// 	int info_totalSynapses = 0;
// 	int info_totalAdamDistance = 0;
// 	int info_totalBodyparts = 0;
// 	int info_totalWeight = 0;
// 	CritterB* c;

// #pragma omp parallel for shared (info_totalNeurons, info_totalSynapses, info_totalAdamDistance, info_totalBodyparts, info_totalWeight, crittersize) private(i, c)
// 	for( unsigned int i=0; i < critters.size(); i++ )
// 	{
// 		c = critters[i];
// 		info_totalNeurons		+= c->brain.totalNeurons;
// 		info_totalSynapses		+= c->brain.totalSynapses;
// 		info_totalAdamDistance		+= c->genotype->adamdist;
// 		info_totalBodyparts		+= c->body.bodyparts.size();
// 		info_totalWeight		+= c->body.totalWeight;
// 	}
// 
// 	settings->info_totalNeurons		+= info_totalNeurons;
// 	settings->info_totalSynapses		+= info_totalSynapses;
// 	settings->info_totalAdamDistance	+= info_totalAdamDistance;
// 	settings->info_totalBodyparts		+= info_totalBodyparts;
// 	settings->info_totalWeight		+= info_totalWeight;

	statsBuffer->add( critters, food );
}

void WorldB::checkCollisions( CritterB* c )
{
	// set inputs to false and recheck
		c->touchingFood = false;
		c->touchingCritter = false;

	if ( c->body.mouths.size() > 0 )
	{
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

			for ( int j = 0; j < manifoldArray.size(); j++ )
			{
				btPersistentManifold* manifold = manifoldArray[j];
				
				btCollisionObject* object1 = static_cast<btCollisionObject*>(manifold->getBody0());
				btCollisionObject* object2 = static_cast<btCollisionObject*>(manifold->getBody1());

				if ( object1->getUserPointer() == c && object2->getUserPointer() == c )
					continue;

				for ( int p = 0; p < manifold->getNumContacts(); p++ )
				{
					const btManifoldPoint &pt = manifold->getContactPoint(p);
					if ( pt.getDistance() < 0.0f )
					{
						void* Collidingobject;
						if ( object1->getUserPointer() != c && object1->getUserPointer() != 0 )
							Collidingobject = object1->getUserPointer();
						else if ( object2->getUserPointer() != c && object2->getUserPointer() != 0 )
							Collidingobject = object2->getUserPointer();
						else 
							continue;

						// Touching Food
						Entity* e = static_cast<Entity*>(Collidingobject);
						if ( e->type == 1 )
						{
// 							cerr << "touches food" << endl;
							c->touchingFood = true;
							c->touchedEntity = e;
							return;
						}
						// Touching Critter
						else if ( e->type == 0 )
						{
// 							cerr << "touches critter" << endl;
							c->touchingCritter = true;
							c->touchedEntity = e;
							return;
						}

/*						// Touching Food
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
						}*/
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
		Food *f = new Food();
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
	return btVector3( (float)randgen->Instance()->get( 0, 100**worldsizeX ) / 100, insertHight, (float)randgen->Instance()->get( 0, 100**worldsizeY ) / 100 );
}

void WorldB::removeCritter(unsigned int cid)
{
	freeEnergy += critters[cid]->energyLevel;

	if ( critters[cid]->isPicked )
		mousepicker->detach();
	
	critterselection->unregisterCritterID(critters[cid]->critterID);
	critterselection->deselectCritter(critters[cid]->critterID);

	delete critters[cid];
	critters.erase(critters.begin()+cid);

	// update higher retina frame positions
	int c;
	omp_set_num_threads( *threads );
// 	#pragma omp parallel for private(c)
	for ( c = cid; c < (int)critters.size(); c++ )
		critters[c]->calcFramePos(c);
}

void WorldB::killHalfOfCritters()
{
	for ( unsigned int c = 0; c < critters.size(); c++ )
		removeCritter(c);

/*	// kill oldest
	if ( critters.size() > 0 )
	{
		unsigned int half = (critters.size()+1)/2;
		for ( unsigned int c = 0; c < half; c++ )
			removeCritter(0);
	}*/
}

void WorldB::renderVision()
{
	// render critter vision
	if ( !*critter_raycastvision )
		for( unsigned int i=0; i < critters.size(); i++)
			if ( critters[i]->body.mouths.size() > 0 )
			{
				critters[i]->place();
// 				drawWithinCritterSight(critters[i]);
				drawWithinCritterSight( i );
			}
}

void WorldB::grabVision()
{
	// Read pixels into retina
	if ( !*critter_raycastvision && critters.size() > 0 )
	{
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
}

void WorldB::drawWithoutFaces()
{
	drawfloor();

	for( unsigned int i=0; i < critters.size(); i++)
		critters[i]->draw(false);

	for( unsigned int i=0; i < food.size(); i++)
		food[i]->draw();
}


void WorldB::drawWithGrid()
{
	drawfloor();

	for( unsigned int i=0; i < critters.size(); i++)
		critters[i]->draw(true);

	for( unsigned int i=0; i < food.size(); i++)
		food[i]->draw();

// 	m_dynamicsWorld->debugDrawWorld();
}

void WorldB::drawfloor()
{
	for( unsigned int i=0; i < walls.size(); i++)
		walls[i]->draw();
}

void WorldB::drawShadow(btScalar* m,const btVector3& extrusion,const btCollisionShape* shape,const btVector3& worldBoundsMin,const btVector3& worldBoundsMax)
{
	glPushMatrix(); 
	glMultMatrixf(m);
	if(shape->getShapeType() == UNIFORM_SCALING_SHAPE_PROXYTYPE)
	{
		const btUniformScalingShape* scalingShape = static_cast<const btUniformScalingShape*>(shape);
		const btConvexShape* convexShape = scalingShape->getChildShape();
		float	scalingFactor = (float)scalingShape->getUniformScalingFactor();
		btScalar tmpScaling[4][4]={	{scalingFactor,0,0,0},
		{0,scalingFactor,0,0},
		{0,0,scalingFactor,0},
		{0,0,0,1}};
		drawShadow((btScalar*)tmpScaling,extrusion,convexShape,worldBoundsMin,worldBoundsMax);
		glPopMatrix();
		return;
	}
	else if(shape->getShapeType()==COMPOUND_SHAPE_PROXYTYPE)
	{
		const btCompoundShape* compoundShape = static_cast<const btCompoundShape*>(shape);
		for (int i=compoundShape->getNumChildShapes()-1;i>=0;i--)
		{
			btTransform childTrans = compoundShape->getChildTransform(i);
			const btCollisionShape* colShape = compoundShape->getChildShape(i);
			btScalar childMat[16];
			childTrans.getOpenGLMatrix(childMat);
			drawShadow(childMat,extrusion*childTrans.getBasis(),colShape,worldBoundsMin,worldBoundsMax);
		}
	}

	glPopMatrix();

}

void WorldB::drawWithinCritterSight(CritterB *c)
{
	if ( c->body.mouths.size() > 0 )
	{
		btVector3 cposi = c->body.mouths[0]->myMotionState->m_graphicsWorldTrans.getOrigin();

		// draw everything in it's sight
		float sightrange = (float)*critter_sightrange/10;

		drawfloor();

		for( unsigned int i=0; i < food.size(); i++)
		{
			Food *f = food[i];
			if ( cposi.distance( f->myMotionState->m_graphicsWorldTrans.getOrigin() ) < sightrange )
				f->draw();
		}

		for( unsigned int j=0; j < critters.size(); j++)
		{
			CritterB *f = critters[j];
			for( unsigned int b=0; b < f->body.bodyparts.size(); b++)
			{
				if ( cposi.distance( f->body.bodyparts[b]->myMotionState->m_graphicsWorldTrans.getOrigin() ) < sightrange )
				{
					f->body.bodyparts[b]->myMotionState->m_graphicsWorldTrans.getOpenGLMatrix(drawposition);
					glPushMatrix(); 
					glMultMatrixf(drawposition);

							glColor4f( f->genotype->bodyArch->color.r, f->genotype->bodyArch->color.g, f->genotype->bodyArch->color.b, f->genotype->bodyArch->color.a );

							btVector3 halfExtent = static_cast<const btBoxShape*>(f->body.bodyparts[b]->shape)->getHalfExtentsWithMargin();
							glScaled(halfExtent[0], halfExtent[1], halfExtent[2]);

							Displaylists::Instance()->call(0);

					glPopMatrix();
				}
			}
			if ( c->critterID != f->critterID )
			{
				for( unsigned int b=0; b < f->body.mouths.size(); b++)
				{
					if ( cposi.distance( f->body.mouths[b]->ghostObject->getWorldTransform().getOrigin() ) < sightrange )
					{
						f->body.mouths[b]->ghostObject->getWorldTransform().getOpenGLMatrix(drawposition);
						
						glPushMatrix(); 
						glMultMatrixf(drawposition);

								glColor4f( 1.0f, 0.0f, 0.0f, 0.0f );

								btVector3 halfExtent = static_cast<const btBoxShape*>(f->body.mouths[b]->shape)->getHalfExtentsWithMargin();
								glScaled(halfExtent[0], halfExtent[1], halfExtent[2]);

								Displaylists::Instance()->call(1);

						glPopMatrix();
					}
				}
			}
		}
	}
}

// same as before, but with exponential optimisation
void WorldB::drawWithinCritterSight(unsigned int cid)
{
	CritterB *c = critters[cid];

	if ( c->body.mouths.size() > 0 )
	{
// 		cerr << endl << "run " << cid << endl;
		btVector3 cposi = c->body.mouths[0]->myMotionState->m_graphicsWorldTrans.getOrigin();

		// draw everything in it's sight
		float sightrange = (float)*critter_sightrange/10;

		drawfloor();

		for( unsigned int i=0; i < food.size(); i++)
		{
			Food *f = food[i];
			if ( cposi.distance( f->myMotionState->m_graphicsWorldTrans.getOrigin() ) < sightrange )
				f->draw();
		}
// 		cerr << "prerecorded " << c->crittersWithinRange.size() <<  endl;

		// first process prechecked crittersWithinRange vector
		for( unsigned int p=0; p < c->crittersWithinRange.size(); p++)
		{
// 			cerr << " drawing " << c->crittersWithinRange[p] << endl;
			CritterB *f = critters[ c->crittersWithinRange[p] ];

			for( unsigned int b=0; b < f->body.bodyparts.size(); b++)
			{
				f->body.bodyparts[b]->myMotionState->m_graphicsWorldTrans.getOpenGLMatrix(drawposition);
				glPushMatrix(); 
				glMultMatrixf(drawposition);

						glColor4f( f->genotype->bodyArch->color.r, f->genotype->bodyArch->color.g, f->genotype->bodyArch->color.b, f->genotype->bodyArch->color.a );

						btVector3 halfExtent = static_cast<const btBoxShape*>(f->body.bodyparts[b]->shape)->getHalfExtentsWithMargin();
						glScaled(halfExtent[0], halfExtent[1], halfExtent[2]);

						Displaylists::Instance()->call(0);

				glPopMatrix();
			}
			for( unsigned int j=0; j < f->body.mouths.size(); j++)
			{
				f->body.mouths[j]->ghostObject->getWorldTransform().getOpenGLMatrix(drawposition);
				
				glPushMatrix(); 
				glMultMatrixf(drawposition);

						glColor4f( 1.0f, 0.0f, 0.0f, 0.0f );

						btVector3 halfExtent = static_cast<const btBoxShape*>(f->body.mouths[j]->shape)->getHalfExtentsWithMargin();
						glScaled(halfExtent[0], halfExtent[1], halfExtent[2]);

						Displaylists::Instance()->call(1);

				glPopMatrix();
			}
			
		}
		// clear crittersWithinRange vector
		c->crittersWithinRange.clear();

// 		cerr << "not recorded " << endl;
		// now start from current critter to last, record new checks for later critters
		for( unsigned int j=cid; j < critters.size(); j++)
		{
// 			cerr << " checking distance of " << j << endl;
			CritterB *f = critters[j];
			
			// if the first head is within range, draw critters bodyparts and if not same critter, draw head.
			if ( c->critterID == f->critterID || cposi.distance( f->body.mouths[0]->ghostObject->getWorldTransform().getOrigin() ) < sightrange )
			{
				//draw bodies if within range
				for( unsigned int b=0; b < f->body.bodyparts.size(); b++)
				{
					f->body.bodyparts[b]->myMotionState->m_graphicsWorldTrans.getOpenGLMatrix(drawposition);
					
					glPushMatrix(); 
					glMultMatrixf(drawposition);

							glColor4f( f->genotype->bodyArch->color.r, f->genotype->bodyArch->color.g, f->genotype->bodyArch->color.b, f->genotype->bodyArch->color.a );

							btVector3 halfExtent = static_cast<const btBoxShape*>(f->body.bodyparts[b]->shape)->getHalfExtentsWithMargin();
							glScaled(halfExtent[0], halfExtent[1], halfExtent[2]);

							Displaylists::Instance()->call(0);

					glPopMatrix();
				}
				//draw heads if within range, and not itself
				if ( c->critterID != f->critterID )
				{
					// record for future distance checks
					f->crittersWithinRange.push_back(cid);
// 					cerr << "recording " << cid << " in " << j << endl;
					
					for( unsigned int b=0; b < f->body.mouths.size(); b++)
					{
						f->body.mouths[b]->ghostObject->getWorldTransform().getOpenGLMatrix(drawposition);
						
						glPushMatrix(); 
						glMultMatrixf(drawposition);

								glColor4f( 1.0f, 0.0f, 0.0f, 0.0f );

								btVector3 halfExtent = static_cast<const btBoxShape*>(f->body.mouths[b]->shape)->getHalfExtentsWithMargin();
								glScaled(halfExtent[0], halfExtent[1], halfExtent[2]);

								Displaylists::Instance()->call(1);

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
	dirH.listContentsFull(dirlayout->loaddir, files);

	for ( unsigned int i = 0; i < files.size(); i++ )
	{
		if ( parseH->Instance()->endMatches( ".cr", files[i] ) )
		{
			stringstream buf;
			buf << "loading " << files[i];
			Logbuffer::Instance()->add(buf);

			string content;
			fileH.open( files[i], content ); 

			CritterB *c = new CritterB(content, m_dynamicsWorld, findPosition(), retina);

			if ( !c->loadError)
			{
				critters.push_back( c );

				c->critterID = currentCritterID++;
				c->calcFramePos(critters.size()-1);

				// start energy
				freeEnergy -= c->energyLevel;
			}
			else
				delete c;
		}
	}
	stringstream buf;
	buf << "Loaded critters from " << dirlayout->loaddir;
	Logbuffer::Instance()->add(buf);
	//cerr << endl << "Loaded critters from " << loaddir << endl << endl;
}

void WorldB::loadAllLastSavedCritters() // FIXME overlap with previous function
{
cerr << "loading" << endl;
	vector<string> files;
	
	string filen = dirlayout->progdir;
	filen.append("/lastsaved");
	
	if ( fileH.exists(filen) )
	{

		string lastsaveddir;
		fileH.open( filen, lastsaveddir ); 
		
		lastsaveddir = lastsaveddir.substr(0, lastsaveddir.length() - 1);
		
	// 	lastsaveddir.append("/");
	cerr << lastsaveddir << endl;

		dirH.listContentsFull(lastsaveddir, files);

	cerr << "found file: " << files.size() << endl;
		for ( unsigned int i = 0; i < files.size(); i++ )
		{
			if ( parseH->Instance()->endMatches( ".cr", files[i] ) )
			{
				stringstream buf;
				buf << "loading " << files[i];
				Logbuffer::Instance()->add(buf);

				string content;
				fileH.open( files[i], content ); 

				CritterB *c = new CritterB(content, m_dynamicsWorld, findPosition(), retina);

				if ( !c->loadError)
				{
					critters.push_back( c );

					c->critterID = currentCritterID++;
					c->calcFramePos(critters.size()-1);

					// start energy
					freeEnergy -= c->energyLevel;
				}
				else
					delete c;
			}
		}
		stringstream buf;
		buf << "Loaded critters from " << lastsaveddir;
		Logbuffer::Instance()->add(buf);
		//cerr << endl << "Loaded critters from " << loaddir << endl << endl;
	}
}

void WorldB::saveAllCritters()
{
	// determine save directory
	stringstream buf;
	buf << dirlayout->savedir << "/" << settings->profileName;
	string subprofiledir = buf.str();
	
	buf << "/" << time(0);
	string subsavedir = buf.str();

	// make dirs
	if ( !dirH.exists(dirlayout->savedir) )	dirH.make(dirlayout->savedir);
	if ( !dirH.exists(subprofiledir) )	dirH.make(subprofiledir);
	if ( !dirH.exists(subsavedir) )		dirH.make(subsavedir);

	for ( unsigned int i = 0; i < critters.size(); i++ )
	{
		// determine filename
		stringstream filename;
		filename << subsavedir << "/" << "critter" << i << ".cr";
	
		// save critters
		fileH.save(filename.str(), critters[i]->genotype->saveGenotype());
	}

	// save lastsaved file
	stringstream lastsaved;
	lastsaved << dirlayout->progdir << "/" << "lastsaved";
	fileH.save( lastsaved.str(), subsavedir );
	cerr << "saved " << lastsaved.str() << " with " << subsavedir << endl;

 	//cerr << endl << "Saved critters to " << subsavedir << endl << endl;
	stringstream buf2;
	buf2 << "Saved critters to " << subsavedir;
	Logbuffer::Instance()->add(buf2);

}

void WorldB::resetCamera()
{
	unsigned int biggest = *worldsizeX;
	if ( *worldsizeY > biggest )
		biggest = 1.4f**worldsizeY;

	camera.position.setOrigin( btVector3( 0.5f**worldsizeX, 1.3f*biggest, 0.5f**worldsizeY) );
// 	camera.position.setRotation(btQuaternion(btVector3(1, 0, 0), btScalar(90)));
	camera.position.getBasis().setEulerZYX( -1.5707f, 0.0f, 0.0f ); // 1.5707f  (float)*energy/10


// 	camera.position = btVector3( -0.5f**worldsizeX, -1.3f*biggest, -0.5f**worldsizeY);
// 	camera.rotation = Vector3f( 90.0f,  0.0f, 0.0f);
}

// selected critter actions
int WorldB::findSelectedCritterID()
{
	for ( unsigned int i=0; i < critters.size(); i++ )
		if ( critters[i]->critterID == critterselection->selectedCritter->critterID )
			return i;
	return -1;
}

int WorldB::findCritterID(unsigned int cid)
{
	for ( unsigned int i=0; i < critters.size(); i++ )
		if ( critters[i]->critterID == cid )
			return i;
	return -1;
}

void WorldB::removeSelectedCritter()
{
	removeCritter(findSelectedCritterID());
}

void WorldB::removeAllSelectedCritters()
{
	while ( critterselection->clist.size() > 0 )
		removeCritter( findCritterID(critterselection->clist[0]->critterID) );
}

void WorldB::duplicateCritter(unsigned int cid, bool brainmutant, bool bodymutant)
{
	btVector3 np = critters[cid]->body.bodyparts[0]->myMotionState->m_graphicsWorldTrans.getOrigin();

	// position offset
	childPositionOffset(&np);

	CritterB *nc = new CritterB(*critters[cid], currentCritterID++, np, brainmutant, bodymutant);

	// duplicate energy levels
	nc->energyLevel = *critter_startenergy;
	freeEnergy -= nc->energyLevel;

	critters.push_back( nc );
	nc->calcFramePos(critters.size()-1);
}

void WorldB::duplicateSelectedCritter()
{
	duplicateCritter( findSelectedCritterID(), false, false );
}
void WorldB::spawnBrainMutantSelectedCritter()
{
	duplicateCritter( findSelectedCritterID(), true, false );
}
void WorldB::spawnBodyMutantSelectedCritter()
{
	duplicateCritter( findSelectedCritterID(), false, true );
}
void WorldB::spawnBrainBodyMutantSelectedCritter()
{
	duplicateCritter( findSelectedCritterID(), true, true );
}

void WorldB::feedSelectedCritter()
{
	CritterB* c = critters[findSelectedCritterID()];
	if ( c->energyLevel < *critter_startenergy )
	{
		float max_currentDiff = (float)*critter_startenergy - c->energyLevel;
		c->energyLevel += max_currentDiff;
		freeEnergy -= max_currentDiff;
	}
}

void WorldB::resetageSelectedCritter()
{
	critters[findSelectedCritterID()]->totalFrames = 0;
}

void WorldB::duplicateAllSelectedCritters()
{
	for ( unsigned int i=0; i < critterselection->clist.size(); i ++ )
		duplicateCritter( findCritterID(critterselection->clist[i]->critterID), false, false );
}
void WorldB::spawnBrainMutantAllSelectedCritters()
{
	for ( unsigned int i=0; i < critterselection->clist.size(); i ++ )
		duplicateCritter( findCritterID(critterselection->clist[i]->critterID), true, false );
}
void WorldB::spawnBodyMutantAllSelectedCritters()
{
	for ( unsigned int i=0; i < critterselection->clist.size(); i ++ )
		duplicateCritter( findCritterID(critterselection->clist[i]->critterID), false, true );
}
void WorldB::spawnBrainBodyMutantAllSelectedCritters()
{
	for ( unsigned int i=0; i < critterselection->clist.size(); i ++ )
		duplicateCritter( findCritterID(critterselection->clist[i]->critterID), true, true );
}



void WorldB::makeFloor()
{
	makeDefaultFloor();
}

void WorldB::makeDefaultFloor()
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
		btVector3 position( *worldsizeX/2.0f, -WallHalfWidth, *worldsizeY/2.0f );
		Wall* w = new Wall( *worldsizeX, WallWidth, *worldsizeY, position, m_dynamicsWorld );
		w->color.r = 0.30f; w->color.g = 0.20f; w->color.b = 0.10f;
		walls.push_back(w);
	
	if ( settings->getCVar("worldwalls") )
	{
		// Left Wall
			position = btVector3 ( 0.0f-WallHalfWidth, WallHalfHeight-WallWidth, *worldsizeY/2.0f );
			w = new Wall( WallWidth, WallHeight, *worldsizeY, position, m_dynamicsWorld );
			w->color.r = 0.34f; w->color.g = 0.25f; w->color.b = 0.11f;
			walls.push_back(w);
		// Right Wall
			position = btVector3 ( *worldsizeX+WallHalfWidth, WallHalfHeight-WallWidth, *worldsizeY/2.0f );
			w = new Wall( WallWidth, WallHeight, *worldsizeY, position, m_dynamicsWorld );
			w->color.r = 0.34f; w->color.g = 0.25f; w->color.b = 0.11f;
			walls.push_back(w);
		// Top Wall
			position = btVector3 ( *worldsizeX/2.0f, WallHalfHeight-WallWidth, 0.0f-WallHalfWidth );
			w = new Wall( *worldsizeX+(WallWidth*2), WallHeight, WallWidth, position, m_dynamicsWorld );
			w->color.r = 0.34f; w->color.g = 0.25f; w->color.b = 0.11f;
			walls.push_back(w);
		// Bottom Wall
			position = btVector3 ( *worldsizeX/2.0f, WallHalfHeight-WallWidth, *worldsizeY+WallHalfWidth );
			w = new Wall( *worldsizeX+(WallWidth*2), WallHeight, WallWidth, position, m_dynamicsWorld );
			w->color.r = 0.34f; w->color.g = 0.25f; w->color.b = 0.11f;
			walls.push_back(w);
	}
}

// camera ops
void WorldB::camera_moveup() { camera.moveUp(0.01f); movePickedBodyFrom(); }
void WorldB::camera_movedown() { camera.moveDown(0.01f); movePickedBodyFrom(); }
void WorldB::camera_moveforward() { camera.moveForward(0.01f); movePickedBodyFrom(); }
void WorldB::camera_movebackward() { camera.moveBackward(0.01f); movePickedBodyFrom(); }
void WorldB::camera_moveleft() { camera.moveLeft(0.01f); movePickedBodyFrom(); }
void WorldB::camera_moveright() { camera.moveRight(0.01f); movePickedBodyFrom(); }

void WorldB::camera_lookup() { camera.lookUp(0.001f); calcMouseDirection(); movePickedBodyTo(); }
void WorldB::camera_lookdown() { camera.lookDown(0.001f); calcMouseDirection(); movePickedBodyTo(); }
void WorldB::camera_lookleft() { camera.lookLeft(0.001f); calcMouseDirection(); movePickedBodyTo(); }
void WorldB::camera_lookright() { camera.lookRight(0.001f); calcMouseDirection(); movePickedBodyTo(); }
void WorldB::camera_rollleft() { camera.rollLeft(0.001f); calcMouseDirection(); movePickedBodyTo(); }
void WorldB::camera_rollright() { camera.rollRight(0.001f); calcMouseDirection(); movePickedBodyTo(); }


WorldB::~WorldB()
{
	for ( unsigned int i=0; i < food.size(); i++ )		delete food[i];
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

	omp_destroy_lock(&my_lock1);
// 	omp_destroy_lock(&my_lock2);
}
