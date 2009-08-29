#include <BulletCollision/NarrowPhaseCollision/btConvexCast.h>
#include "worldb.h"
/*extern int gNumClampedCcdMotions;*/
// FIXME PUT C/H IN CRITTER FILENAME
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

	freeEnergy = *food_maxenergy * settings->getCVar("energy");
	settings->freeEnergyInfo = freeEnergy;
		
	currentCritterID	= 0;
	insertCritterCounter	= 0;
	autosaveCounter		= 0.0f;

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

// 	debugDrawer.setDebugMode(btIDebugDraw::DBG_DrawWireframe|btIDebugDraw::DBG_DrawConstraints+btIDebugDraw::DBG_DrawConstraintLimits);
// 	debugDrawer.setDebugMode(btIDebugDraw::DBG_DrawConstraints+btIDebugDraw::DBG_DrawConstraintLimits);
// 	debugDrawer.setDebugMode(btIDebugDraw::DBG_DrawConstraints);
// 	debugDrawer.setDebugMode(btIDebugDraw::DBG_DrawConstraintLimits);
// 	m_dynamicsWorld->setDebugDrawer(&debugDrawer);

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

/*	// clientResetScene
	gNumClampedCcdMotions = 0;
	int numObjects = 0;
	int i;

	if (m_dynamicsWorld)
	{
		numObjects = m_dynamicsWorld->getNumCollisionObjects();
	}

	///create a copy of the array, not a reference!
	btCollisionObjectArray copyArray = m_dynamicsWorld->getCollisionObjectArray();

	for (i=0;i<copyArray.size();i++)
	{
		btRigidBody* body = btRigidBody::upcast(copyArray[i]);
		if (body)
			m_dynamicsWorld->removeRigidBody(body);
	}



	for (i=0;i<numObjects;i++)
	{
		btCollisionObject* colObj = copyArray[i];
		btRigidBody* body = btRigidBody::upcast(colObj);
		if (body)
		{
			if (body->getMotionState())
			{
				btDefaultMotionState* myMotionState = (btDefaultMotionState*)body->getMotionState();
				myMotionState->m_graphicsWorldTrans = myMotionState->m_startWorldTrans;
				body->setCenterOfMassTransform( myMotionState->m_graphicsWorldTrans );
				colObj->setInterpolationWorldTransform( myMotionState->m_startWorldTrans );
				colObj->forceActivationState(ACTIVE_TAG);
				colObj->activate();
				colObj->setDeactivationTime(0);
				//colObj->setActivationState(WANTS_DEACTIVATION);
			}
			//removed cached contact points (this is not necessary if all objects have been removed from the dynamics world)
			m_dynamicsWorld->getBroadphase()->getOverlappingPairCache()->cleanProxyFromPairs(colObj->getBroadphaseHandle(),m_dynamicsWorld->getDispatcher());

			btRigidBody* body = btRigidBody::upcast(colObj);
			if (body && !body->isStaticObject())
			{
				btRigidBody::upcast(colObj)->setLinearVelocity(btVector3(0,0,0));
				btRigidBody::upcast(colObj)->setAngularVelocity(btVector3(0,0,0));
			}
		}

	}

	///reset some internal cached data in the broadphase
	m_dynamicsWorld->getBroadphase()->resetPool(m_dynamicsWorld->getDispatcher());
	m_dynamicsWorld->getConstraintSolver()->reset();
	
	for ( i=0;i<copyArray.size();i++)
	{
		btRigidBody* body = btRigidBody::upcast(copyArray[i]);
		if (body)
			m_dynamicsWorld->addRigidBody(btRigidBody::upcast(copyArray[i]));
	}*/
	
}

// void WorldB::resize(unsigned int X, unsigned int Y)
// {
// 	sizeX = X;
// 	sizeY = Y;
// // 	grid.resize(X, Y, m_dynamicsWorld);
// }

void WorldB::castRay(Vector3f drayFrom, btVector3 direction)
{
/*			unsigned int totalp = walls.size()+food.size();
			for( unsigned int j=0; j < critters.size(); j++)
			{
				for( unsigned int k=0; k < critters[j]->body->bodyparts.size(); k++)
				{
					totalp++;
				}
			}
*/

			btVector3 rayFrom = btVector3( -drayFrom.x, -drayFrom.y, -drayFrom.z );
			btVector3 rayTo = btVector3( direction.getX(), -direction.getY(), -direction.getZ() );

// 			cerr << "origin   : " << rayFrom.getX() << " - " << rayFrom.getY() << " - " << rayFrom.getZ() << endl;
// 			cerr << "direction: " << rayTo.getX() <<   " - " << rayTo.getY() <<   " - " << rayTo.getZ() << endl;

			btCollisionWorld::ClosestRayResultCallback resultCallback(rayFrom,rayTo);
			m_dynamicsWorld->rayTest(rayFrom,rayTo,resultCallback);

			if (resultCallback.hasHit())
			{
// 				cerr << endl << "ray hit something" << endl << endl;
				btRigidBody* body = btRigidBody::upcast(resultCallback.m_collisionObject);
				if (body)
				{
					Food* f = static_cast<Food*>(body->getUserPointer());
					if ( f )
					{
						if ( f->type == 1 )
						{
							cerr << endl << "hit food " << endl << endl;
							f->color[0] = 1.0f;
							f->color[1] = 1.0f;
							f->color[2] = 1.0f;
						}
						else
						{
							CritterB* b = static_cast<CritterB*>(body->getUserPointer());
							if ( b->type == 0 )
							{
								cerr << endl << "hit critter " << endl << endl;
								b->color[0] = 1.0f;
								b->color[1] = 1.0f;
								b->color[2] = 1.0f;
							}
						}
					}
				}
			}
}

