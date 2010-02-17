#include "critterb.h"

void CritterB::initConst()
{
	// settings and pointers
	settings = Settings::Instance();
	genotypes = Genotypes::Instance();
	retinasperrow = settings->getCVarPtr("retinasperrow");
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
	components		= 4;
	colorTrim		= 0.15f;

	eat			= false;
	procreate		= false;

	// raycast
	raycast = new Raycast(btDynWorld);
}

CritterB::CritterB(btDynamicsWorld* btWorld, long unsigned int id, const btVector3& startPos, unsigned char* retinap)
{
	// first things first
	btDynWorld						= btWorld;
	retina							= retinap;
	critterID						= id;

	initConst();

	adamdist						= 0;

	energyLevel						= settings->getCVar("critter_startenergy");

// 	lifetime						= settings->critter_maxlifetime;
	retinasize						= settings->getCVar("critter_retinasize");

	genotype = genotypes->newg();

	genotype->brainzArch->maxNeurons					= settings->getCVar("brain_maxneurons");
	genotype->brainzArch->minSynapses					= settings->getCVar("brain_minsynapses");
	genotype->brainzArch->maxSynapses					= settings->getCVar("brain_maxsynapses");
	genotype->brainzArch->minNeuronsAtBuildtime				= settings->getCVar("brain_minneuronsatbuildtime");
	genotype->brainzArch->maxNeuronsAtBuildtime				= settings->getCVar("brain_maxneuronsatbuildtime");

	genotype->brainzArch->minSynapsesAtBuildtime				= settings->getCVar("brain_minsynapsesatbuildtime");
// 		brain.mutate_minSynapsesAtBuildtime		= settings->getCVar("brain_mutate_minsynapsesatbuildtime");

	genotype->brainzArch->maxSynapsesAtBuildtime				= settings->getCVar("brain_maxsynapsesatbuildtime");
// 		brain.mutate_maxSynapsesAtBuildtime		= settings->getCVar("brain_mutate_maxsynapsesatbuildtime");

	genotype->brainzArch->percentChanceInhibitoryNeuron			= settings->getCVar("brain_percentchanceinhibitoryneuron");
		genotype->brainzArch->mutate_percentChanceInhibitoryNeuron	= settings->getCVar("brain_mutate_percentchanceinhibitoryneuron");

	genotype->brainzArch->percentChanceMotorNeuron				= settings->getCVar("brain_percentchancemotorneuron");
		genotype->brainzArch->mutate_percentChanceMotorNeuron		= settings->getCVar("brain_mutate_percentchancemotorneuron");

	genotype->brainzArch->percentChancePlasticNeuron			= settings->getCVar("brain_percentchanceplasticneuron");
		genotype->brainzArch->mutate_percentChancePlasticNeuron			= settings->getCVar("brain_mutate_percentchanceplasticneuron");

	genotype->brainzArch->minPlasticityStrengthen				= settings->getCVar("brain_minplasticitystrengthen");
	genotype->brainzArch->maxPlasticityStrengthen				= settings->getCVar("brain_maxplasticitystrengthen");
	genotype->brainzArch->minPlasticityWeaken				= settings->getCVar("brain_minplasticityweaken");
	genotype->brainzArch->maxPlasticityWeaken				= settings->getCVar("brain_maxplasticityweaken");
		genotype->brainzArch->mutate_PlasticityFactors				= settings->getCVar("brain_mutate_plasticityfactors");

	genotype->brainzArch->minFiringThreshold				= settings->getCVar("brain_minfiringthreshold");
		genotype->brainzArch->mutate_minFiringThreshold				= settings->getCVar("brain_mutate_minfiringthreshold");

	genotype->brainzArch->maxFiringThreshold				= settings->getCVar("brain_maxfiringthreshold");
		genotype->brainzArch->mutate_maxFiringThreshold				= settings->getCVar("brain_mutate_maxfiringthreshold");

	genotype->brainzArch->maxDendridicBranches				= settings->getCVar("brain_maxdendridicbranches");
		genotype->brainzArch->mutate_maxDendridicBranches		= settings->getCVar("brain_mutate_maxdendridicbranches");

	genotype->brainzArch->percentChanceConsistentSynapses			= settings->getCVar("brain_percentchanceconsistentsynapses");
		genotype->brainzArch->mutate_percentChanceConsistentSynapses		= settings->getCVar("brain_mutate_percentchanceconsistentsynapses");

	genotype->brainzArch->percentChanceInhibitorySynapses			= settings->getCVar("brain_percentchanceinhibitorysynapses");
		genotype->brainzArch->mutate_percentChanceInhibitorySynapses		= settings->getCVar("brain_mutate_percentchanceinhibitorysynapses");

	genotype->brainzArch->percentChanceSensorySynapse			= settings->getCVar("brain_percentchancesensorysynapse");
		genotype->brainzArch->mutate_percentChanceSensorySynapse	= settings->getCVar("brain_mutate_percentchancesensorysynapse");

	genotype->brainzArch->percentMutateEffectAddNeuron			= settings->getCVar("brain_percentmutateeffectaddneuron");
	genotype->brainzArch->percentMutateEffectRemoveNeuron			= settings->getCVar("brain_percentmutateeffectremoveneuron");
	genotype->brainzArch->percentMutateEffectAlterNeuron			= settings->getCVar("brain_percentmutateeffectalterneuron");
	genotype->brainzArch->percentMutateEffectAddSynapse			= settings->getCVar("brain_percentmutateeffectaddsynapse");
	genotype->brainzArch->percentMutateEffectRemoveSynapse			= settings->getCVar("brain_percentmutateeffectremovesynapse");
		genotype->brainzArch->mutate_MutateEffects				= settings->getCVar("brain_mutate_mutateeffects");

	color[0] = (float)RandGen::Instance()->get( 10*colorTrim,100 ) / 100.0f;
	color[1] = (float)RandGen::Instance()->get( 10*colorTrim,100 ) / 100.0f;
	color[2] = (float)RandGen::Instance()->get( 10*colorTrim,100 ) / 100.0f;
	color[3] = 0.0f;

	speciescolor[0] = (float)RandGen::Instance()->get( 10*colorTrim,100 ) / 100.0f;
	speciescolor[1] = (float)RandGen::Instance()->get( 10*colorTrim,100 ) / 100.0f;
	speciescolor[2] = (float)RandGen::Instance()->get( 10*colorTrim,100 ) / 100.0f;
	speciescolor[3] = 0.0f;

	// BODY
	genotype->bodyArch->buildArch();
	body.wireArch( genotype->bodyArch, (void*)this, btDynWorld, startPos );

	// LINK
	registerBrainInputOutputs();
	
	// BRAIN
	genotype->brainzArch->buildArch();
	brain.wireArch( genotype->brainzArch );
}

