#include "critterb.h"

void CritterB::initConst()
{
	settings = Settings::Instance();
	type = 0;

	totalFrames		= 0;
	procreateTimeCount	= 0;

// 	sightrange = settings->critter_sightrange;
	components		= 4;
	colorTrim		= 0.15f;
}

CritterB::CritterB(btDynamicsWorld* btWorld, long unsigned int id, const btVector3& startPos, unsigned char* retinap)
{
	initConst();
	
	// first things first
	btDynWorld						= btWorld;
	retina							= retinap;
	critterID						= id;
	
	adamdist						= 0;

// 	lifetime						= settings->critter_maxlifetime;
	retinasize						= settings->critter_retinasize;

	brain.maxNeurons					= settings->brain_maxneurons;
	brain.minSynapses					= settings->brain_minsynapses;
	brain.maxSynapses					= settings->brain_maxsynapses;

	brain.minNeuronsAtBuildtime				= settings->brain_minneuronsatbuildtime;
	brain.maxNeuronsAtBuildtime				= settings->brain_maxneuronsatbuildtime;

	brain.minSynapsesAtBuildtime				= settings->brain_minsynapsesatbuildtime;
		brain.mutate_minSynapsesAtBuildtime		= settings->brain_mutate_minsynapsesatbuildtime;

	brain.maxSynapsesAtBuildtime				= settings->brain_maxsynapsesatbuildtime;
		brain.mutate_maxSynapsesAtBuildtime		= settings->brain_mutate_maxsynapsesatbuildtime;

	brain.percentChanceInhibitoryNeuron			= settings->brain_percentchanceinhibitoryneuron;
		brain.mutate_percentChanceInhibitoryNeuron	= settings->brain_mutate_percentchanceinhibitoryneuron;

	brain.percentChanceConsistentSynapses			= settings->brain_percentchanceconsistentsynapses;
		brain.mutate_percentChanceConsistentSynapses		= settings->brain_mutate_percentchanceconsistentsynapses;

	brain.percentChanceInhibitorySynapses			= settings->brain_percentchanceinhibitorysynapses;
		brain.mutate_percentChanceInhibitorySynapses		= settings->brain_mutate_percentchanceinhibitorysynapses;

	brain.percentChanceMotorNeuron				= settings->brain_percentchancemotorneuron;
		brain.mutate_percentChanceMotorNeuron		= settings->brain_mutate_percentchancemotorneuron;

	brain.percentChancePlasticNeuron				= settings->brain_percentchanceplasticneuron;
		brain.mutate_percentChancePlasticNeuron		= settings->brain_mutate_percentchanceplasticneuron;

	brain.minPlasticityStrengthen				= settings->brain_minplasticitystrengthen;
	brain.maxPlasticityStrengthen				= settings->brain_maxplasticitystrengthen;
	brain.minPlasticityWeaken				= settings->brain_minplasticityweaken;
	brain.maxPlasticityWeaken				= settings->brain_maxplasticityweaken;
		brain.mutate_PlasticityFactors				= settings->brain_mutate_plasticityfactors;

	brain.percentChanceSensorySynapse			= settings->brain_percentchancesensorysynapse;
		brain.mutate_percentChanceSensorySynapse	= settings->brain_mutate_percentchancesensorysynapse;

	brain.minFiringThreshold				= settings->brain_minfiringthreshold;
		brain.mutate_minFiringThreshold				= settings->brain_mutate_minfiringthreshold;

	brain.maxFiringThreshold				= settings->brain_maxfiringthreshold;
		brain.mutate_maxFiringThreshold				= settings->brain_mutate_maxfiringthreshold;

	brain.maxDendridicBranches				= settings->brain_maxdendridicbranches;
		brain.mutate_maxDendridicBranches		= settings->brain_mutate_maxdendridicbranches;

	brain.percentMutateEffectAddNeuron			= settings->brain_percentmutateeffectaddneuron;
	brain.percentMutateEffectRemoveNeuron			= settings->brain_percentmutateeffectremoveneuron;
	brain.percentMutateEffectAlterNeuron			= settings->brain_percentmutateeffectalterneuron;
	brain.percentMutateEffectAddSynapse			= settings->brain_percentmutateeffectaddsynapse;
	brain.percentMutateEffectRemoveSynapse			= settings->brain_percentmutateeffectremovesynapse;
		brain.mutate_MutateEffects				= settings->brain_mutate_mutateeffects;

	color[0] = (float)RandGen::Instance()->get( 10*colorTrim,100 ) / 100.0f;
	color[1] = (float)RandGen::Instance()->get( 10*colorTrim,100 ) / 100.0f;
	color[2] = (float)RandGen::Instance()->get( 10*colorTrim,100 ) / 100.0f;

	speciescolor[0] = (float)RandGen::Instance()->get( 10*colorTrim,100 ) / 100.0f;
	speciescolor[1] = (float)RandGen::Instance()->get( 10*colorTrim,100 ) / 100.0f;
	speciescolor[2] = (float)RandGen::Instance()->get( 10*colorTrim,100 ) / 100.0f;

	// BODY
	body.buildArch();
	body.wireArch( (void*)this, btDynWorld, startPos );

	// LINK
	registerBrainInputOutputs();
	
	// BRAIN
	brain.buildArch();
	brain.wireArch();
}

