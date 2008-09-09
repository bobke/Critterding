#include "critterb.h"

// todo : include mutation % (from world)

void CritterB::initConst()
{
	// FIXME to new naming convention
	speedfactor		= 0.0f;
	size			= 0.0f;
	halfsize		= 0.0f;
	colorNeurons		= 0;
	maxtotalFrames		= 0;
	maxEnergyLevel		= 0.0f;

	procreateTimeTrigger	= 0;
	fireTimeTrigger		= 0;

	visionPosition		= 0;
	retinasperrow		= 0;
	retinaColumnStart	= 0;
	retinaRowStart		= 0;
	retinaRowLength		= 0;

	components		= 4;
	colorDivider		= 0;
	retinasize		= 0;

	colorTrim		= 0.25f;
}

CritterB::CritterB()
{
	initConst();

	// frame capturing options
	adamdist		= 0;

	// give it a random color
	color[0] = (float)randgen.get( 20,100 ) / 100.0f;
	color[1] = (float)randgen.get( 20,100 ) / 100.0f;
	color[2] = (float)randgen.get( 20,100 ) / 100.0f;
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

	string arch = other.saveCritterB();
	loadCritterB(arch);

	items = retinasize * retinasize * components;

	// energy
	energyLevel		= other.energyLevel;
}


void CritterB::calcInputOutputNeurons()
{
	items = retinasize * retinasize * components;

	brain.numberOfInputs = (items*colorNeurons)+1+1+1+10+1;
	brain.numberOfOutputs = 9;
}

void CritterB::setup()
{
	totalFrames		= 0;
	procreateTimeCount	= 0;
	fireTimeCount		= 0;

	colorDivider		= 256 / colorNeurons;

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

	// link vision array directly to the sensor neurons' output
/*		if ( colorNeurons == 1 )
		{
			for ( unsigned int i=0; i < items; i++ )
			{
				if ( retina[i]>0 ) brain.Inputs[i].output = 1;
			}
		}
		else
		{*/

//see what it sees
// 			for ( unsigned int h=retinaRowStart; h < retinaRowStart+(retinasize*retinaRowLength); h += retinaRowLength )
// 			{
// 				for ( unsigned int w=h+retinaColumnStart; w < h+retinaColumnStart+((retinasize)*components); w+=components )
// 				{
// 					if ( (int)retina[w] ) cerr << "\033[1;31mR\033[0m";
// 					else cerr << ".";
// 					if ( (int)retina[w+1] ) cerr << "\033[1;32mG\033[0m";
// 					else cerr << ".";
// 					if ( (int)retina[w+2] ) cerr << "\033[1;34mB\033[0m";
// 					else cerr << ".";
// 					if ( (int)retina[w+3] ) cerr << "\033[1;35mA\033[0m";
// 					else cerr << ".";
// 				}
// 				cerr << "" << endl;
// 			}
// 			cerr << "" << endl;
// 			usleep (10000);

			unsigned int i=0;
			for ( unsigned int h=retinaRowStart; h < retinaRowStart+(retinasize*retinaRowLength); h += retinaRowLength )
			{
				for ( unsigned int w=h+retinaColumnStart; w < h+retinaColumnStart+((retinasize)*components); w++ )
				{
					unsigned itarget = i * colorNeurons;

					if ( retina[w]>0 )
					{
						brain.Inputs[itarget+ ((unsigned int)retina[w] / colorDivider)].output = 1;
					}
					i++;
				}
			}

// 		}

	unsigned int overstep = items*colorNeurons;

	// over food sensor neuron
		if ( touchingFood )	brain.Inputs[overstep].output = 1;
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

	// over energy neurons
		unsigned int NeuronToFire = (int)((energyLevel / maxEnergyLevel) * 10) + overstep;
		unsigned int count = 10 + overstep;
		while ( overstep < count )
		{
			if ( overstep <= NeuronToFire )	brain.Inputs[overstep].output = 1; // !!! <=
			else 				brain.Inputs[overstep].output = 0;
			overstep++;
		}

	// the always firing neuron
		brain.Inputs[overstep].output = 1;

	// debugging check
//		if ( overstep != brain.Inputs.size()-1 )
//		{
//			cerr << overstep << " does not equal " << brain.Inputs.size()-1 << endl;
//			exit(0);
//		}
}

void CritterB::procOutputNeurons()
{
	motorneuronsfired = 0;

	// there are 9 motor neurons

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

}

void CritterB::mutate(unsigned int maxMutateRuns)
{
	adamdist++;

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
	cameraposition.x = position.x - (sin(reused) * (halfsize - 0.01));
	cameraposition.z = position.z - (cos(reused) * (halfsize - 0.01));
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

void CritterB::draw()
{
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	
	glPushMatrix();

		//pthread_mutex_lock( &position_mutex );
			glTranslatef( position.x, position.y, position.z );
		//pthread_mutex_unlock( &position_mutex );

		glRotatef( rotation, 0.0, 1.0, 0.0 );

		glColor4f( color[0], color[1], color[2], color[3] );
		glDrawElements(GL_QUADS, 20, GL_UNSIGNED_BYTE, indices);

 		glColor4f( 1.0f, 1.0f, 1.0f, 0.0f );
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, tindices);

	glPopMatrix();
}

void CritterB::resize(float newsize)
{
	size		= newsize;
	halfsize	= (newsize / 2.0f);

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
	indices[4] = 2; indices[5] = 3; indices[6] = 7; indices[7] = 6;
	indices[8] = 1; indices[9] = 0; indices[10] = 4; indices[11] = 5;
	indices[12] = 1; indices[13] = 2; indices[14] = 3; indices[15] = 0;
	indices[16] = 5; indices[17] = 6; indices[18] = 7; indices[19] = 4;

	// nose
	vertices[24] = 0; vertices[25] = halfsize; vertices[26] = -halfsize*1.3f;

	tindices[0] = 3; tindices[1] = 7; tindices[2] = 8;

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
		calcCamPos();
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
		calcCamPos();
	}
	
	void CritterB::rotateRight()
	{
		rotation -= speedfactor*20.0f;
		if ( rotation < 0.0f ) rotation += 360.0f;
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
	
			// adamdist=690;
				else if ( parseH.beginMatchesStrip( "adamdist=", line ) )
				{
					string AD = parseH.returnUntillStrip( ";", line );
					//cerr << "AD: " << AD  << endl;
					if(EOF == sscanf(AD.c_str(), "%d", &adamdist)) cerr << "ERROR INSERTING CRITTER" << endl;
				}
	
			// retinasize=9;
				else if ( parseH.beginMatchesStrip( "retinasize=", line ) )
				{
					string RES = parseH.returnUntillStrip( ";", line );
					//cerr << "RES: " << RES  << endl;
					if(EOF == sscanf(RES.c_str(), "%d", &retinasize)) cerr << "ERROR INSERTING CRITTER" << endl;
					//retinasize = retinasize;
					//if(EOF == sscanf(RES.c_str(), "%d", &retinasize)) cerr << "ERROR INSERTING CRITTER" << endl;
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