CritterB::CritterB(CritterB& other, long unsigned int id, const btVector3& startPos, bool brainmutant, bool bodymutant)
{

	// first things first
	btDynWorld					= other.btDynWorld;
	retina						= other.retina;
	critterID					= id;

	initConst();

	adamdist					= other.adamdist;
	retinasize					= other.retinasize;
// 	lifetime					= other.lifetime;

	color[0]					= other.color[0];
	color[1]					= other.color[1];
	color[2]					= other.color[2];
	color[3]					= other.color[3];

	speciescolor[0]					= other.speciescolor[0];
	speciescolor[1]					= other.speciescolor[1];
	speciescolor[2]					= other.speciescolor[2];
	speciescolor[3]					= other.speciescolor[3];

	// IF we mutate, copy the genotype
	if ( bodymutant || brainmutant )
		genotype = genotypes->copy(other.genotype);
	else
	{
		genotypes->add(other.genotype);
		genotype = other.genotype;
	}
	
	if ( bodymutant )
		mutateBody();

	body.wireArch( genotype->bodyArch, (void*)this, btDynWorld, startPos );

	// LINK
	registerBrainInputOutputs();
	if ( bodymutant )
		genotype->brainzArch->removeObsoleteMotorsAndSensors();

	// BRAIN
	if ( brainmutant )
		mutateBrain();

	brain.wireArch( genotype->brainzArch );
}

