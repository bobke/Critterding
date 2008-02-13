#include "critter.h"

Critter::Critter()
{
	adamdist	= 0;
	// size & color
	maxSize		= 1.0f;
	size		= 0.1f;
	rotation	= 0.0f;
	resize(size);
	color[0]	= 1.0f;
	color[1]	= 0.0f;
	color[2]	= 0.0f;
	color[3]	= 0.0f;

	drawEvery	= 3;
	drawedAgo	= drawEvery;

	// initialize mutexes
	pthread_mutex_init (&position_mutex, NULL);

	// frame capturing options
	frameWidth		= 9;
	frameHeight		= frameWidth; // must be same as frameWidth
	components		= 4;
	items			= frameWidth * frameHeight * components;
	framePosX		= 0;
	framePosY		= 0;
	itemsPerRow		= 5;
	visionDivider		= 4;
	calcFramePos(0);

	// energy
	maxEnergyLevel		= 5000.0f;
	energyLevel		= maxEnergyLevel / 2.0f;

	// old age death
	totalFrames		= 0;
	maxtotalFrames		= 5000;

	procreateTimeCount	= 0;
	procreateTimeTrigger	= maxtotalFrames / 5;
	minprocenergyLevel	= maxEnergyLevel * 0.8f;

	// fire limits
	fireTimeCount		= 0;
	fireTimeTrigger		= 5;
	minfireenergyLevel	= maxEnergyLevel * 0.0f;

	eat			= false;
	touchingFood		= false;
	wasShot			= false;

	canFire			= false;
	fire			= false;

	canProcreate		= false;
	procreate		= false;

	brain.setupInputs( (items*visionDivider)+1+1+1+10 );
	brain.setupOutputs(9);

	// Allocate the neccessary memory.
	outputImage = (unsigned char*)malloc(items);

}

Critter::Critter(Critter &other)
{
	adamdist	= other.adamdist;

	// size & color
	maxSize		= other.maxSize;
	size		= other.size;
	rotation	= 0.0f;
	resize(size);
	color[0]	= other.color[0];
	color[1]	= other.color[1];
	color[2]	= other.color[2];
	color[3]	= other.color[3];

	drawEvery	= other.drawEvery;
	drawedAgo	= other.drawEvery;

	// initialize mutexes
	pthread_mutex_init (&position_mutex, NULL);

	// frame capturing options
	frameWidth		= other.frameWidth;
	frameHeight		= other.frameHeight; // must be same as frameWidth
	components		= 4;
	items			= frameWidth * frameHeight * components;
	framePosX		= 0;
	framePosY		= 0;
	itemsPerRow		= other.itemsPerRow;
	visionDivider		= other.visionDivider;
	calcFramePos(0);

	// energy
	maxEnergyLevel		= other.maxEnergyLevel;
	energyLevel		= other.energyLevel;

	// old age death
	totalFrames		= 0;
	maxtotalFrames		= other.maxtotalFrames;

	procreateTimeCount	= 0;
	procreateTimeTrigger	= other.procreateTimeTrigger;
	minprocenergyLevel	= other.minprocenergyLevel;

	// fire limits
	fireTimeCount		= 0;
	fireTimeTrigger		= other.fireTimeTrigger;
	minfireenergyLevel	= other.minfireenergyLevel;

	eat			= false;
	touchingFood		= false;
	wasShot			= false;

	canFire			= false;
	fire			= false;

	canProcreate		= false;
	procreate		= false;

	brain.setupInputs( (items*visionDivider)+1+1+1+10 );
	brain.setupOutputs(9);

	// Allocate the neccessary memory.
	outputImage = (unsigned char*)malloc(items);

	string arch = other.saveCritter();
	loadCritter(arch);
}

void Critter::process()
{
	// increase counters
		totalFrames++;
		procreateTimeCount++;
		fireTimeCount++;

	// reset motor bools
		eat		= false;
		fire		= false;
		procreate	= false;

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
		energyUsed = 0.0f;

		energyUsed += (float)brain.neuronsfired	* size;
		energyUsed += (float)motorneuronsfired	* volume;

	// apply energy usage
	energyLevel -= energyUsed;
}

