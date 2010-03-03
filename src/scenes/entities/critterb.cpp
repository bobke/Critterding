#include "critterb.h"

void CritterB::initConst()
{
	// settings and pointers
	settings = Settings::Instance();
	genotypes = Genotypes::Instance();
	retinasperrow = settings->getCVarPtr("retinasperrow");
	colormode = settings->getCVarPtr("colormode");
	critter_maxlifetime = settings->getCVarPtr("critter_maxlifetime");
	critter_maxenergy = settings->getCVarPtr("critter_maxenergy");
	critter_sightrange = settings->getCVarPtr("critter_sightrange");
	critter_procinterval = settings->getCVarPtr("critter_procinterval");
	critter_minenergyproc = settings->getCVarPtr("critter_minenergyproc");
	critter_raycastvision = settings->getCVarPtr("critter_raycastvision");

	brain_costhavingneuron = settings->getCVarPtr("brain_costhavingneuron");
	brain_costfiringneuron = settings->getCVarPtr("brain_costfiringneuron");
	brain_costfiringmotorneuron = settings->getCVarPtr("brain_costfiringmotorneuron");
	brain_costhavingsynapse = settings->getCVarPtr("brain_costhavingsynapse");

	type = 0;
	isPicked		= false;

	totalFrames		= 0;
	procreateTimeCount	= 0;

// 	sightrange = settings->critter_sightrange;
// 	colorTrim		= 0.15f;

	eat			= false;
	procreate		= false;

	// raycast
	raycast = new Raycast(btDynWorld);
}

CritterB::CritterB(btDynamicsWorld* btWorld, long unsigned int id, const btVector3& startPos, unsigned char* retinap)
{
	loadError = false;

	// first things first
	btDynWorld						= btWorld;
	retina							= retinap;
	critterID						= id;

	initConst();

	energyLevel						= settings->getCVar("critter_startenergy");

// 	lifetime						= settings->critter_maxlifetime;

	genotype = genotypes->newg( settings );

	// BODY
// 	genotype->bodyArch->buildArch();
	body.wireArch( genotype->bodyArch, (void*)this, btDynWorld, startPos );

	// LINK
	registerBrainInputOutputs();
	
	// BRAIN
// 	genotype->brainzArch->buildArch();
	brain.wireArch( genotype->brainzArch );
}

CritterB::CritterB(CritterB& other, long unsigned int id, const btVector3& startPos, bool brainmutant, bool bodymutant)
{
	loadError = false;

	// first things first
	btDynWorld					= other.btDynWorld;
	retina						= other.retina;
	critterID					= id;

	initConst();

// 	lifetime					= other.lifetime;

	genotype = genotypes->copy(other.genotype, brainmutant, RandGen::Instance()->get(1, settings->getCVar("brain_maxmutations")), bodymutant, RandGen::Instance()->get(1, settings->getCVar("body_maxmutations")));

	body.wireArch( genotype->bodyArch, (void*)this, btDynWorld, startPos );

	// LINK
	registerBrainInputOutputs();

	brain.wireArch( genotype->brainzArch );
}

CritterB::CritterB(string &critterstring, btDynamicsWorld* btWorld, const btVector3& startPos, unsigned char* retinap)
{
	loadError = false;
	// critterID is arranged in world, definite critter insertion is not determined yet

	// first things first
	btDynWorld		= btWorld;
	retina			= retinap;

	initConst();

	energyLevel		= settings->getCVar("critter_startenergy");

	genotype = genotypes->loadGenotype(critterstring);

	if ( genotype->bodyArch->retinasize != settings->getCVar("critter_retinasize"))
	{
		stringstream buf;
		buf << "ERROR: critter retinasize (" << genotype->bodyArch->retinasize << ") doesn't fit world retinasize (" << settings->getCVar("critter_retinasize") << ")";
		Logbuffer::Instance()->add(buf);

		cerr << "!ERROR: critter retinasize (" << genotype->bodyArch->retinasize << ") doesn't fit world retinasize (" << settings->getCVar("critter_retinasize") << ")" << endl;
		loadError = true;
	}
	else
	{
		// BODY
		body.wireArch( genotype->bodyArch, (void*)this, btDynWorld, startPos );

		// LINK
		registerBrainInputOutputs();

		// BRAIN
		brain.wireArch( genotype->brainzArch );
	}
}