CritterB::CritterB(string &critterstring, btDynamicsWorld* btWorld, const btVector3& startPos, unsigned char* retinap)
{
	// critterID is arranged in world, definite critter insertion is not determined yet

	// first things first
	btDynWorld		= btWorld;
	retina			= retinap;

	initConst();

	energyLevel		= settings->getCVar("critter_startenergy");

	speciescolor[0] = (float)RandGen::Instance()->get( 10*colorTrim,100 ) / 100.0f;
	speciescolor[1] = (float)RandGen::Instance()->get( 10*colorTrim,100 ) / 100.0f;
	speciescolor[2] = (float)RandGen::Instance()->get( 10*colorTrim,100 ) / 100.0f;
	speciescolor[3] = 0.0f;

	genotype = genotypes->newg(); // FIXME, with a speciesID
	loadCritterB(critterstring);

	// BODY
	body.wireArch( genotype->bodyArch, (void*)this, btDynWorld, startPos );

	// LINK
	registerBrainInputOutputs();

	// BRAIN
	brain.wireArch( genotype->brainzArch );
}

void CritterB::registerBrainInputOutputs()
{

// BRAIN INPUTS

	// touching food
		brain.registerInput( 10000 );
		genotype->brainzArch->registerInput( 10000 );


	// touching critter
		brain.registerInput( 10001 );
		genotype->brainzArch->registerInput( 10001 );

	// canprocreate
		brain.registerInput( 20000 );
		genotype->brainzArch->registerInput( 20000 );

	// energy state
		for ( unsigned int i=0; i < 10; i++ )
		{
			brain.registerInput( 30000+i );
			genotype->brainzArch->registerInput( 30000+i );
		}
	// age state
		for ( unsigned int i=0; i < 10; i++ )
		{
			brain.registerInput( 40000+i );
			genotype->brainzArch->registerInput( 40000+i );
		}

	// vision retina number of items
		items = retinasize * retinasize * components;
		for ( unsigned int i=0; i < items; i++ )
		{
			brain.registerInput( 50000+i );
			genotype->brainzArch->registerInput( 50000+i );
		}

	// register constraint angles outputs as brain inputs, take constraint_id1 for ease
		for ( unsigned int i=0; i < genotype->bodyArch->archConstraints.size(); i++ )
		{
			brain.registerInput( genotype->bodyArch->archConstraints[i].constraint_id1 );
			genotype->brainzArch->registerInput( genotype->bodyArch->archConstraints[i].constraint_id1 );
		}

// BRAIN OUTPUTS

	// register constraints's inputs as brain outputs
		for ( unsigned int i=0; i < body.constraints.size(); i++ )
		{
			for ( unsigned int j=0; j < body.constraints[i]->Inputs.size(); j+=2 )
			{
				brain.registerOutput( body.constraints[i]->Inputs[j], genotype->bodyArch->archConstraints[i].constraint_id1 );
				brain.registerOutput( body.constraints[i]->Inputs[j+1], genotype->bodyArch->archConstraints[i].constraint_id2 );
				
				genotype->brainzArch->registerOutput( genotype->bodyArch->archConstraints[i].constraint_id1 );
				genotype->brainzArch->registerOutput( genotype->bodyArch->archConstraints[i].constraint_id2 );
			}
		}

	// eat
		brain.registerOutput( &eat, 100000 );
		genotype->brainzArch->registerOutput( 100000 );

	// procreate
		brain.registerOutput( &procreate, 100001 );
		genotype->brainzArch->registerOutput( 100001 );
}