void Critter::procInputNeurons()
{
	// link vision array directly to the sensor neurons' output
		if ( visionDivider == 1 )
		{
			for ( unsigned int i=0; i < items; i++ )
			{
				if ( outputImage[i] )	brain.Inputs[i]->output = 1;
				else			brain.Inputs[i]->output = 0;
			}
		}
		else
		{
			for ( unsigned int i=0; i < items; i++ )
			{
				unsigned target = i * visionDivider;
				unsigned int NeuronToFire = (unsigned int)(((float)outputImage[i] / 256.0f) * (float)visionDivider);
				for ( unsigned int z=0; z < visionDivider; z++ )
				{
					if ( outputImage[i] && z == NeuronToFire  )	brain.Inputs[target+z]->output = 1;
					else						brain.Inputs[target+z]->output = 0;
				}
			}
		}

	unsigned int overstep = items*visionDivider;

	// over food sensor neuron
		if ( touchingFood )	brain.Inputs[overstep]->output = 1;
		else			brain.Inputs[overstep]->output = 0;

	overstep++;

	// can fire a bullet
		canFire		= false;
		if ( fireTimeCount > fireTimeTrigger && energyLevel > minfireenergyLevel )
		{
			brain.Inputs[overstep]->output = 1;
			canFire = true;
		}
		else brain.Inputs[overstep]->output = 0;

	overstep++;

	// can procreate sensor neuron
		canProcreate	= false;
		if ( procreateTimeCount > procreateTimeTrigger && energyLevel > minprocenergyLevel )
		{
			brain.Inputs[overstep]->output = 1;
			canProcreate = true;
		}
		else brain.Inputs[overstep]->output = 0;

	overstep++;

		// over energy neurons
		unsigned int NeuronToFire = (int)((energyLevel / maxEnergyLevel) * 10) + overstep;
		unsigned int count = 10 + overstep;
		while ( overstep < count )
		{
			if ( overstep == NeuronToFire )	brain.Inputs[overstep]->output = 1;
			else 				brain.Inputs[overstep]->output = 0;
			overstep++;
		}

	// debugging check
/*	if ( overstep != brain.Inputs.size() )
	{
		cerr << overstep << " does not equal " << brain.Inputs.size()-1 << endl;
		exit(0);
	}*/
}

void Critter::procOutputNeurons()
{

	motorneuronsfired = 0;

	// there are 9 motor neurons

	if ( brain.Outputs[0]->output > 0 )
	{
		moveForward();
		motorneuronsfired++;
	}

	if ( brain.Outputs[1]->output > 0 )
	{
		moveBackward();
		motorneuronsfired++;
	}

	if ( brain.Outputs[2]->output > 0 )
	{
		moveLeft();
		motorneuronsfired++;
	}

	if ( brain.Outputs[3]->output > 0 )
	{
		moveRight();
		motorneuronsfired++;
	}

	if ( brain.Outputs[4]->output > 0 )
	{
		rotateLeft();
		motorneuronsfired++;
	}

	if ( brain.Outputs[5]->output > 0 )
	{
		rotateRight();
		motorneuronsfired++;
	}

	if ( brain.Outputs[6]->output > 0 )
	{
		eat = true;
		motorneuronsfired++;
	}

	if ( brain.Outputs[7]->output > 0 )
	{
		fire = true;
		motorneuronsfired++;
	}

	if ( brain.Outputs[8]->output > 0 )
	{
		procreate = true;
		motorneuronsfired++;
	}

}

void Critter::procFrame()
{
	// Clear the variable.
	// done in world now
	//memset(outputImage, 0, items);

	// read from front buffer
//	glReadBuffer(GL_FRONT);
	
	glReadPixels(framePosX, framePosY, frameWidth, frameHeight, GL_RGBA, GL_UNSIGNED_BYTE, outputImage);
}

void Critter::setup()
{
	brain.setupArchitecture();

	// resize by brain architecture properties
	float newsize = ((maxSize/2) / brain.absmaxneurons) * brain.totalneurons + (((maxSize/2)/(brain.absmaxneurons*brain.absmaxconns))*brain.totalconnections);
	resize(newsize);

	volume		= size * size * size * 100.0f;

	speedfactor	= (maxSize-size) / 10.0f; // FIXME HACK lower me :)
//	speedfactor	= 100.0f / (volume*10000.0f);

// 	maxEnergyLevel	= 50000.0f * size;
//	maxtotalFrames	= 50000.0f * size;

}

