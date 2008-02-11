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
	energyUsed		= 0.0f;

	// old age death
	totalFrames		= 0;
	maxtotalFrames		= 3000;

	procreateTimeCount	= 0;
	procreateTimeTrigger	= maxtotalFrames / 5;
	minprocenergyLevel	= maxEnergyLevel * 0.8f;

	// fire limits
	fireTimeCount		= 0;
	fireTimeTrigger		= 5;
	minfireenergyLevel	= maxEnergyLevel * 0.0f;

	// neural properties
	percentSensoryConns	= 20;
	percentMotor		= 20;

	absmaxneurons		= 150;
	absmaxconns		= 150;

	minneurons		= 20;
	maxneurons		= randgen.get( minneurons, absmaxneurons );

	minconns		= 1;
	maxconns		= randgen.get( minconns, absmaxconns );

	totalneurons		= 0;
	totalconnections	= 0;

	mutatepercent		= 3;

	eat			= false;
	touchingFood		= false;
	wasShot			= false;

	canFire			= false;
	fire			= false;

	canProcreate		= false;
	procreate		= false;

	setupSensors();

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
	energyUsed		= 0.0f;

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

	// neural properties
	percentSensoryConns	= other.percentSensoryConns;
	percentMotor		= other.percentMotor;

	absmaxneurons		= other.absmaxneurons;
	absmaxconns		= other.absmaxconns;

	minneurons		= other.minneurons;
	maxneurons		= other.maxneurons;

	minconns		= other.minconns;
	maxconns		= other.maxconns;

	totalneurons		= 0;
	totalconnections	= 0;

	mutatepercent		= other.mutatepercent;

	eat			= false;
	touchingFood		= false;
	wasShot			= false;

	canFire			= false;
	fire			= false;

	canProcreate		= false;
	procreate		= false;

	setupSensors();

	// Allocate the neccessary memory.
	outputImage = (unsigned char*)malloc(items);

	string arch = other.getArch();
	setArch(arch);
}

void Critter::process()
{
	// increase counters
	totalFrames++;
	procreateTimeCount++;
	fireTimeCount++;

	// energy used
	energyUsed = 0.0f;

	// reset extern motor neurons
	eat		= false;
	fire		= false;
	procreate	= false;

	wasShot		= false;

	prepNewPoss();
	procSensorNeurons();
	procNeurons();

//	for ( unsigned int i=0; i < 300; i++ ) procNeurons();
}

void Critter::setup()
{
	setupArchitecture();
	resizeByArch();
}

void Critter::setupSensors()
{
	SensorNeurons.clear();

	// Vision Sensors
	for ( unsigned int i=0; i < (items*visionDivider); i++ )
	{
		SensorNeurons.push_back( new NeuronSensor );
	}

	// is over food sensor neuron, it doesn't even need to know what or where it is, it should find it, it should learn to use it
	SensorNeurons.push_back( new NeuronSensor );

	// ready to fire a bullet neuron
	SensorNeurons.push_back( new NeuronSensor );

	// ready to procreate neuron
	SensorNeurons.push_back( new NeuronSensor );

	// a couple of energy status neurons
	for ( unsigned int i=0; i < 10; i++ )
	{
		SensorNeurons.push_back( new NeuronSensor );
	}
}

void Critter::procSensorNeurons()
{
	// link vision array directly to the sensor neurons' output

	if ( visionDivider == 1 )
	{
		for ( unsigned int i=0; i < items; i++ )
		{
			if ( outputImage[i] ) SensorNeurons[i]->output = 1;
			else  SensorNeurons[i]->output = 0;
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
				if ( outputImage[i] && z == NeuronToFire  ) SensorNeurons[target+z]->output = 1;
				else SensorNeurons[target+z]->output = 0;
			}
		}
	}

	// over food sensor neuron
	unsigned int overstep = items*visionDivider;
	if ( touchingFood ) SensorNeurons[overstep]->output = 1;
	else SensorNeurons[overstep]->output = 0;

	// can fire a bullet
	overstep++;
	canFire		= false;
	if ( fireTimeCount > fireTimeTrigger && energyLevel > minfireenergyLevel )
	{
		SensorNeurons[overstep]->output = 1;
		canFire = true;
	}
	else SensorNeurons[overstep]->output = 0;

	// can procreate sensor neuron
	overstep++;
	canProcreate	= false;
	if ( procreateTimeCount > procreateTimeTrigger && energyLevel > minprocenergyLevel )
	{
		SensorNeurons[overstep]->output = 1;
		canProcreate = true;
	}
	else SensorNeurons[overstep]->output = 0;

	// over energy neurons
	overstep++;
	unsigned int NeuronToFire = (int)((energyLevel / maxEnergyLevel) * 10) + overstep;
	unsigned int count = 10 + overstep;
	for ( unsigned int i = overstep; i < count; i++ )
	{
		if ( i == NeuronToFire ) SensorNeurons[i]->output = 1;
		else SensorNeurons[i]->output = 0;
	}
}