void WorldB::process()
{
	// Autosave Critters?
		if ( *critter_autosaveinterval > 0 )
		{
			autosaveCounter += Timer::Instance()->elapsed;
			if ( autosaveCounter > *critter_autosaveinterval )
			{
				autosaveCounter = 0.0f;
				saveAllCritters();
			}
		}

	// kill half?
		if ( critters.size() >= *critter_killhalfat )
		{
			killHalfOfCritters();
			
			// reduce energy :)
			if ( (settings->freeEnergyInfo - *food_maxenergy) / *food_maxenergy >= 0.0f )
			{
				settings->freeEnergyInfo -= *food_maxenergy*5;
				freeEnergy -= *food_maxenergy*5;
			}
		}

	// Remove food
		for( unsigned int i=0; i < food.size(); i++)
		{
			// food was eaten
			if ( food[i]->energyLevel <= 0 )
			{
				freeEnergy += food[i]->energyLevel;
				delete food[i];
				food.erase(food.begin()+i);
				i--;
			}

			// old food, this should remove stuff from corners
			else if ( ++food[i]->totalFrames >= *food_maxlifetime )
			{
				freeEnergy += food[i]->energyLevel;
				delete food[i];
				food.erase(food.begin()+i);
				i--;
			}
		}

	// remove all dead critters
		for( unsigned int i=0; i < critters.size(); i++)
		{
			// see if energy level isn't below 0 -> die, or die of old age
			if ( critters[i]->energyLevel <= 0.0f )
			{
				stringstream buf;
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
		}

// 		btCollisionObjectArray copyArray = m_dynamicsWorld->getCollisionObjectArray();
// 		int numObjects = m_dynamicsWorld->getNumCollisionObjects();
// 		for (int i=0; i < numObjects; i++)
// 		{
// 			btCollisionObject* colObj = copyArray[i];
// 			btRigidBody* body = btRigidBody::upcast(colObj);
// 			if (body)
// 			{
// /*				if (body->getMotionState())
// 				{
// 					btDefaultMotionState* myMotionState = (btDefaultMotionState*)body->getMotionState();
// 					myMotionState->m_graphicsWorldTrans = myMotionState->m_startWorldTrans;
// 					body->setCenterOfMassTransform( myMotionState->m_graphicsWorldTrans );
// 					colObj->setInterpolationWorldTransform( myMotionState->m_startWorldTrans );
// 					colObj->forceActivationState(ACTIVE_TAG);
// 					colObj->activate();
// 					colObj->setDeactivationTime(0);
// 					//colObj->setActivationState(WANTS_DEACTIVATION);
// 				}*/
// 				//removed cached contact points (this is not necessary if all objects have been removed from the dynamics world)
// 				m_dynamicsWorld->getBroadphase()->getOverlappingPairCache()->cleanProxyFromPairs(colObj->getBroadphaseHandle(),m_dynamicsWorld->getDispatcher());
// 
// /*				btRigidBody* body = btRigidBody::upcast(colObj);
// 				if (body && !body->isStaticObject())
// 				{
// 					btRigidBody::upcast(colObj)->setLinearVelocity(btVector3(0,0,0));
// 					btRigidBody::upcast(colObj)->setAngularVelocity(btVector3(0,0,0));
// 				}*/
// 			}
// 		}

	// Autoinsert Food
		while ( freeEnergy >= *food_maxenergy )
		{
			insertRandomFood(1, *food_maxenergy);
			freeEnergy -= *food_maxenergy;
			//cerr << "food: " << food.size() << endl;
		}

	// Autoinsert Critters?
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
	// do a bullet step
		m_dynamicsWorld->stepSimulation(Timer::Instance()->bullet_ms / 1000000.f);

	// render critter vision
	for( unsigned int i=0; i < critters.size(); i++)
	{
		if ( critters[i]->body.mouths.size() > 0 )
		{
			critters[i]->place();
			drawWithinCritterSight(i);
		}
	}

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

// 	settings->info_crittersC = 0;
	settings->info_totalNeurons = 0;
	settings->info_totalSynapses = 0;
	settings->info_totalAdamDistance = 0;

	// process all critters
	unsigned int lmax = critters.size();
	for( unsigned int i=0; i < lmax; i++)
	{
		CritterB *c = critters[i];

		// getAngle test
/* 		if ( i == 0 )
 		{
			float percentAngle = critters[0]->body->constraints[0]->getAngle();
			cerr << percentAngle << endl;
		}*/
		// RayCast Test
// 		if ( 0 == 0 )
// 		{
// 
// 		}
		
		// set inputs to false and recheck
			c->touchingFood = false;
			c->touchingCritter = false;

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
										else
										{
											CritterB* b = static_cast<CritterB*>(Collidingobject);
											if ( b->type == 0 )
											{
												stop = true;
												c->touchingCritter = true;
												c->touchedCritterID = b;
											}
										}
									}
									else
									{
									}
							}
						}
					}
				}
			}

		// process
			c->process();

		// record critter used energy
			freeEnergy += c->energyUsed;

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
				}
				else if ( settings->getCVar("critter_enableherbivores") && c->touchingCritter )
				{
					CritterB* ct = c->touchedCritterID;
					float eaten = *critter_maxenergy / 50.0f;
					if ( c->energyLevel + eaten > *critter_maxenergy )
						eaten -= (c->energyLevel + eaten) - *critter_maxenergy;
					if ( ct->energyLevel - eaten < 0 )
						eaten = ct->energyLevel;

					c->energyLevel += eaten;
					ct->energyLevel -= eaten;
				}
			}

		// procreation if procreation energy trigger is hit
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
				np.setY(1.0f);
				CritterB *nc = new CritterB(*c, currentCritterID++, np, brainmutant, bodymutant);
				//CritterB *nc = new CritterB(*c, currentCritterID++, findPosition(), mutant);

				// display message of birth
					stringstream buf;
					buf << setw(4) << c->critterID << " : " << setw(4) << nc->critterID;
					buf << " ad: " << setw(4) << nc->adamdist;
					buf << " n: " << setw(4) << nc->brain.totalNeurons << " s: " << setw(5) << nc->brain.totalSynapses;