CritterB::CritterB(CritterB &other, long unsigned int id, const btVector3& startPos, bool brainmutant, bool bodymutant)
{
	initConst();

	// first things first
	btDynWorld					= other.btDynWorld;
	retina						= other.retina;
	critterID					= id;

	adamdist					= other.adamdist;
	retinasize					= other.retinasize;
// 	lifetime					= other.lifetime;

	color[0]					= other.color[0];
	color[1]					= other.color[1];
	color[2]					= other.color[2];

	speciescolor[0]					= other.speciescolor[0];
	speciescolor[1]					= other.speciescolor[1];
	speciescolor[2]					= other.speciescolor[2];

	// BODY FIXME HACK IMPROVE WITHOUT PARSING
// 	string* otherBodyArch = other.body.getArch();
// 	body.setArch(otherBodyArch);
	body.copyFrom(other.body);
	brain.copyFrom(other.brain);

	if ( bodymutant )
	{
		mutateBody();
		brain.removeObsoleteMotorsAndSensors();
	}
	body.wireArch( (void*)this, btDynWorld, startPos );

	// LINK
	registerBrainInputOutputs();

	// BRAIN
	if ( brainmutant )
		mutateBrain();

	brain.wireArch();
}

CritterB::CritterB(string &critterstring, btDynamicsWorld* btWorld, const btVector3& startPos, unsigned char* retinap)
{
	initConst();

	// critterID is arranged in world, definite critter insertion is not determined yet

	// first things first
	btDynWorld					= btWorld;
	retina						= retinap;

	speciescolor[0] = (float)RandGen::Instance()->get( 10*colorTrim,100 ) / 100.0f;
	speciescolor[1] = (float)RandGen::Instance()->get( 10*colorTrim,100 ) / 100.0f;
	speciescolor[2] = (float)RandGen::Instance()->get( 10*colorTrim,100 ) / 100.0f;

	loadCritterB(critterstring);

	// BODY
// 	body.buildArch();
	body.wireArch( (void*)this, btDynWorld, startPos );

	// LINK
	registerBrainInputOutputs();

	// BRAIN
	brain.wireArch();
}

void CritterB::registerBrainInputOutputs()
{

// BRAIN INPUTS

	// touching food
		brain.registerInput( 10000 );

	// canprocreate
		brain.registerInput( 20000 );

	// energy state
		for ( unsigned int i=0; i < 10; i++ )
			brain.registerInput( 30000+i );
	// age state
		for ( unsigned int i=0; i < 10; i++ )
			brain.registerInput( 40000+i );

	// vision retina number of items
		items = retinasize * retinasize * components;
		for ( unsigned int i=0; i < items; i++ )
			brain.registerInput( 50000+i );

	// register constraint angles outputs as brain inputs, take constraint_id1 for ease
		for ( unsigned int i=0; i < body.archConstraints.size(); i++ )
			brain.registerInput( body.archConstraints[i].constraint_id1 );

// BRAIN OUTPUTS

	// register constraints's inputs as brain outputs
		for ( unsigned int i=0; i < body.constraints.size(); i++ )
		{
			for ( unsigned int j=0; j < body.constraints[i]->Inputs.size(); j+=2 )
			{
				brain.registerOutput( body.constraints[i]->Inputs[j], body.archConstraints[i].constraint_id1 );
				brain.registerOutput( body.constraints[i]->Inputs[j+1], body.archConstraints[i].constraint_id2 );
			}
		}

	// eat
		brain.registerOutput( &eat, 100000 );

	// procreate
		brain.registerOutput( &procreate, 100001 );
}