void Critter::mutate()
{
	adamdist++;

	// mutate color
	unsigned int mode = randgen.get(1,2);

	unsigned int ncolor = randgen.get(0,2);
	if ( mode == 1 )
	{
		color[ncolor] += (float)randgen.get(1,3)/100.0f;
		if ( color[ncolor] > 1.0f ) color[ncolor] = 1.0f;
	}
	else
	{
		color[ncolor] -= (float)randgen.get(1,3)/100.0f;
		if ( color[ncolor] < 0.0f ) color[ncolor] = 0.0f;
	}

	brain.mutate();
}


void Critter::calcCamPos()
{
	float reused = rotation * 0.0174532925f;
	cameraposition.x = position.x - (sin(reused) * (halfsize - 0.01));
	cameraposition.z = position.z - (cos(reused) * (halfsize - 0.01));
	cameraposition.y = position.y + 0.05f;
}

void Critter::place()
{
	glViewport(framePosX, framePosY, frameWidth, frameHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum( -0.05f, 0.05f, -0.05, 0.05, 0.1f, 10.0f);

	glRotatef(rotation, 0.0f, -1.0f, 0.0f);
	glTranslatef(-cameraposition.x, -cameraposition.y, -cameraposition.z);

//	glMatrixMode(GL_MODELVIEW);
}

void Critter::calcFramePos(unsigned int pos)
{
	framePosY = 0;
	while ( pos >= itemsPerRow )
	{
		pos -= itemsPerRow;
		framePosY += frameHeight;
	}
	framePosX = (pos * frameWidth) + pos;
}

void Critter::printVision()
{
	int rowlength = frameWidth * components;

	cerr << rowlength << " " << items << endl;
	for ( int h=items-rowlength; h >= 0; h -= rowlength )
	{
		for ( int w=h; w < (int)(frameWidth*components)+h; w += components )
		{
			if ( (int)outputImage[w+2] ) cerr << "\033[1;31mR\033[0m";
			else cerr << ".";
			if ( (int)outputImage[w+1] ) cerr << "\033[1;32mG\033[0m";
			else cerr << ".";
			if ( (int)outputImage[w] ) cerr << "\033[1;34mB\033[0m";
			else cerr << ".";
			if ( (int)outputImage[w+3] ) cerr << "\033[1;35mA\033[0m";
			else cerr << ".";
		}
		cerr << "" << endl;
	}
	cerr << "" << endl;
}

void Critter::draw()
{
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	
	glPushMatrix();

		//pthread_mutex_lock( &position_mutex );
			glTranslatef( position.x, position.y, position.z );
		//pthread_mutex_unlock( &position_mutex );

		glRotatef( rotation, 0.0, 1.0, 0.0 );

		glColor4f( color[0], color[1], color[2], color[3] );
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);

 		glColor4f( 1.0f, 1.0f, 1.0f, 0.0f );
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, tindices);

	glPopMatrix();
}

void Critter::resize(float newsize)
{
	size		= newsize;
	halfsize	= (newsize / 2.0f);

	// change position according to height
	position.y	= halfsize;

	// left plane
	vertices[0] = -halfsize; vertices[1] = halfsize; vertices[2] = halfsize;
	vertices[3] = -halfsize; vertices[4] = -halfsize; vertices[5] = halfsize;
	vertices[6] = -halfsize; vertices[7] = -halfsize; vertices[8] = -halfsize;
	vertices[9] = -halfsize; vertices[10] = halfsize; vertices[11] = -halfsize;

	// right plane
	vertices[12] = halfsize; vertices[13] = halfsize; vertices[14] = halfsize;
	vertices[15] = halfsize; vertices[16] = -halfsize; vertices[17] = halfsize;
	vertices[18] = halfsize; vertices[19] = -halfsize; vertices[20] = -halfsize;
	vertices[21] = halfsize; vertices[22] = halfsize; vertices[23] = -halfsize;

	indices[0] = 0; indices[1] = 3; indices[2] = 7; indices[3] = 4;
	indices[4] = 1; indices[5] = 2; indices[6] = 6; indices[7] = 5;
	indices[8] = 2; indices[9] = 3; indices[10] = 7; indices[11] = 6;
	indices[12] = 1; indices[13] = 0; indices[14] = 4; indices[15] = 5;
	indices[16] = 1; indices[17] = 2; indices[18] = 3; indices[19] = 0;
	indices[20] = 5; indices[21] = 6; indices[22] = 7; indices[23] = 4;

	// nose
	vertices[24] = 0; vertices[25] = halfsize; vertices[26] = -halfsize*1.3f;

	tindices[0] = 3; tindices[1] = 7; tindices[2] = 8;

	calcCamPos();
}