// 							if ( nc->crittertype == 1 )
// 								buf << " carnivore";
// 							else
// 								buf << " herbivore";
					if ( brainmutant ) buf << " brain mutant";
					if ( bodymutant ) buf << " body mutant";
					Textverbosemessage::Instance()->addBirth(buf);

				// split energies in half
					nc->energyLevel = c->energyLevel/2.0f;
					c->energyLevel = nc->energyLevel;

				// reset procreation energy count
					c->procreateTimeCount = 0;

					settings->info_critters++;
					settings->info_totalNeurons += nc->brain.totalNeurons;
					settings->info_totalSynapses += nc->brain.totalSynapses;
					settings->info_totalAdamDistance += nc->adamdist;

					critters.push_back( nc );
					
					nc->calcFramePos(critters.size()-1);
			}

		// move
			c->move();

		// count totals of neurons, synapses and adamdistances
			settings->info_totalNeurons		+= c->brain.totalNeurons;
			settings->info_totalSynapses		+= c->brain.totalSynapses;
			settings->info_totalAdamDistance	+= c->adamdist;

		// move ghostobject to mouth object position
		for ( unsigned int i=0; i < c->body.mouths.size(); i++ )
		{
			c->body.mouths[i]->updateGhostObjectPosition();
		}
	}

	settings->info_critters = critters.size();
	settings->info_food = food.size();

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
	btVector3 pos( (float)randgen->Instance()->get( 0, 100*settings->getCVar("worldsizeX") ) / 100, 1.0f, (float)randgen->Instance()->get( 0, 100*settings->getCVar("worldsizeY") ) / 100 );
// 	pos.x = (float)randgen->Instance()->get( 0, 100*sizeX ) / 100;
// 	pos.y = 1.0;
// 	pos.z = (float)randgen->Instance()->get( 0, 100*sizeY ) / 100;

	return pos;
}

void WorldB::removeCritter(unsigned int cid)
{
	freeEnergy += critters[cid]->energyLevel;

	delete critters[cid];
	critters.erase(critters.begin()+cid);

	// update higher retina frame positions
	for ( unsigned int c = cid; c < critters.size(); c++ )
		critters[c]->calcFramePos(c);
}

void WorldB::killHalfOfCritters()
{
	unsigned int c = 0;
	unsigned int halfc = critters.size()/2;
	while ( c < halfc )
	{
		freeEnergy += critters[0]->energyLevel;

		delete critters[0];
		critters.erase(critters.begin());
		c++;
	}

// 	for ( unsigned int c = 0; c < critters.size(); c++ )
// 	{
// 		freeEnergy += critters[c]->energyLevel;
// 
// 		delete critters[c];
// 		critters.erase(critters.begin()+c);
// 	}

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
		{
			walls[i]->draw();
		}

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
}