void CritterB::move()
{
	// motorate all constraints
	for ( unsigned int i=0; i < body.constraints.size(); i++ )
	{
		body.constraints[i]->motorate();
	}
}

void CritterB::draw(bool drawFaces)
{
	for( unsigned int j=0; j < body.bodyparts.size(); j++)
	{
		btRigidBody* bodypart = body.bodyparts[j]->body;
		btDefaultMotionState* myMotionState = (btDefaultMotionState*)bodypart->getMotionState();
		myMotionState->m_graphicsWorldTrans.getOpenGLMatrix(position);

		glPushMatrix(); 
		glMultMatrixf(position);

			if ( settings->colormode == 0 )
				glColor4f( color[0], color[1], color[2], 0.0f );
			else if ( settings->colormode == 1 )
				glColor4f( speciescolor[0], speciescolor[1], speciescolor[2], 0.0f );

// 				const btCapsuleShape* capsuleShape = static_cast<const btCapsuleShape*>(body->bodyparts[j]->shape);
// 				btScalar radius = capsuleShape->getRadius();
//  				glScaled(radius, capsuleShape->getHalfHeight(), radius);
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
/*	for( unsigned int j=0; j < body->mouths.size(); j++)
	{
		btRigidBody* bodypart = body->mouths[j]->body;
		btDefaultMotionState* myMotionState = (btDefaultMotionState*)bodypart->getMotionState();
		myMotionState->m_graphicsWorldTrans.getOpenGLMatrix(position);

		glPushMatrix(); 
		glMultMatrixf(position);

			if ( settings->colormode == 0 )
				glColor4f( color[0], color[1], color[2], 0.0f );
			else if ( settings->colormode == 1 )
				glColor4f( speciescolor[0], speciescolor[1], speciescolor[2], 0.0f );

				const btBoxShape* boxShape = static_cast<const btBoxShape*>(body->mouths[j]->shape);
				btVector3 halfExtent = boxShape->getHalfExtentsWithMargin();
				glScaled(halfExtent[0], halfExtent[1], halfExtent[2]);

				Displaylists::Instance()->call(0);

		glPopMatrix();
	}*/
}

void CritterB::process()
{
	// increase counters
		totalFrames++;
		procreateTimeCount++;

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

 		energyUsed =  brain.totalNeurons	* settings->brain_costhavingneuron;
 		energyUsed += brain.neuronsFired	* settings->brain_costfiringneuron;
 		energyUsed += brain.motorneuronsFired	* settings->brain_costfiringmotorneuron;
 		energyUsed += brain.totalSynapses	* settings->brain_costhavingsynapse;
		energyUsed = energyUsed / 100000;
// 		cerr << energyUsed << endl;

	// apply energy usage
	energyLevel -= energyUsed;
}

void CritterB::procInputNeurons()
{

	// clear all inputs

	brain.clearInputs();

	unsigned int overstep = 0;

	// over food sensor neuron
		if ( touchingFood )	brain.Inputs[overstep++].output = 1;
		else			brain.Inputs[overstep++].output = 0;

	// can procreate sensor neuron
		canProcreate	= false;
		if ( procreateTimeCount > settings->critter_procinterval && energyLevel > settings->critter_minenergyproc )
		{
			brain.Inputs[overstep++].output = 1;
			canProcreate = true;
		}
		else brain.Inputs[overstep++].output = 0;

	// energy neurons
		unsigned int NeuronToFire = (int)((energyLevel / (settings->critter_maxenergy+1)) * 10) + overstep;
		unsigned int count = 10 + overstep;
		while ( overstep < count )
		{
			if ( overstep <= NeuronToFire )	brain.Inputs[overstep++].output = 1; // !!! <=
			else 				brain.Inputs[overstep++].output = 0;
		}

	// age neurons
		NeuronToFire = (int)(((float)totalFrames / (settings->critter_maxlifetime+1)) * 10) + overstep;
		count = 10 + overstep;
		while ( overstep < count )
		{
			if ( overstep <= NeuronToFire )	brain.Inputs[overstep++].output = 1; // !!! <=
			else 				brain.Inputs[overstep++].output = 0;
		}

	// Vision
		for ( unsigned int h=retinaRowStart; h < retinaRowStart+(retinasize*retinaRowLength); h += retinaRowLength )
		{
			for ( unsigned int w=h+retinaColumnStart; w < h+retinaColumnStart+((retinasize)*components); w++ )
			{
				brain.Inputs[overstep++].output = (float)retina[w] / 256.0f;
// 				cerr << "brain.Inputs[" << overstep <<  "].output" << endl;
			}
		}

	// constraint angle neurons
		for ( unsigned int i=0; i < body.constraints.size(); i++ )
		{
			brain.Inputs[overstep++].output = body.constraints[i]->getAngle();
		}

	// debugging check
// 		if ( overstep-1 != brain.Inputs.size()-1 )
// 		{
// 			cerr << overstep << " does not equal " << brain.Inputs.size()-1 << endl;
// 			exit(0);
// 		}
}

void CritterB::mutateBody()
{
	adamdist++;

	unsigned int runs = RandGen::Instance()->get(1, settings->body_maxmutations);
	body.mutate( runs ); // 0 for random

	// a new color
	color[0] = (float)RandGen::Instance()->get( 10*colorTrim,100 ) / 100.0f;
	color[1] = (float)RandGen::Instance()->get( 10*colorTrim,100 ) / 100.0f;
	color[2] = (float)RandGen::Instance()->get( 10*colorTrim,100 ) / 100.0f;

	// a new speciescolor
	speciescolor[0] = (float)RandGen::Instance()->get( 10*colorTrim,100 ) / 100.0f;
	speciescolor[1] = (float)RandGen::Instance()->get( 10*colorTrim,100 ) / 100.0f;
	speciescolor[2] = (float)RandGen::Instance()->get( 10*colorTrim,100 ) / 100.0f;
}

void CritterB::mutateBrain()
{
	adamdist++;

// 	// mutate lifetime
// 	if ( RandGen::Instance()->get(1,10) <= 5 )
// 	{
// 		if ( RandGen::Instance()->get(1,2) == 1 )
// 		{
// 			lifetime -= lifetime/20;
// 		}
// 		else
// 		{
// 			lifetime += lifetime/20;
// 			if ( lifetime > settings->critter_maxlifetime )
// 				lifetime = settings->critter_maxlifetime;
// 		}
// 	}

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


	unsigned int runs = RandGen::Instance()->get(1, settings->brain_maxmutations);
	brain.mutate( runs ); // 0 for random
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

	body.setArch(&passToBody);
	brain.setArch(&passToBrain);
}

string CritterB::saveCritterB()
{
	stringstream buf;
	buf << "color=" << color[0] << "," << color[1] << "," << color[2] << ";\n";
	buf << "adamdist=" << adamdist << ";\n";
	buf << "retinasize=" << retinasize << ";\n";

	string* bodyarch = body.getArch();
	string* brainarch = brain.getArch();
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
		glFrustum( -0.05f, 0.05f, -0.05, 0.05, 0.1f, settings->critter_sightrange);

		btScalar position[16];
		btDefaultMotionState* myMotionState = (btDefaultMotionState*)body.mouths[0]->body->getMotionState();
		btTransform tr = myMotionState->m_graphicsWorldTrans.inverse();
		tr.getOpenGLMatrix(position);
		glMultMatrixf(position);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void CritterB::calcFramePos(unsigned int pos)
	{
		visionPosition = pos;

		// Calc 2D cartesian vectors X & Y for frame positioning of retina
		framePosY = 0;
		while ( pos >= settings->retinasperrow )
		{
			pos -= settings->retinasperrow;
			framePosY += retinasize;
		}
		framePosX = (pos * retinasize) + pos;

		// Calculate where in the Great Retina this critter shold start (column & row)
		unsigned int target = visionPosition;
		retinaRowStart = 0;

		// determine on which row of the retina to start for this critter
		retinaRowLength = settings->retinasperrow * (retinasize+1) * components;

		// determine on which column to start
		while ( target >= settings->retinasperrow )
		{
			retinaRowStart += retinasize * retinaRowLength;
			target -= settings->retinasperrow;
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
}


