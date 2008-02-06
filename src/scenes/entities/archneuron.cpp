#include "archneuron.h"

ArchNeuron::ArchNeuron()
{
	fireThresh	= 1;
	iWeightRange	= 1;
	isMotor		= false;
	MotorFunc	= 0;
}


ArchNeuron::~ArchNeuron()
{
	for ( unsigned int c=0; c < connections.size(); c++ ) delete connections[c];
}


