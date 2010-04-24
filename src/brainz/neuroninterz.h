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

 		float			output;
 		float			waitoutput;

		bool			isInhibitory;

		unsigned int		firingThreshold;

		bool			isMotor;
		unsigned int		motorFunc;

		void			process();
		void			connec( float *output, float synapticWeight ); // unsigned int dendriteBranch, 

		vector<Synapse>		Synapses;

		float			potential;
		float			potentialDecay;

		bool			isPlastic;
		float			plasticityStrengthen;
		float			plasticityWeaken;

	private:


};

#endif
