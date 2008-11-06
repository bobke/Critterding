#include "critterb.h"

void CritterB::initConst()
{
	settings = Settings::Instance();

	totalFrames		= 0;
	procreateTimeCount	= 0;
	fireTimeCount		= 0;

	carriesFood		= false;
	carriesCorpse		= false;

	resize(settings->critter_size);

	speedfactor = settings->critter_speed;

	sightrange = settings->critter_sightrange;

	components		= 4;
	colorTrim		= 0.375f; // (1/256) * 96
}

CritterB::CritterB()
{
	initConst();

	crittertype		= 0;
	adamdist		= 0;

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

	// give it a random color
	color[0] = (float)randgen->Instance()->get( 10*colorTrim,100 ) / 100.0f;
	color[1] = (float)randgen->Instance()->get( 10*colorTrim,100 ) / 100.0f;
	color[2] = (float)randgen->Instance()->get( 10*colorTrim,100 ) / 100.0f;

	items = retinasize * retinasize * components;
	brain.numberOfInputs = items+26; // 1 over food + 1 over corpse + 1 can fire bullet + 1 can procreate + 10 energy neurons + 10 age neurons + 1 carrying food neuron + 1 carrying corpse neuron
	brain.numberOfOutputs = 13;

	brain.buildArch();
}

CritterB::CritterB(string &critterstring)
{
	initConst();

	loadCritterB(critterstring);

	items = retinasize * retinasize * components;
}

CritterB::CritterB(CritterB &other)
{
	initConst();

	color[0]					= other.color[0];
	color[1]					= other.color[1];
	color[2]					= other.color[2];

	crittertype					= other.crittertype;
	adamdist					= other.adamdist;
	retinasize					= other.retinasize;

	brain.copyFrom(other.brain);

	items = retinasize * retinasize * components;
}

void CritterB::calcRotSinCos()
{
	float reused = rotation * 0.0174532925f;
	reuseRotSinX = sin(reused);
	reuseRotCosX = cos(reused);

	reused = (90.0f+rotation) * 0.0174532925f;
	reuseRotSinY = sin(reused);
	reuseRotCosY = cos(reused);
}

