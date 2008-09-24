#include "critterb.h"

// todo : include mutation % (from world)

void CritterB::initConst()
{
	speedfactor		= 0.0f;
	size			= 0.0f;
	halfsize		= 0.0f;
	colorNeurons		= 0;
	totalFrames		= 0;
	maxtotalFrames		= 0;
	maxEnergyLevel		= 0.0f;

	procreateTimeTrigger	= 0;
	fireTimeTrigger		= 0;

	visionPosition		= 0;
	retinasperrow		= 0;
	retinaColumnStart	= 0;
	retinaRowStart		= 0;
	retinaRowLength		= 0;

	sightrange		= 0.0f;

	carriesFood		= false;
	carriesCorpse		= false;

	components		= 4;
	colorDivider		= 0;
	retinasize		= 0;

	colorTrim		= 0.5f;
}

CritterB::CritterB()
{
	initConst();

	// frame capturing options
	crittertype		= 0;
	adamdist		= 0;

	// give it a random color
	color[0] = (float)randgen.get( 50,100 ) / 100.0f;
	color[1] = (float)randgen.get( 50,100 ) / 100.0f;
	color[2] = (float)randgen.get( 50,100 ) / 100.0f;
	color[3] = 0.0f;
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
	color[3]					= other.color[3];

	crittertype					= other.crittertype;
	adamdist					= other.adamdist;
	retinasize					= other.retinasize;
	colorNeurons					= other.colorNeurons;

	brain.copyFrom(other.brain);

	items = retinasize * retinasize * components;

	// energy
	energyLevel		= other.energyLevel;
}


void CritterB::calcInputOutputNeurons()
{
	items = retinasize * retinasize * components;

	brain.numberOfInputs = (items*colorNeurons)+26; // 1 over food + 1 over corpse + 1 can fire bullet + 1 can procreate + 10 energy neurons + 10 age neurons + 1 carrying food neuron + 1 carrying corpse neuron
	brain.numberOfOutputs = 10;
}

void CritterB::setup()
{
	procreateTimeCount	= 0;
	fireTimeCount		= 0;

//	colorDivider		= 256.0f / colorNeurons;
	colorDivider		= 128.0f / colorNeurons;

	// setup brain from architecture
	brain.wireArch();
}

void CritterB::process()
{
	// increase counters
		totalFrames++;
		procreateTimeCount++;
		fireTimeCount++;

	// reset motor bools
		eat		= false;
		fire		= false;
		procreate	= false;
		carrydrop	= false;

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

// cerr << energyUsed << endl;
// 
// 		energyUsed = ( (float)brain.neuronsFired + (2.0f*(float)motorneuronsfired) + ((float)brain.totalSynapses/50.0f) ) / 50.0f;
// 
// cerr << " vs " << energyUsed << endl << endl;;

	// apply energy usage
	energyLevel -= energyUsed;
}

void CritterB::calcFramePos(unsigned int pos, unsigned int cretinasperrow)
{
	visionPosition = pos;
	retinasperrow = cretinasperrow;

	// Calc 2D cartesian vectors X & Y for frame positioning of retina
	framePosY = 0;
	while ( pos >= retinasperrow )
	{
		pos -= retinasperrow;
		framePosY += retinasize;
	}
	framePosX = (pos * retinasize) + pos;

	// Calculate where in the Great Retina this critter shold start (column & row)
	unsigned int target = visionPosition;
	retinaRowStart = 0;

	// determine on which row of the retina to start for this critter
	retinaRowLength = retinasperrow * (retinasize+1) * components;

	// determine on which column to start
	while ( target >= retinasperrow )
	{
		retinaRowStart += retinasize * retinaRowLength;
		target -= retinasperrow;
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
				if ( (unsigned int)retina[w]>127 ) // >> 127 due to window resizing being a problem.
				{
					brain.Inputs[(i*colorNeurons) + (int)(((float)retina[w]-128) / colorDivider)].output = 1;
				}
				i++;
			}
		}

	unsigned int overstep = items*colorNeurons;

	// over food sensor neuron
		if ( touchingFood )	brain.Inputs[overstep].output = 1;
		else			brain.Inputs[overstep].output = 0;

	overstep++;

	// over corpse sensor neuron
		if ( touchingCorpse )	brain.Inputs[overstep].output = 1;
		else			brain.Inputs[overstep].output = 0;

	overstep++;

	// can fire a bullet
		canFire		= false;
		if ( fireTimeCount > fireTimeTrigger && energyLevel > minfireenergyLevel )
		{
			brain.Inputs[overstep].output = 1;
			canFire = true;
		}
		else brain.Inputs[overstep].output = 0;

	overstep++;

	// can procreate sensor neuron
		canProcreate	= false;
		if ( procreateTimeCount > procreateTimeTrigger && energyLevel > minprocenergyLevel )
		{
			brain.Inputs[overstep].output = 1;
			canProcreate = true;
		}
		else brain.Inputs[overstep].output = 0;

	overstep++;

	// energy neurons
		unsigned int NeuronToFire = (int)((energyLevel / (maxEnergyLevel+1)) * 10) + overstep;
		unsigned int count = 10 + overstep;
		while ( overstep < count )
		{
			if ( overstep <= NeuronToFire )	brain.Inputs[overstep].output = 1; // !!! <=
			else 				brain.Inputs[overstep].output = 0;
			overstep++;
		}

	// age neurons
		NeuronToFire = (int)(((float)totalFrames / (maxtotalFrames+1)) * 10) + overstep;
		count = 10 + overstep;
		while ( overstep < count )
		{
			if ( overstep <= NeuronToFire )	brain.Inputs[overstep].output = 1; // !!! <=
			else 				brain.Inputs[overstep].output = 0;
			overstep++;
		}

	// carries food
		if (carriesFood) brain.Inputs[overstep].output = 1;

	overstep++;

	// carries corpse
		if (carriesCorpse) brain.Inputs[overstep].output = 1;

	// debugging check
