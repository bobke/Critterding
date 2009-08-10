#include "archneuronz.h"

ArchNeuronz::ArchNeuronz()
{
	isInhibitory		= false;
	hasConsistentSynapses	= false;
	hasInhibitorySynapses	= false;
	firingThreshold		= 100;
	dendridicBranches	= 10;

	isMotor			= false;
	motorID			= 0;

	isPlastic		= false;
	plasticityStrengthen	= 1;
	plasticityWeaken	= 1;
}


ArchNeuronz::~ArchNeuronz()
{
}


