#ifndef BRAINZ_H
#define BRAINZ_H

// internal includes
	#include "../utils/randgen.h"
	#include "../utils/parser.h"

	#include "archneuronz.h"
//	#include "neuronsensorz.h"
	#include "neuroninterz.h"

// external includes
	#include <vector>
	#include <sstream>
	#include <iostream>
	using namespace std;

struct motorNeuron
{
	bool*		output;
	unsigned int	id;
};

struct sensorNeuron
{
	float		output;
	unsigned int	id;
};

class Brainz
{
	public:
		Brainz();
		~Brainz();

		// input / output accessor/mutators
			vector<sensorNeuron>	Inputs;
			vector<motorNeuron>	Outputs;
		// vectors
			vector<NeuronInterz>	Neurons;
			vector<ArchNeuronz>	ArchNeurons;

	// BUILD TIME

		// min/max neurons at build time
			unsigned int		minNeuronsAtBuildtime;
			unsigned int		maxNeuronsAtBuildtime;

		// fixed numbers of inputs/outputs
			unsigned int		numberOfInputs;
			unsigned int		numberOfOutputs;

		// absolute max neurons (mutation bounding)
			unsigned int		maxNeurons;

			unsigned int		percentMutateEffectAddNeuron;
			unsigned int		percentMutateEffectRemoveNeuron;
			unsigned int		percentMutateEffectAlterNeuron;
			unsigned int		percentMutateEffectAddSynapse;
			unsigned int		percentMutateEffectRemoveSynapse;
			unsigned int		percentMutateEffectAlterMutable;
				bool			mutate_MutateEffects;

		// percent chance that when adding a new random neuron, it's inhibitory
			unsigned int		percentChanceInhibitoryNeuron;
				bool			mutate_percentChanceInhibitoryNeuron;

		// synaptic consistancy, meaning all synapses of a neuron will be OR I OR E
		// if set to 0, neurons will have mixed I and E synapses
			unsigned int		percentChanceConsistentSynapses;
				bool			mutate_percentChanceConsistentSynapses;

		// percent chance that when adding a new random neuron, it has inhibitory synapses
			unsigned int		percentChanceInhibitorySynapses;
				bool			mutate_percentChanceInhibitorySynapses;

		// percent chance that when adding a new random neuron, it has a motor function
			unsigned int		percentChanceMotorNeuron;
				bool			mutate_percentChanceMotorNeuron;

		// percent chance that when adding a new random neuron, it is has synaptic plasticity
			unsigned int		percentChancePlasticNeuron;
				bool			mutate_percentChancePlasticNeuron;

			// min/max synaptic plasticity strengthening factor
				unsigned int		minPlasticityStrengthen;
				unsigned int		maxPlasticityStrengthen;

			// min/max synaptic plasticity weakening factor
				unsigned int		minPlasticityWeaken;
				unsigned int		maxPlasticityWeaken;

			// flag if we'll mutate these
				bool			mutate_PlasticityFactors;

		// min/max firing threshold
			unsigned int		minFiringThreshold;
				bool			mutate_minFiringThreshold;
			unsigned int		maxFiringThreshold;
				bool			mutate_maxFiringThreshold;

		// max dendritic branches in a new neuron
			unsigned int		maxDendridicBranches;
				bool			mutate_maxDendridicBranches;

		// percent chance that a new synapse is connected to a sensor neuron
			unsigned int		percentChanceSensorySynapse;
				bool			mutate_percentChanceSensorySynapse;

		// min/max synapses at build time
			unsigned int		minSynapsesAtBuildtime;
			unsigned int		maxSynapsesAtBuildtime;

		// absolute min/max synapses (mutation/plastic bounding)
			unsigned int		minSynapses;
			unsigned int		maxSynapses;

		// brain architecture mutation factor @ mutation time (%)
			unsigned int		percentMutation;
				bool			mutate_percentMutation;

	// INFO
		// total neuron & connection keepers
			unsigned int		totalNeurons;
			unsigned int		totalSynapses;

		// after every time instance, this will contain how many neurons where fired in that instant (energy usage help)
			unsigned int		neuronsFired;
			unsigned int 		motorneuronsFired;

	// build commands

		// functions
			void			copyFrom(const Brainz& otherBrain);
			void			mergeFrom(const Brainz& otherBrain1, const Brainz& otherBrain2);
			void			registerOutput(bool* var, unsigned int id);
			void			registerInput(unsigned int id);
			void			removeObsoleteMotorsAndSensors();
			void			buildArch();
			void			mutate(unsigned int runs);
			void			wireArch();
		// load save architecture (serialize)
			void			setArch(string* content);
			string*			getArch();

	// RUN TIME

		// functions
			void			clearInputs();
			void			process();
			void			processTillAnswer();

			int			findSensorNeuron( unsigned int id );
	private:
		// utilities
			Parser			*parseH;
			RandGen			*randgen;

		// a buffer for reading architecture
			string			archBuffer;

			int			findMotorNeuron( unsigned int id );
// 			int			findSensorNeuron( unsigned int id );

		// build time functions
			void			addRandomArchNeuron();
			unsigned int		addRandomArchSynapse(unsigned int parentneuron);

};

#endif