// 		if ( overstep != brain.Inputs.size()-1 )
// 		{
// 			cerr << overstep << " does not equal " << brain.Inputs.size()-1 << endl;
// 			exit(0);
// 		}
}

void CritterB::procOutputNeurons()
{
	motorneuronsfired = 0;

	// there are 11 motor neurons

	if ( brain.Outputs[0].output > 0 )
	{
		moveForward();
		motorneuronsfired++;
	}

	if ( brain.Outputs[1].output > 0 )
	{
		moveBackward();
		motorneuronsfired++;
	}

	if ( brain.Outputs[2].output > 0 )
	{
		moveLeft();
		motorneuronsfired++;
	}

	if ( brain.Outputs[3].output > 0 )
	{
		moveRight();
		motorneuronsfired++;
	}

	if ( brain.Outputs[4].output > 0 )
	{
		rotateLeft();
		motorneuronsfired++;
	}

	if ( brain.Outputs[5].output > 0 )
	{
		rotateRight();
		motorneuronsfired++;
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
}

void CritterB::mutate(unsigned int maxMutateRuns, unsigned int percentChangeType)
{
	adamdist++;

	// herbivore / carnivore switch
	if ( randgen.get(1,100) <= percentChangeType )
	{
		if ( crittertype == 0 )
			crittertype = 1;
		else
			crittertype = 0;
	}

	// mutate color
	unsigned int mode = randgen.get(1,2);
	unsigned int ncolor = randgen.get(0,2);

	if ( mode == 1 )
	{
		color[ncolor] += (float)randgen.get(1,10)/120.0f;
		if ( color[ncolor] > 1.0f ) color[ncolor] = 1.0f;
	}
	else
	{
		color[ncolor] -= (float)randgen.get(1,10)/120.0f;
		if ( color[ncolor] < colorTrim ) color[ncolor] = colorTrim;
	}

	unsigned int runs = randgen.get(1, maxMutateRuns);
	brain.mutate( runs ); // 0 for random
}


void CritterB::calcCamPos()
{
	float reused = rotation * 0.0174532925f;
	cameraposition.x = position.x - (sin(reused) * (halfsize - 0.01f));
	cameraposition.z = position.z - (cos(reused) * (halfsize - 0.01f));
	cameraposition.y = position.y + 0.05f;
}

void CritterB::place()
{
	glViewport(framePosX, framePosY, retinasize, retinasize);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum( -0.05f, 0.05f, -0.05, 0.05, 0.1f, 5.0f);

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

 		float reused = rotation * 0.0174532925f;

		frustCullTriangle1.x += sin(reused) * 0.4f;
		frustCullTriangle1.z += cos(reused) * 0.4f;

		frustCullTriangle2.x -= sin(reused) * (sightrange+halfsize);
		frustCullTriangle2.z -= cos(reused) * (sightrange+halfsize);

		frustCullTriangle3 = frustCullTriangle2;

		reused = (270.0f+rotation) * 0.0174532925f;
		float sr = sightrange/2.0f;
		frustCullTriangle2.x -= sin(reused) * sr;
		frustCullTriangle2.z -= cos(reused) * sr;

		reused = (90.0f+rotation) * 0.0174532925f;
		frustCullTriangle3.x -= sin(reused) * sr;
		frustCullTriangle3.z -= cos(reused) * sr;

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
			{
				return true;
			}
		}
		return false;
	}

	void CritterB::moveForward()
	{
		moved = true;
		float reused = rotation * 0.0174532925f;
		newposition.x -= sin(reused) * speedfactor;
		newposition.z -= cos(reused) * speedfactor;
	}
	
	void CritterB::moveBackward()
	{
		moved = true;
		float reused = rotation * 0.0174532925f;
		newposition.x += sin(reused) * speedfactor;
		newposition.z += cos(reused) * speedfactor;
	}
	
	void CritterB::moveLeft()
	{
		moved = true;
		float reused = (90.0f+rotation) * 0.0174532925f;
		newposition.x -= sin(reused) * speedfactor;
		newposition.z -= cos(reused) * speedfactor;
	}
	
	void CritterB::moveRight()
	{
		moved = true;
		float reused = (270.0f+rotation) * 0.0174532925f;
		newposition.x -= sin(reused) * speedfactor;
		newposition.z -= cos(reused) * speedfactor;
	}