void CritterB::registerBrainInputOutputs()
{
// 	cerr << "attaching INPUTS" << endl;
	for ( unsigned int i=0; i < genotype->brainzArch->InputIDs.size(); i++ )
	{
		brain.registerInput( genotype->brainzArch->InputIDs[i] );
	}

// 	cerr << "attaching OUTPUTS" << endl;

	for ( unsigned int i=0; i < body.constraints.size(); i++ )
	{
		for ( unsigned int j=0; j < body.constraints[i]->Inputs.size(); j++ )
		{
			brain.registerOutput( body.constraints[i]->Inputs[j], genotype->brainzArch->OutputIDs[ (i*2)+j ] );
		}
	}

	// eat
		brain.registerOutput( &eat, 100000 );

	// procreate
		brain.registerOutput( &procreate, 100001 );
		
	// debug check
	if ( brain.Outputs.size() != genotype->brainzArch->OutputIDs.size() )
		cerr << "WARNING: brain.Outputs.size() != genotype->brainzArch->OutputIDs.size()" << endl;
}

void CritterB::draw(bool drawFaces)
{
	for( unsigned int j=0; j < body.bodyparts.size(); j++)
	{
		body.bodyparts[j]->myMotionState->m_graphicsWorldTrans.getOpenGLMatrix(position);

		glPushMatrix(); 
		glMultMatrixf(position);

			if ( *colormode == 1 )
				glColor4f( genotype->speciescolor.r, genotype->speciescolor.g, genotype->speciescolor.b, genotype->speciescolor.a );
			else
				glColor4f( genotype->bodyArch->color.r, genotype->bodyArch->color.g, genotype->bodyArch->color.b, genotype->bodyArch->color.a );

				const btBoxShape* boxShape = static_cast<const btBoxShape*>(body.bodyparts[j]->shape);
				btVector3 halfExtent = boxShape->getHalfExtentsWithMargin();
				glScaled(halfExtent[0], halfExtent[1], halfExtent[2]);

				Displaylists::Instance()->call(1);

		glPopMatrix();
	}
	if ( drawFaces )
	{
		for( unsigned int j=0; j < body.mouths.size(); j++)
		{
			body.mouths[j]->ghostObject->getWorldTransform().getOpenGLMatrix(position);
			glPushMatrix(); 
			glMultMatrixf(position);

					glColor4f( 1.0f, 0.0f, 0.0f, 0.0f );

					const btBoxShape* boxShape = static_cast<const btBoxShape*>(body.mouths[j]->shape);
					btVector3 halfExtent = boxShape->getHalfExtentsWithMargin();
					glScaled(halfExtent[0], halfExtent[1], halfExtent[2]);

					Displaylists::Instance()->call(1);

			glPopMatrix();
		}
	}
}

void CritterB::process()
{
	// increase counters
		totalFrames++;
		procreateTimeCount++;

		eaten = false;

	// reset motor bools
		movementsmade	= 0;
// 		eat		= false;
// 		procreate	= false;
// 		carrydrop	= false;

	// SENSORS
		procInputNeurons();

	// INTERS
		brain.process();

	// MOTORS
// 		procOutputNeurons();

	// calc used energy, energyUsed is used in world aswell, don't remove

// 		energyUsed = ( (float)brain.totalNeurons + (float)brain.neuronsFired + (2.0f*(float)motorneuronsfired) + ((float)brain.totalSynapses/10.0f) ) / 200.0f;

 		energyUsed =  brain.totalNeurons	* *brain_costhavingneuron;
 		energyUsed += brain.neuronsFired	* *brain_costfiringneuron;
 		energyUsed += brain.motorneuronsFired	* *brain_costfiringmotorneuron;
 		energyUsed += brain.totalSynapses	* *brain_costhavingsynapse;
		energyUsed = energyUsed / 100000;
// 		cerr << energyUsed << endl;

	// apply energy usage
	energyLevel -= energyUsed;

	// move
		// motorate all constraints
		for ( unsigned int i=0; i < body.constraints.size(); i++ )
			body.constraints[i]->motorate();

	// move ghostobject to mouth object position
		for ( unsigned int i=0; i < body.mouths.size(); i++ )
			body.mouths[i]->updateGhostObjectPosition();
}