void Critter::procNeurons()
{
	unsigned int nsize = Neurons.size();
	for ( unsigned int i=0; i < nsize; i++ )
	{
		Neurons[i]->process();

		// if neuron fires
		if ( Neurons[i]->waitoutput != 0 )
		{
			// decrease energy
			//energyLevel -= volume;
			float cost = 1.0f;
			energyLevel	-= cost;
			energyUsed	+= cost;

			// motor neuron check & exec
			if ( Neurons[i]->isMotor )
			{
				float cost = volume;

				// decrease energy again
				energyLevel	-= cost;
				energyUsed	+= cost;

				// exec motor func
				switch ( Neurons[i]->MotorFunc )
				{
					case 0:
						moveForward();
						break;
					case 1:
						moveBackward();
						break;
					case 2:
						moveLeft();
						break;
					case 3:
						moveRight();
						break;
					case 4:
						rotateLeft();
						break;
					case 5:
						rotateRight();
						break;
					case 6:
						eat = true;
						break;
					case 7:
						fire = true;
						break;
					case 8:
						procreate = true;
						break;
				}
			}
		}
	}

	// commit outputs at the end
	for ( unsigned int i=0; i < Neurons.size(); i++ ) Neurons[i]->output = Neurons[i]->waitoutput;
}

void Critter::setupArchitecture()
{
	Neurons.clear();

	// first create all neurons
	for ( unsigned int i=0; i < NeuronArch.size(); i++ )
	{
		NeuronInter *n = new NeuronInter;
		n->fireThresh	= NeuronArch[i]->fireThresh;
		n->iWeightRange	= NeuronArch[i]->iWeightRange;
		n->isMotor	= NeuronArch[i]->isMotor;
		n->MotorFunc	= NeuronArch[i]->MotorFunc;
		Neurons.push_back( n );
	}

	for ( unsigned int i=0; i < NeuronArch.size(); i++ )
	{
		for ( unsigned int j=0; j < NeuronArch[i]->connections.size(); j++ )
		{
			if ( NeuronArch[i]->connections[j]->type == 'n' )
			{
				Neurons[i]->connec( &Neurons[ NeuronArch[i]->connections[j]->id ]->output, NeuronArch[i]->connections[j]->weight );
			}
			else if ( NeuronArch[i]->connections[j]->type == 's' )
			{
				Neurons[i]->connec( &SensorNeurons[ NeuronArch[i]->connections[j]->id ]->output, NeuronArch[i]->connections[j]->weight );
			}
		}
	}
}

void Critter::resizeByArch()
{
	doNeuronConnCount();

	float newsize = ((maxSize/2) / absmaxneurons) * totalneurons + (((maxSize/2)/(absmaxneurons*absmaxconns))*totalconnections);

	resize(newsize);
}