// Looking

	void CritterB::rotateLeft()
	{
		rotation += speedfactor*20.0f;
		if ( rotation > 360.0f ) rotation -= 360.0f;
		calcFrustrumTriangle();
		calcCamPos();
	}
	
	void CritterB::rotateRight()
	{
		rotation -= speedfactor*20.0f;
		if ( rotation < 0.0f ) rotation += 360.0f;
		calcFrustrumTriangle();
		calcCamPos();
	}

// LOAD critter

	void CritterB::loadCritterB(string &content)
	{
		string passToBrain;
		string line = parseH.returnUntillStrip( "\n", content );
		while ( !line.empty() )
		{
			// color=0.03,0.82,0.12,0;
				if ( parseH.beginMatchesStrip( "color=", line ) )
				{
					string R = parseH.returnUntillStrip( ",", line );
					string G = parseH.returnUntillStrip( ",", line );
					string B = parseH.returnUntillStrip( ",", line );
					string A = parseH.returnUntillStrip( ";", line );
		/*			cerr << "R: " << R  << endl;
					cerr << "G: " << G << endl;
					cerr << "B: " << B << endl;
					cerr << "A: " << A << endl;*/
	
					if(EOF == sscanf(R.c_str(), "%f", &color[0])) cerr << "ERROR INSERTING CRITTER" << endl;
					if(EOF == sscanf(G.c_str(), "%f", &color[1])) cerr << "ERROR INSERTING CRITTER" << endl;
					if(EOF == sscanf(B.c_str(), "%f", &color[2])) cerr << "ERROR INSERTING CRITTER" << endl;
					if(EOF == sscanf(A.c_str(), "%f", &color[3])) cerr << "ERROR INSERTING CRITTER" << endl;
				}
	
			// type=0;
				else if ( parseH.beginMatchesStrip( "type=", line ) )
				{
					string CTYPE = parseH.returnUntillStrip( ";", line );
					//cerr << "CTYPE: " << CTYPE << endl;
					if(EOF == sscanf(CTYPE.c_str(), "%d", &crittertype)) cerr << "ERROR INSERTING CRITTER" << endl;
				}

			// adamdist=690;
				else if ( parseH.beginMatchesStrip( "adamdist=", line ) )
				{
					string AD = parseH.returnUntillStrip( ";", line );
					//cerr << "AD: " << AD << endl;
					if(EOF == sscanf(AD.c_str(), "%d", &adamdist)) cerr << "ERROR INSERTING CRITTER" << endl;
				}
	
			// retinasize=9;
				else if ( parseH.beginMatchesStrip( "retinasize=", line ) )
				{
					string RES = parseH.returnUntillStrip( ";", line );
					//cerr << "RES: " << RES << endl;
					if(EOF == sscanf(RES.c_str(), "%d", &retinasize)) cerr << "ERROR INSERTING CRITTER" << endl;
				}

			// colorneurons=1;
				else if ( parseH.beginMatchesStrip( "colorneurons=", line ) )
				{
					string VD = parseH.returnUntillStrip( ";", line );
					//cerr << "AD: " << AD  << endl;
					if(EOF == sscanf(VD.c_str(), "%d", &colorNeurons)) cerr << "ERROR INSERTING CRITTER" << endl;
				}

			// the rest goes to the brain
				else //  if ( parseH.beginMatches( "n(", line ) )
				{
					passToBrain.append(line);
					passToBrain.append("\n");
				}
	
			line = parseH.returnUntillStrip( "\n", content );
		}

		brain.setArch(&passToBrain);
	}



	string CritterB::saveCritterB()
	{
		stringstream buf;
		buf << "color=" << color[0] << "," << color[1] << "," << color[2] << "," << color[3] << ";\n";
		buf << "type=" << crittertype << ";\n";
		buf << "adamdist=" << adamdist << ";\n";
		buf << "retinasize=" << retinasize << ";\n";
		buf << "colorneurons=" << colorNeurons << ";\n";

		string* arch = brain.getArch();
		buf << *arch;
		//cout << *arch << endl;

		return buf.str();
	}


CritterB::~CritterB()
{
}


