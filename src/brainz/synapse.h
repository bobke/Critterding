#ifndef SYNAPSE_H
#define SYNAPSE_H

class Synapse
{
	public:
		Synapse();
		~Synapse();

		// InputNeuron's Output Pointer
		//int *ref;
		float *ref;

		// dendridic branch synapse is located on
		float dendriteBranch;

		// it's synaptic weight -1.0f <-> +1.0f
		float weight;

	private:
};

#endif
