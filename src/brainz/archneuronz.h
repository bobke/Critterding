#ifndef ARCHNEURONZ_H
#define ARCHNEURONZ_H

// interneal includes
	#include "archsynapse.h"

// external includes
	#include <vector>
	using namespace std;

class ArchNeuronz
{
	public:
		ArchNeuronz();
		~ArchNeuronz();

		// inhibitory neuron by flag
			bool				isInhibitory;

		// Consistent Synapses flag
			bool				hasConsistentSynapses;

		// inhibitory synapses flag
			bool				hasInhibitorySynapses;

		// neuron firing potential
			unsigned int			firingThreshold;

		// dendridic branches
			unsigned int			dendridicBranches;

		// motor neuron ability (excititatory only)
			// flag
			bool				isMotor;
			// function
			unsigned int			motorFunc;

		// synaptic plasticity by flag
			bool				isPlastic;
			// factors
			unsigned int			plasticityStrengthen;
			unsigned int			plasticityWeaken;

		// vector of synapses
			vector<ArchSynapse>		ArchSynapses;


	private:

};

#endif
