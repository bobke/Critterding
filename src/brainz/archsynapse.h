#ifndef ARCHSYNAPSE_H
#define ARCHSYNAPSE_H

class ArchSynapse
{
	public:
		ArchSynapse();
		~ArchSynapse();

		// determines if id referes to an interneuron or sensorneuron
			bool		isSensorNeuron;
	
		// id of neuron which axon connects to this synapse
			unsigned int	neuronID;
	
		// dendridic weight according
			unsigned int	dendriteBranch;

		// it's "weight"
			float		weight;

	private:
};

#endif