void CritterB::process()
{
	// increase counters
		totalFrames++;
		procreateTimeCount++;
		fireTimeCount++;

	// reset motor bools
		movementsmade	= 0;
		eat		= false;
		fire		= false;
		procreate	= false;
		carrydrop	= false;

		nosecolor[0]	= 0.0f;
		nosecolor[1]	= 0.0f;
		nosecolor[2]	= 0.0f;

	// wasShot (used in world)
		wasShot		= false;

	// newpos = pos
		prepNewPoss();

	// SENSORS
		procInputNeurons();

	// INTERS
		brain.process();

	// MOTORS
		procOutputNeurons();

	// calc used energy, energyUsed is used in world aswell, don't remove

		energyUsed = ( (float)brain.totalNeurons + (float)brain.neuronsFired + (2.0f*(float)motorneuronsfired) + ((float)brain.totalSynapses/10.0f) ) / 200.0f;

// 		energyUsed = brain.totalNeurons * costofhavingneuron;
// 		energyUsed = brain.totalSynapses * costofhavingsynapse;
// 		energyUsed = brain.neuronsFired * costoffiringneuron;
// 		energyUsed = motorneuronsfired * costoffiringmotorneuron;
// 		energyUsed = movementsmade * costofmovement;

	// make nose white if nosecolor is all 0
		if ( nosecolor[0] == 0.0f && nosecolor[1] == 0.0f && nosecolor[2] == 0.0f )
		{
			nosecolor[0]	= 1.0f;
			nosecolor[1]	= 1.0f;
			nosecolor[2]	= 1.0f;
		}

// cerr << energyUsed << endl;
// 
// 		energyUsed = ( (float)brain.neuronsFired + (2.0f*(float)motorneuronsfired) + ((float)brain.totalSynapses/50.0f) ) / 50.0f;
// 
// cerr << " vs " << energyUsed << endl << endl;;

	// apply energy usage
	energyLevel -= energyUsed;
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

void CritterB::procInputNeurons()
{

	// clear all inputs

	brain.clearInputs();

	// vision

// see what it sees
// 		for ( unsigned int h=retinaRowStart; h < retinaRowStart+(retinasize*retinaRowLength); h += retinaRowLength )
// 		{
// 			for ( unsigned int w=h+retinaColumnStart; w < h+retinaColumnStart+((retinasize)*components); w+=4 )
// 			{
// 				if ( (int)retina[w] ) cerr << "\033[1;31mR\033[0m";
// 				else cerr << ".";
// 				if ( (int)retina[w+1] ) cerr << "\033[1;32mG\033[0m";
// 				else cerr << ".";
// 				if ( (int)retina[w+2] ) cerr << "\033[1;34mB\033[0m";
// 				else cerr << ".";
// 				if ( (int)retina[w+3] ) cerr << "\033[1;35mA\033[0m";
// 				else cerr << ".";
// 			}
// 			cerr << "" << endl;
// 		}
// 		cerr << "" << endl;
// 		usleep (10000);

		unsigned int i=0;
		for ( unsigned int h=retinaRowStart; h < retinaRowStart+(retinasize*retinaRowLength); h += retinaRowLength )
		{
			for ( unsigned int w=h+retinaColumnStart; w < h+retinaColumnStart+((retinasize)*components); w++ )
			{
				brain.Inputs[i++].output = (float)retina[w] / 256.0f;
			}
		}

	unsigned int overstep = items;

	// over food sensor neuron
		if ( touchingFood )	brain.Inputs[overstep++].output = 1;
		else			brain.Inputs[overstep++].output = 0;

	// over corpse sensor neuron
		if ( touchingCorpse )	brain.Inputs[overstep++].output = 1;
		else			brain.Inputs[overstep++].output = 0;

	// can fire a bullet
		canFire		= false;
		if ( fireTimeCount > settings->critter_fireinterval && energyLevel > settings->critter_minenergyfire )
		{
			brain.Inputs[overstep++].output = 1;
			canFire = true;
		}
		else brain.Inputs[overstep++].output = 0;

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

	// carries food
		if (carriesFood) brain.Inputs[overstep++].output = 1;

	// carries corpse
		if (carriesCorpse) brain.Inputs[overstep++].output = 1;

	// debugging check
// 		if ( overstep-1 != brain.Inputs.size()-1 )
// 		{
// 			cerr << overstep << " does not equal " << brain.Inputs.size()-1 << endl;
// 			exit(0);
// 		}
}

void CritterB::procOutputNeurons()
{
	motorneuronsfired = 0;

	// there are 10 motor neurons

	if ( brain.Outputs[0].output > 0 )
	{
		moveForward();
		motorneuronsfired++;
		movementsmade++;
	}

	if ( brain.Outputs[1].output > 0 )
	{
		moveBackward();
		motorneuronsfired++;
		movementsmade++;
	}

	if ( brain.Outputs[2].output > 0 )
	{
		moveLeft();
		motorneuronsfired++;
		movementsmade++;
	}

	if ( brain.Outputs[3].output > 0 )
	{
		moveRight();
		motorneuronsfired++;
		movementsmade++;
	}

	if ( brain.Outputs[4].output > 0 )
	{
		rotateLeft();
		motorneuronsfired++;
		movementsmade++;
	}

	if ( brain.Outputs[5].output > 0 )
	{
		rotateRight();
		motorneuronsfired++;
		movementsmade++;
	}

	if ( brain.Outputs[6].output > 0 )
	{
		eat = true;
		motorneuronsfired++;
	}

	if ( brain.Outputs[7].output > 0 )
	{
		fire = true;
		motorneuronsfired++;
	}

	if ( brain.Outputs[8].output > 0 )
	{
		procreate = true;
		motorneuronsfired++;
	}

	if ( brain.Outputs[9].output > 0 )
	{
		carrydrop = true;
		motorneuronsfired++;
	}

	if ( brain.Outputs[10].output > 0 )
	{
		nosecolor[0] = 1.0f;
		motorneuronsfired++;
	}

	if ( brain.Outputs[11].output > 0 )
	{
		nosecolor[1] = 1.0f;
		motorneuronsfired++;
	}

	if ( brain.Outputs[12].output > 0 )
	{
		nosecolor[2] = 1.0f;
		motorneuronsfired++;
	}
}

void CritterB::mutate()
{
	adamdist++;

	// herbivore / carnivore switch
	if ( randgen->Instance()->get(1,100) <= settings->critter_percentchangetype )
	{
		if ( crittertype == 0 )
			crittertype = 1;
		else
			crittertype = 0;
	}

	// mutate color
	unsigned int mode = randgen->Instance()->get(1,2);
	unsigned int ncolor = randgen->Instance()->get(0,2);

	if ( mode == 1 )
	{
		color[ncolor] += (float)randgen->Instance()->get(1,10)/100.0f;
		if ( color[ncolor] > 1.0f ) color[ncolor] = 1.0f;
	}
	else
	{
		color[ncolor] -= (float)randgen->Instance()->get(1,10)/100.0f;
		if ( color[ncolor] < colorTrim ) color[ncolor] = colorTrim;
	}

	unsigned int runs = randgen->Instance()->get(1, settings->critter_maxmutations);
	brain.mutate( runs ); // 0 for random
}


void CritterB::calcCamPos()
{
	cameraposition.x = position.x - (reuseRotSinX * (halfsize - 0.01f));
	cameraposition.z = position.z - (reuseRotCosX * (halfsize - 0.01f));
	cameraposition.y = position.y + 0.05f;
}

void CritterB::place()
{
	glViewport(framePosX, framePosY, retinasize, retinasize);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum( -0.05f, 0.05f, -0.05, 0.05, 0.1f, sightrange);

	glRotatef(rotation, 0.0f, -1.0f, 0.0f);
	glTranslatef(-cameraposition.x, -cameraposition.y, -cameraposition.z);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void CritterB::printVision()
{
	cerr << "hi" << endl;
	int rowlength = retinasize * components;

	cerr << rowlength << " " << items << endl;
	for ( int h=items-rowlength; h >= 0; h -= rowlength )
	{
		for ( int w=h; w < (int)(retinasize*components)+h; w += components )
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

void CritterB::resize(float newsize)
{
	size		= newsize;
	halfsize	= newsize / 2.0f;

	calcCamPos();
}


// Moving

	void CritterB::prepNewPoss()
	{
		moved = false;
		newposition = position;
	}

	void CritterB::moveToNewPoss()
	{
		position = newposition;

		calcFrustrumTriangle();

		calcCamPos();
		if ( carriesFood )
		{
			foodBeingCarried->position.x = position.x;
			foodBeingCarried->position.z = position.z;
		}
	}

	void CritterB::calcFrustrumTriangle()
	{
		frustCullTriangle1 = position;
		frustCullTriangle2 = position;

		frustCullTriangle1.x += reuseRotSinX * 0.5f;
		frustCullTriangle1.z += reuseRotCosX * 0.5f;

		frustCullTriangle2.x -= reuseRotSinX * (sightrange+halfsize);
		frustCullTriangle2.z -= reuseRotCosX * (sightrange+halfsize);

		frustCullTriangle3 = frustCullTriangle2;

		float sr = sightrange/2.0f;
		frustCullTriangle2.x += reuseRotSinY * sr;
		frustCullTriangle2.z += reuseRotCosY * sr;

		frustCullTriangle3.x -= reuseRotSinY * sr;
		frustCullTriangle3.z -= reuseRotCosY * sr;

		v1x = frustCullTriangle1.x - frustCullTriangle3.x;
		v1z = frustCullTriangle1.z - frustCullTriangle3.z;

		v2x = frustCullTriangle2.x - frustCullTriangle3.x;
		v2z = frustCullTriangle2.z - frustCullTriangle3.z;

		denom = v1x*v2z-v1z*v2x;
	}

	bool CritterB::isWithinSight(Vector3f& point)
	{

		// denom = cross(a-c, b-c)
		//  u = cross(p-c, b-c) / denom
		//  v = cross(a-c, p-c) / denom
		//  w = 1 - u - v 

		float realSightRange = sightrange + size;

		if ( fabs( position.x - point.x ) <= realSightRange && fabs( position.z - point.z ) <= realSightRange )
		{
			// p-c
			float v3x = point.x - frustCullTriangle3.x;
			float v3z = point.z - frustCullTriangle3.z;
			float u = (v3x*v2z-v3z*v2x) / denom;
			float v = (v1x*v3z-v1z*v3x) / denom;

			if ( u > 0.0f && u < 1.0f && v > 0.0f && v < 1.0f && u + v < 1.0f )
				return true;
		}
		return false;
	}

	void CritterB::moveForward()
	{
		moved = true;
		newposition.x -= reuseRotSinX * speedfactor;
		newposition.z -= reuseRotCosX * speedfactor;
	}
	
	void CritterB::moveBackward()
	{
		moved = true;
		newposition.x += reuseRotSinX * speedfactor;
		newposition.z += reuseRotCosX * speedfactor;
	}
	
	void CritterB::moveLeft()
	{
		moved = true;
		newposition.x -= reuseRotSinY * speedfactor;
		newposition.z -= reuseRotCosY * speedfactor;
	}
	
	void CritterB::moveRight()
	{
		moved = true;
		newposition.x += reuseRotSinY * speedfactor;
		newposition.z += reuseRotCosY * speedfactor;
	}

// Looking

	void CritterB::rotateLeft()
	{
		rotation += speedfactor*20.0f;
		if ( rotation > 360.0f ) rotation -= 360.0f;

		calcRotSinCos();
		calcFrustrumTriangle();
		calcCamPos();
	}
	
	void CritterB::rotateRight()
	{
		rotation -= speedfactor*20.0f;
		if ( rotation < 0.0f ) rotation += 360.0f;

		calcRotSinCos();
		calcFrustrumTriangle();
		calcCamPos();
	}

	void CritterB::setRotation(unsigned int r)
	{
		rotation = r;
		if ( rotation > 360.0f ) rotation -= 360.0f;

		calcRotSinCos();
		calcFrustrumTriangle();
		calcCamPos();
	}

// LOAD critter

	void CritterB::loadCritterB(string &content)
	{
		string passToBrain;
		string line = parseH->Instance()->returnUntillStrip( "\n", content );
		while ( !line.empty() )
		{
			// color=0.03,0.82,0.12,0;
				if ( parseH->Instance()->beginMatchesStrip( "color=", line ) )
				{
					string R = parseH->Instance()->returnUntillStrip( ",", line );
					string G = parseH->Instance()->returnUntillStrip( ",", line );
					string B = parseH->Instance()->returnUntillStrip( ",", line );
		/*			cerr << "R: " << R  << endl;
					cerr << "G: " << G << endl;
					cerr << "B: " << B << endl;
					cerr << "A: " << A << endl;*/
	
					if(EOF == sscanf(R.c_str(), "%f", &color[0])) cerr << "ERROR INSERTING CRITTER" << endl;
					if(EOF == sscanf(G.c_str(), "%f", &color[1])) cerr << "ERROR INSERTING CRITTER" << endl;
					if(EOF == sscanf(B.c_str(), "%f", &color[2])) cerr << "ERROR INSERTING CRITTER" << endl;
				}
	
			// type=0;
				else if ( parseH->Instance()->beginMatchesStrip( "type=", line ) )
				{
					string CTYPE = parseH->Instance()->returnUntillStrip( ";", line );
					//cerr << "CTYPE: " << CTYPE << endl;
					if(EOF == sscanf(CTYPE.c_str(), "%d", &crittertype)) cerr << "ERROR INSERTING CRITTER" << endl;
				}

			// adamdist=690;
				else if ( parseH->Instance()->beginMatchesStrip( "adamdist=", line ) )
				{
					string AD = parseH->Instance()->returnUntillStrip( ";", line );
					//cerr << "AD: " << AD << endl;
					if(EOF == sscanf(AD.c_str(), "%d", &adamdist)) cerr << "ERROR INSERTING CRITTER" << endl;
				}
	
			// retinasize=9;
				else if ( parseH->Instance()->beginMatchesStrip( "retinasize=", line ) )
				{
					string RES = parseH->Instance()->returnUntillStrip( ";", line );
					//cerr << "RES: " << RES << endl;
					if(EOF == sscanf(RES.c_str(), "%d", &retinasize)) cerr << "ERROR INSERTING CRITTER" << endl;
				}

			// the rest goes to the brain
				else //  if ( parseH->Instance()->beginMatches( "n(", line ) )
				{
					passToBrain.append(line);
					passToBrain.append("\n");
				}
	
			line = parseH->Instance()->returnUntillStrip( "\n", content );
		}

		brain.setArch(&passToBrain);
	}



	string CritterB::saveCritterB()
	{
		stringstream buf;
		buf << "color=" << color[0] << "," << color[1] << "," << color[2] << ";\n";
		buf << "type=" << crittertype << ";\n";
		buf << "adamdist=" << adamdist << ";\n";
		buf << "retinasize=" << retinasize << ";\n";

		string* arch = brain.getArch();
		buf << *arch;
		//cout << *arch << endl;

		return buf.str();
	}


CritterB::~CritterB()
{
}