void Critter::doNeuronConnCount()
{
	totalneurons		= NeuronArch.size();
	totalconnections	= 0;
	for ( unsigned int i = 0; i < totalneurons; i++ ) totalconnections += NeuronArch[i]->connections.size();
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

void Critter::randomArchitecture()
{
	NeuronArch.clear();

	// random amount of neurons
	unsigned int nAmount = randgen.get( minneurons, maxneurons );

	// create the neurons
	for ( unsigned i = 0; i < nAmount; i++ )
	{
		addRandomArchNeuron();
	}

	// link the neurons
	for ( unsigned i = 0; i < nAmount; i++ )
	{
		// random amount of connections
		unsigned int cAmount = randgen.get( minconns, maxconns );
		for ( unsigned j = 0; j < cAmount; j++ )
		{
			addRandomArchConnection(i);
		}
	}

}

unsigned int Critter::addRandomArchNeuron()
{
	unsigned int ThreshMin = 10;
	unsigned int ThreshMax = 100;
	unsigned int MaxWeightRange = 20;

	ArchNeuron *n = new ArchNeuron;
	n->fireThresh	= randgen.get( ThreshMin, ThreshMax );
	n->iWeightRange	= randgen.get( 1, MaxWeightRange );
	n->isMotor = false;

	if ( randgen.get( 1, 100 ) <= percentMotor )
	{
		n->isMotor = true;
		n->MotorFunc = randgen.get( 0, 8 );
	}

	NeuronArch.push_back( n );
 	return (NeuronArch.size()-1);
}

unsigned int Critter::addRandomArchConnection(unsigned int parentneuron)
{
	ArchConnection *c = new ArchConnection;

	// type
	c->type = 'n';
	if ( randgen.get( 1, 100 ) <= percentSensoryConns ) c->type = 's';

	// id
	if ( c->type == 's' ) c->id = randgen.get( 0, SensorNeurons.size()-1 );
	else if ( c->type == 'n' )
	{
		c->id = randgen.get( 0, NeuronArch.size()-1 );
		while ( c->id == parentneuron )
		{
			c->id = randgen.get( 0, NeuronArch.size()-1 );
		}
	}
	else exit(0);

	// weight
	c->weight = randgen.get( 1, NeuronArch[parentneuron]->iWeightRange );

//	cerr << NeuronArch[parentneuron].iWeightRange << "  > " << c.weight << endl;

	// reverse 1 in 2;
	if ( randgen.get(1,2)==1 ) c->weight = (c->weight * -1);

	NeuronArch[parentneuron]->connections.push_back( c );
 	return (NeuronArch[parentneuron]->connections.size()-1);
}

void Critter::mutate()
{
	adamdist++;

	doNeuronConnCount();
	unsigned int runs = randgen.get(1, (int)(totalconnections/(100/mutatepercent)));

//	cerr << " N: " << totalneurons << " C: " << totalconnections;

	for ( unsigned int i=0; i < runs; i++ )
	{
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

		mode = randgen.get(1,30);

		// add a new neuron
			if ( mode == 1 )
			{
				if ( NeuronArch.size() < absmaxneurons )
				{
					//cerr << "\t+N " << nid << endl;
					unsigned int nid = addRandomArchNeuron();

					// random amount of connections
					unsigned int cAmount = randgen.get( minconns, maxconns );
					for ( unsigned j = 0; j < cAmount; j++ )
					{
						addRandomArchConnection(nid);
					}
				}
			}

		// remove a neuron
			else if ( mode == 2 )
			{
				// don't go under minimum neurons
				//if ( NeuronArch.size() > minneurons )
				//{
					// pick a random neuron
					unsigned int nid = randgen.get( 0, NeuronArch.size()-1 );
					//cerr << "\t-N " << nid << endl;

					// first remove all connections to this neuron, FIXME remove neuron too if no connections are left
					for ( unsigned int i=0; i < NeuronArch.size(); i++ )
					{
						for ( unsigned int j=0; j < NeuronArch[i]->connections.size(); j++ )
						{
							if ( NeuronArch[i]->connections[j]->type == 'n' )
							{
								if ( NeuronArch[i]->connections[j]->id == nid )
								{
									delete NeuronArch[i]->connections[j];
									NeuronArch[i]->connections.erase(NeuronArch[i]->connections.begin()+j);
									j--;
								}
								// if higher id drop one
								else if ( NeuronArch[i]->connections[j]->id > nid )
								{
									NeuronArch[i]->connections[j]->id--;
								}
							}
						}
					}

					// remove the neuron itself, and all its connections
//					for ( unsigned int c=0; c < NeuronArch[nid]->connections.size(); c++ ) delete NeuronArch[nid]->connections[c];
					delete NeuronArch[nid];
					NeuronArch.erase(NeuronArch.begin()+nid);
				//}
			}

		// do something to a random input
			else
			{
				// pick a random neuron
				unsigned int nid = randgen.get( 0, NeuronArch.size()-1 );

				unsigned int imode = randgen.get(1,2);

				// add a new connection
				if ( imode == 1 )
				{
					// don't go over maximum connections
					if ( NeuronArch[nid]->connections.size() < absmaxconns )
					{
						//cerr << "\t+C " << nid << endl;
						addRandomArchConnection(nid);
					}
				}
				// remove a random connection
				else
				{
					// don't go under minimum connections
					if ( NeuronArch[nid]->connections.size() > minconns )
					{
						//cerr << "\t-C " << nid << endl;
						unsigned int connid = randgen.get(0, NeuronArch[nid]->connections.size()-1);
						delete NeuronArch[nid]->connections[connid];
						NeuronArch[nid]->connections.erase(NeuronArch[nid]->connections.begin()+connid);
					}
				}

			}

	}
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

		glTranslatef( position.x, position.y, position.z );
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

	volume		= size * size * size * 100.0f;

	speedfactor	= (maxSize-size) / 10.0f; // FIXME HACK lower me :)
//	speedfactor	= 100.0f / (volume*10000.0f);

// 	maxEnergyLevel	= 50000.0f * size;
//	maxtotalFrames	= 50000.0f * size;

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

	void Critter::setArch(string &content)
	{
	
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
	
			// neuron(ft=24|iwr=20|mtr=4|inputs(|s,78,6|s,186,-12|s,123,10|n,19,5|n,3,3|n,11,-19));
				else if ( parseH.beginMatchesStrip( "neuron(", line ) )
				{
					ArchNeuron *n = new ArchNeuron;
					NeuronArch.push_back( n );
					unsigned int nid = (NeuronArch.size()-1);
	
					if ( parseH.beginMatchesStrip( "ft=", line ) )
					{
						string FT = parseH.returnUntillStrip( "|", line );
						//cerr << "FT: " << FT  << endl;
						if(EOF == sscanf(FT.c_str(), "%d", &NeuronArch[nid]->fireThresh)) cerr << "ERROR INSERTING CRITTER" << endl;
					}
	
					if ( parseH.beginMatchesStrip( "iwr=", line ) )
					{
						string IWR = parseH.returnUntillStrip( "|", line );
						//cerr << "IWR: " << IWR  << endl;
						if(EOF == sscanf(IWR.c_str(), "%d", &NeuronArch[nid]->iWeightRange)) cerr << "ERROR INSERTING CRITTER" << endl;
					}
	
					if ( parseH.beginMatchesStrip( "mtr=", line ) )
					{
						string MTR = parseH.returnUntillStrip( "|", line );
						//cerr << "MTR: " << MTR  << endl;
						if(EOF == sscanf(MTR.c_str(), "%d", &NeuronArch[nid]->MotorFunc)) cerr << "ERROR INSERTING CRITTER" << endl;
						NeuronArch[nid]->isMotor = true;
					}
	
					if ( parseH.beginMatchesStrip( "inputs(|", line ) )
					{
						string INPUTS = parseH.returnUntillStrip( ")", line );
						INPUTS.append("|");
						//cerr << "INPUTS: " << INPUTS  << endl;
	
						string inp = parseH.returnUntillStrip( "|", INPUTS );
						while ( !inp.empty() )
						{
							ArchConnection *c = new ArchConnection;
							NeuronArch[nid]->connections.push_back( c );
							unsigned int cid = (NeuronArch[nid]->connections.size()-1);
	
	
							string TYPE = parseH.returnUntillStrip( ",", inp );
							string ID = parseH.returnUntillStrip( ",", inp );
							string WEIGHT = inp;
	// 						cerr << "TYPE: " << TYPE  << endl;
	// 						cerr << "ID: " << ID << endl;
	// 						cerr << "WEIGHT: " << WEIGHT << endl;
							if(EOF == sscanf(TYPE.c_str(), "%c", &NeuronArch[nid]->connections[cid]->type)) cerr << "ERROR INSERTING CRITTER" << endl;
							if(EOF == sscanf(ID.c_str(), "%d", &NeuronArch[nid]->connections[cid]->id)) cerr << "ERROR INSERTING CRITTER" << endl;
							if(EOF == sscanf(WEIGHT.c_str(), "%d", &NeuronArch[nid]->connections[cid]->weight)) cerr << "ERROR INSERTING CRITTER" << endl;
	
							inp = parseH.returnUntillStrip( "|", INPUTS );
						}
					}
				}
	
			line = parseH.returnUntillStrip( "\n", content );
		}
	}

	string Critter::getArch()
	{
		stringstream buf;
		buf << "color=" << color[0] << "," << color[1] << "," << color[2] << "," << color[3] << ";\n";
		buf << "visionres=" << frameWidth << ";\n";
		buf << "adamdist=" << adamdist << ";\n";
	
		// neuronal arch & connections
		for ( unsigned int i = 0; i < NeuronArch.size(); i++ )
		{
			// neuron info
			buf << "neuron(";
			buf << "ft=" << NeuronArch[i]->fireThresh;
			buf << "|iwr=" << NeuronArch[i]->iWeightRange;
			if ( NeuronArch[i]->isMotor ) buf << "|mtr=" << NeuronArch[i]->MotorFunc;
	
			// inputs
			buf << "|inputs(";
			for ( unsigned int j = 0; j < NeuronArch[i]->connections.size(); j++ )
			{
				buf << "|" << NeuronArch[i]->connections[j]->type << "," << NeuronArch[i]->connections[j]->id << "," << NeuronArch[i]->connections[j]->weight;
			}
			buf << "));\n";
		}

		return buf.str();
	}


Critter::~Critter()
{
	free(outputImage);
	for ( unsigned int i=0; i < NeuronArch.size(); i++ )	delete NeuronArch[i];
	for ( unsigned int i=0; i < SensorNeurons.size(); i++ )	delete SensorNeurons[i];
	for ( unsigned int i=0; i < Neurons.size(); i++ )	delete Neurons[i];
}