void CritterB::procInputNeurons()
{
	// clear all inputs

	brain.clearInputs();

	unsigned int overstep = 0;

	// touching food
		if ( touchingFood )	brain.Inputs[overstep++].output = 1;
		else			brain.Inputs[overstep++].output = 0;

	// touching critter
		if ( touchingCritter )	brain.Inputs[overstep++].output = 1;
		else			brain.Inputs[overstep++].output = 0;

	// can procreate sensor neuron
		canProcreate	= false;
		if ( procreateTimeCount > *critter_procinterval && energyLevel > *critter_minenergyproc )
		{
			brain.Inputs[overstep++].output = 1;
			canProcreate = true;
		}
		else brain.Inputs[overstep++].output = 0;

	// energy neurons
		unsigned int NeuronToFire = (int)((energyLevel / (*critter_maxenergy+1)) * 10) + overstep;
		unsigned int count = 10 + overstep;
		while ( overstep < count )
		{
			if ( overstep <= NeuronToFire )	brain.Inputs[overstep++].output = 1; // !!! <=
			else 				brain.Inputs[overstep++].output = 0;
		}

	// age neurons
		NeuronToFire = (int)(((float)totalFrames / (*critter_maxlifetime+1)) * 10) + overstep;
		count = 10 + overstep;
		while ( overstep < count )
		{
			if ( overstep <= NeuronToFire )	brain.Inputs[overstep++].output = 1; // !!! <=
			else 				brain.Inputs[overstep++].output = 0;
		}

	// Vision
// 		unsigned int vstart = overstep;

		if ( *critter_raycastvision )
			for ( int y = genotype->bodyArch->retinasize-1; y >= 0; y-- )
				for ( unsigned int x = 0; x < genotype->bodyArch->retinasize; x++ )
				{
// 					cerr << "starting" << endl;
					mouseRay = raycast->cast( body.mouths[0]->ghostObject->getWorldTransform().getOrigin(), getScreenDirection(x+1, y) );
// 					cerr << "e1" << endl;
					if ( mouseRay.hit )
					{
						Entity* e = static_cast<Entity*>(mouseRay.hitBody->getUserPointer());
						if ( e->type == 0 )
						{
							CritterB* c = static_cast<CritterB*>(e);
							brain.Inputs[overstep++].output = c->genotype->bodyArch->color.r;
							brain.Inputs[overstep++].output = c->genotype->bodyArch->color.g;
							brain.Inputs[overstep++].output = c->genotype->bodyArch->color.b;
							brain.Inputs[overstep++].output = c->genotype->bodyArch->color.a;
						}
						else
						{
							brain.Inputs[overstep++].output = e->color.r;
							brain.Inputs[overstep++].output = e->color.g;
							brain.Inputs[overstep++].output = e->color.b;
							brain.Inputs[overstep++].output = e->color.a;
						}
					}
					else
					{
						brain.Inputs[overstep++].output = 0.0f;
						brain.Inputs[overstep++].output = 0.0f;
						brain.Inputs[overstep++].output = 0.0f;
						brain.Inputs[overstep++].output = 0.0f;
					}
// 					cerr << "e2" << endl;
				}
		else
			for ( unsigned int h=retinaRowStart; h < retinaRowStart+(genotype->bodyArch->retinasize*retinaRowLength); h += retinaRowLength )
				for ( unsigned int w=h+retinaColumnStart; w < h+retinaColumnStart+((genotype->bodyArch->retinasize)*4); w++ )
					brain.Inputs[overstep++].output = (float)retina[w] / 256.0f;

// 		for ( unsigned int x = 0; x < retinasize; x++ )
// 		{
// 			for ( unsigned int y = vstart+(retinasize*4*x); y < vstart+(retinasize*4*x)+(retinasize*4); y+=4 )
// 			{
// // 				cerr << " now = " << y << endl;
// 				if ( brain.Inputs[y].output ) cerr << "\033[1;34mB\033[0m";
// 				else cerr << ".";
// 				if ( brain.Inputs[y+1].output ) cerr << "\033[1;32mG\033[0m";
// 				else cerr << ".";
// 				if ( brain.Inputs[y+2].output ) cerr << "\033[1;31mR\033[0m";
// 				else cerr << ".";
// 				if ( brain.Inputs[y+3].output ) cerr << "\033[1;35mA\033[0m";
// 				else cerr << ".";
// 			}
// 			cerr << endl;
// 		}
// 		cerr << endl;
// 
// 		for ( unsigned int h=retinaRowStart; h < retinaRowStart+(retinasize*retinaRowLength); h += retinaRowLength )
// 		{
// 			for ( unsigned int w=h+retinaColumnStart; w < h+retinaColumnStart+((retinasize)*4); w+=4 )
// 			{
// 				if ( (int)retina[w] ) cerr << "\033[1;34mB\033[0m";
// 				else cerr << ".";
// 				if ( (int)retina[w+1] ) cerr << "\033[1;32mG\033[0m";
// 				else cerr << ".";
// 				if ( (int)retina[w+2] ) cerr << "\033[1;31mR\033[0m";
// 				else cerr << ".";
// 				if ( (int)retina[w+3] ) cerr << "\033[1;35mA\033[0m";
// 				else cerr << ".";
// 			}
// 			cerr << endl;
// 		}
// 		cerr << endl;

	// constraint angle neurons
		for ( unsigned int i=0; i < body.constraints.size(); i++ )
			brain.Inputs[overstep++].output = body.constraints[i]->getAngle();

	// debugging check
		if ( overstep-1 != brain.numberOfInputs-1 )
		{
			cerr << overstep << " does not equal " << brain.Inputs.size()-1 << endl;
			exit(0);
		}
}

