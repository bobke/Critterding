#ifndef NEURONINTERZ_H
#define NEURONINTERZ_H

// internal includes
	#include "synapse.h"

// external includes
	#include <vector>
	#include <iostream>
	#include <cmath>

	using namespace std;

class NeuronInterz
{
	public:
		NeuronInterz();
		~NeuronInterz();

		int			output;
		int			waitoutput;
		unsigned int		maxSynapses;

		bool			isInhibitory;

		int			firingThreshold;
		unsigned int		dendridicBranches;

		bool			isMotor;
		unsigned int		motorFunc;

		void			process();
		void			connec( int *output, unsigned int dendriteBranch, float synapticWeight );

		vector<Synapse>		Synapses;

		float			potential;
		float			potentialDecay;

		bool			isPlastic;
		float			plasticityStrengthen;
		float			plasticityWeaken;

	private:


};

#endif