// Moving

	void Critter::prepNewPoss()
	{
		moved = false;
		newposition = position;
	}

	void Critter::moveToNewPoss()
	{
		position = newposition;
		calcCamPos();
	}

	void Critter::moveForward()
	{
		moved = true;
		float reused = rotation * 0.0174532925f;
		newposition.x -= sin(reused) * speedfactor;
		newposition.z -= cos(reused) * speedfactor;
	}
	
	void Critter::moveBackward()
	{
		moved = true;
		float reused = rotation * 0.0174532925f;
		newposition.x += sin(reused) * speedfactor;
		newposition.z += cos(reused) * speedfactor;
	}
	
	void Critter::moveLeft()
	{
		moved = true;
		float reused = (90.0f+rotation) * 0.0174532925f;
		newposition.x -= sin(reused) * speedfactor;
		newposition.z -= cos(reused) * speedfactor;
	}
	
	void Critter::moveRight()
	{
		moved = true;
		float reused = (270.0f+rotation) * 0.0174532925f;
		newposition.x -= sin(reused) * speedfactor;
		newposition.z -= cos(reused) * speedfactor;
	}

// Looking

	void Critter::rotateLeft()
	{
		rotation += speedfactor*20.0f;
		calcCamPos();
	}
	
	void Critter::rotateRight()
	{
		rotation -= speedfactor*20.0f;
		calcCamPos();
	}

// LOAD critter

	void Critter::loadCritter(string &content)
	{
		string line = parseH.returnUntillStrip( "\n", content );
		string passToBrain;
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
	
			// visionres=9;
				else if ( parseH.beginMatchesStrip( "visionres=", line ) )
				{
					string RES = parseH.returnUntillStrip( ";", line );
					//cerr << "RES: " << RES  << endl;
					if(EOF == sscanf(RES.c_str(), "%d", &frameWidth)) cerr << "ERROR INSERTING CRITTER" << endl;
					if(EOF == sscanf(RES.c_str(), "%d", &frameHeight)) cerr << "ERROR INSERTING CRITTER" << endl;
				}
	
			// adamdist=690;
				else if ( parseH.beginMatchesStrip( "adamdist=", line ) )
				{
					string AD = parseH.returnUntillStrip( ";", line );
					//cerr << "AD: " << AD  << endl;
					if(EOF == sscanf(AD.c_str(), "%d", &adamdist)) cerr << "ERROR INSERTING CRITTER" << endl;
				}

			// drawevery=1;
				else if ( parseH.beginMatchesStrip( "drawevery=", line ) )
				{
					string DE = parseH.returnUntillStrip( ";", line );
					//cerr << "AD: " << AD  << endl;
					if(EOF == sscanf(DE.c_str(), "%d", &drawEvery)) cerr << "ERROR INSERTING CRITTER" << endl;
				}

			// visiondivider=1;
				else if ( parseH.beginMatchesStrip( "visiondivider=", line ) )
				{
					string VD = parseH.returnUntillStrip( ";", line );
					//cerr << "AD: " << AD  << endl;
					if(EOF == sscanf(VD.c_str(), "%d", &visionDivider)) cerr << "ERROR INSERTING CRITTER" << endl;
				}

			// neuron(ft=24|iwr=20|mtr=4|inputs(|s,78,6|s,186,-12|s,123,10|n,19,5|n,3,3|n,11,-19));
				else if ( parseH.beginMatches( "neuron(", line ) )
				{
					passToBrain.append(line);
					passToBrain.append("\n");
					//line.clear();
				}
	
			line = parseH.returnUntillStrip( "\n", content );
		}
		brain.setArch(passToBrain);
	}

	string Critter::saveCritter()
	{
		stringstream buf;
		buf << "color=" << color[0] << "," << color[1] << "," << color[2] << "," << color[3] << ";\n";
		buf << "visionres=" << frameWidth << ";\n";
		buf << "adamdist=" << adamdist << ";\n";
		buf << "drawevery=" << drawEvery << ";\n";
		buf << "visiondivider=" << visionDivider << ";\n";

		buf << brain.getArch();

		return buf.str();
	}


Critter::~Critter()
{
	free(outputImage);
}