btVector3 CritterB::getScreenDirection(const int& x, const int& y)
{
	float directionlength = 1000000.f;

	btTransform tr = body.mouths[0]->ghostObject->getWorldTransform();
	btVector3 forwardRay( 
		-tr.getBasis()[0][2], 
		-tr.getBasis()[1][2], 
		-tr.getBasis()[2][2]); 
	forwardRay *=  directionlength;

	btVector3 upRay( 
		tr.getBasis()[0][1], 
		tr.getBasis()[1][1], 
		tr.getBasis()[2][1]); 

	btVector3 hor = forwardRay.cross(upRay);
	hor.normalize();
	hor *= directionlength;

	upRay = hor.cross(forwardRay);
	upRay.normalize();
	upRay *= directionlength;

	btVector3 rayTo = (tr.getOrigin() + forwardRay) - (0.5f * hor) + (0.5f * upRay);
	rayTo += x * (hor * (1.0f/(genotype->bodyArch->retinasize)));
	rayTo -= y * (upRay * (1.0f/(genotype->bodyArch->retinasize)));

	return rayTo;
}

void CritterB::mutateBrain() // FIXME PUSH THIS TO BODYARCH MUTATE FUNCTION
{
// 	// mutate color
// 	unsigned int mode = RandGen::Instance()->get(1,2);
// 	unsigned int ncolor = RandGen::Instance()->get(0,2);
// 
// 	// nasty correction
// 	if ( ncolor == 1 )
// 		ncolor = 0;
// 	if ( mode == 1 )
// 	{
// 		color[ncolor] += (float)RandGen::Instance()->get(1,10)/100.0f;
// 		if ( color[ncolor] > 1.0f ) color[ncolor] = 1.0f;
// 	}
// 	else
// 	{
// 		color[ncolor] -= (float)RandGen::Instance()->get(1,10)/100.0f;
// 		if ( color[ncolor] < colorTrim ) color[ncolor] = colorTrim;
// 	}
}


// Vision Stuff
	void CritterB::place()
	{
		glViewport(framePosX, framePosY, genotype->bodyArch->retinasize, genotype->bodyArch->retinasize);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum( -0.05f, 0.05f, -0.05, 0.05, 0.1f, (float)*critter_sightrange/10);

		body.mouths[0]->ghostObject->getWorldTransform().inverse().getOpenGLMatrix(position);
		glMultMatrixf(position);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void CritterB::calcFramePos(unsigned int pos)
	{
		visionPosition = pos;

		// Calc 2D cartesian vectors X & Y for frame positioning of retina
		framePosY = 0;
		while ( pos >= *retinasperrow )
		{
			pos -= *retinasperrow;
			framePosY += genotype->bodyArch->retinasize;
		}
		framePosX = (pos * genotype->bodyArch->retinasize) + pos;

		// Calculate where in the Great Retina this critter shold start (column & row)
		unsigned int target = visionPosition;
		retinaRowStart = 0;

		// determine on which row of the retina to start for this critter
		retinaRowLength = *retinasperrow * (genotype->bodyArch->retinasize+1) * 4;

		// determine on which column to start
		while ( target >= *retinasperrow )
		{
			retinaRowStart += genotype->bodyArch->retinasize * retinaRowLength;
			target -= *retinasperrow;
		}
		retinaColumnStart = target * (genotype->bodyArch->retinasize+1) * 4;

	// cerr << framePosX << " : " << framePosY << endl;
	// usleep (1000);

	}

	void CritterB::printVision()
	{
		for ( unsigned int h=retinaRowStart; h < retinaRowStart+(genotype->bodyArch->retinasize*retinaRowLength); h += retinaRowLength )
		{
			for ( unsigned int w=h+retinaColumnStart; w < h+retinaColumnStart+((genotype->bodyArch->retinasize)*4); w+=4 )
			{
				if ( (int)retina[w+2] ) cerr << "\033[1;31mR\033[0m";
				else cerr << ".";
				if ( (int)retina[w+1] ) cerr << "\033[1;32mG\033[0m";
				else cerr << ".";
				if ( (int)retina[w] ) cerr << "\033[1;34mB\033[0m";
				else cerr << ".";
				if ( (int)retina[w+3] ) cerr << "\033[1;35mA\033[0m";
				else cerr << ".";
			}
			cerr << "" << endl;
		}
		cerr << "" << endl;
	}

CritterB::~CritterB()
{
	genotypes->remove(genotype);
	delete raycast;
}