void CritterB::draw(bool drawFaces)
{
	for( unsigned int j=0; j < body.bodyparts.size(); j++)
	{
		body.bodyparts[j]->myMotionState->m_graphicsWorldTrans.getOpenGLMatrix(position);

		glPushMatrix(); 
		glMultMatrixf(position);

			if ( settings->getCVar("colormode") == 1 )
				glColor4f( speciescolor[0], speciescolor[1], speciescolor[2], speciescolor[3] );
			else
				glColor4f( color[0], color[1], color[2], 0.0f );

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
			for ( int y = retinasize-1; y >= 0; y-- )
				for ( unsigned int x = 0; x < retinasize; x++ )
				{
// 					cerr << "starting" << endl;
					mouseRay = raycast->cast( body.mouths[0]->ghostObject->getWorldTransform().getOrigin(), getScreenDirection(x+1, y) );
// 					cerr << "e1" << endl;
					if ( mouseRay.hit )
					{
						Entity* e = static_cast<Entity*>(mouseRay.hitBody->getUserPointer());
						brain.Inputs[overstep++].output = e->color[0];
						brain.Inputs[overstep++].output = e->color[1];
						brain.Inputs[overstep++].output = e->color[2];
						brain.Inputs[overstep++].output = e->color[3];
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
			for ( unsigned int h=retinaRowStart; h < retinaRowStart+(retinasize*retinaRowLength); h += retinaRowLength )
				for ( unsigned int w=h+retinaColumnStart; w < h+retinaColumnStart+((retinasize)*components); w++ )
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
// 			for ( unsigned int w=h+retinaColumnStart; w < h+retinaColumnStart+((retinasize)*components); w+=components )
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
	rayTo += x * (hor * (1.0f/(retinasize)));
	rayTo -= y * (upRay * (1.0f/(retinasize)));

	return rayTo;
}


void CritterB::mutateBody()
{
	adamdist++;

	// mutate color
	unsigned int mode = RandGen::Instance()->get(1,2);
	unsigned int ncolor = RandGen::Instance()->get(0,2);

	// nasty correction
	if ( ncolor == 1 )
		ncolor = 0;
	if ( mode == 1 )
	{
		color[ncolor] += (float)RandGen::Instance()->get(1,10)/100.0f;
		if ( color[ncolor] > 1.0f ) color[ncolor] = 1.0f;
	}
	else
	{
		color[ncolor] -= (float)RandGen::Instance()->get(1,10)/100.0f;
		if ( color[ncolor] < colorTrim ) color[ncolor] = colorTrim;
	}

	// a new speciescolor
	speciescolor[0] = (float)RandGen::Instance()->get( 10*colorTrim,100 ) / 100.0f;
	speciescolor[1] = (float)RandGen::Instance()->get( 10*colorTrim,100 ) / 100.0f;
	speciescolor[2] = (float)RandGen::Instance()->get( 10*colorTrim,100 ) / 100.0f;

	unsigned int runs = RandGen::Instance()->get(1, settings->getCVar("body_maxmutations"));

	genotype->bodyArch->mutate( runs ); // 0 for random
// 	cerr << "MUTATION is disabled at tis time" << endl;
}

void CritterB::mutateBrain()
{
	adamdist++;

	// mutate color
	unsigned int mode = RandGen::Instance()->get(1,2);
	unsigned int ncolor = RandGen::Instance()->get(0,2);

	// nasty correction
	if ( ncolor == 1 )
		ncolor = 0;
	if ( mode == 1 )
	{
		color[ncolor] += (float)RandGen::Instance()->get(1,10)/100.0f;
		if ( color[ncolor] > 1.0f ) color[ncolor] = 1.0f;
	}
	else
	{
		color[ncolor] -= (float)RandGen::Instance()->get(1,10)/100.0f;
		if ( color[ncolor] < colorTrim ) color[ncolor] = colorTrim;
	}

	// a new speciescolor
	speciescolor[0] = (float)RandGen::Instance()->get( 10*colorTrim,100 ) / 100.0f;
	speciescolor[1] = (float)RandGen::Instance()->get( 10*colorTrim,100 ) / 100.0f;
	speciescolor[2] = (float)RandGen::Instance()->get( 10*colorTrim,100 ) / 100.0f;

	unsigned int runs = RandGen::Instance()->get(1, settings->getCVar("brain_maxmutations"));
	genotype->brainzArch->mutate( runs ); // 0 for random
// 	cerr << "MUTATION is disabled at tis time" << endl;
}

// LOAD critter

void CritterB::loadCritterB(string &content)
{
	string passToBody;
	string passToBrain;
	string line = Parser::Instance()->returnUntillStrip( "\n", content );
	while ( !line.empty() )
	{
		// color=0.03,0.82,0.12,0;
			if ( Parser::Instance()->beginMatchesStrip( "color=", line ) )
			{
				string R = Parser::Instance()->returnUntillStrip( ",", line );
				string G = Parser::Instance()->returnUntillStrip( ",", line );
				string B = Parser::Instance()->returnUntillStrip( ";", line );

				if(EOF == sscanf(R.c_str(), "%f", &color[0])) cerr << "ERROR INSERTING CRITTER (colorR)" << endl;
				if(EOF == sscanf(G.c_str(), "%f", &color[1])) cerr << "ERROR INSERTING CRITTER (colorG)" << endl;
				if(EOF == sscanf(B.c_str(), "%f", &color[2])) cerr << "ERROR INSERTING CRITTER (colorB)" << endl;
				color[3] = 0.0f;
			}

		// adamdist=690;
			else if ( Parser::Instance()->beginMatchesStrip( "adamdist=", line ) )
			{
				string AD = Parser::Instance()->returnUntillStrip( ";", line );
				//cerr << "AD: " << AD << endl;
				if(EOF == sscanf(AD.c_str(), "%d", &adamdist)) cerr << "ERROR INSERTING CRITTER" << endl;
			}

		// retinasize=9;
			else if ( Parser::Instance()->beginMatchesStrip( "retinasize=", line ) )
			{
				string RES = Parser::Instance()->returnUntillStrip( ";", line );
				//cerr << "RES: " << RES << endl;
				if(EOF == sscanf(RES.c_str(), "%d", &retinasize)) cerr << "ERROR INSERTING CRITTER" << endl;
			}

		// the rest goes to the body or brain
			else
			{
				if ( 
					Parser::Instance()->beginMatches( "b ", line ) ||
					Parser::Instance()->beginMatches( "m ", line ) ||
					Parser::Instance()->beginMatches( "c ", line ) ||
					Parser::Instance()->beginMatches( "cm ", line )
				)
				{
					passToBody.append(line);
					passToBody.append("\n");
				}
				else
				{
					passToBrain.append(line);
					passToBrain.append("\n");
				}
			}

		line = Parser::Instance()->returnUntillStrip( "\n", content );
	}

	genotype->bodyArch->setArch(&passToBody);
	genotype->brainzArch->setArch(&passToBrain);
}

string CritterB::saveCritterB()
{
	stringstream buf;
	buf << "color=" << color[0] << "," << color[1] << "," << color[2] << ";\n";
	buf << "adamdist=" << adamdist << ";\n";
	buf << "retinasize=" << retinasize << ";\n";

	string* bodyarch = genotype->bodyArch->getArch();
	string* brainarch = genotype->brainzArch->getArch();
	buf << *bodyarch;
	buf << *brainarch;
	//cout << *arch << endl;

	return buf.str();
}

// Vision Stuff
	void CritterB::place()
	{
		glViewport(framePosX, framePosY, retinasize, retinasize);
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
			framePosY += retinasize;
		}
		framePosX = (pos * retinasize) + pos;

		// Calculate where in the Great Retina this critter shold start (column & row)
		unsigned int target = visionPosition;
		retinaRowStart = 0;

		// determine on which row of the retina to start for this critter
		retinaRowLength = *retinasperrow * (retinasize+1) * components;

		// determine on which column to start
		while ( target >= *retinasperrow )
		{
			retinaRowStart += retinasize * retinaRowLength;
			target -= *retinasperrow;
		}
		retinaColumnStart = target * (retinasize+1) * components;

	// cerr << framePosX << " : " << framePosY << endl;
	// usleep (1000);

	}

	void CritterB::printVision()
	{
		for ( unsigned int h=retinaRowStart; h < retinaRowStart+(retinasize*retinaRowLength); h += retinaRowLength )
		{
			for ( unsigned int w=h+retinaColumnStart; w < h+retinaColumnStart+((retinasize)*components); w+=components )
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


