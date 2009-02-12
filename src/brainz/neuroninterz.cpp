#include "neuroninterz.h"

NeuronInterz::NeuronInterz()
{

// 	maxSynapses			= 150;

	isInhibitory			= false;

	// input weight range, 5 = -5 <-> +5	-> 10 in total because 0 will be excluded
// 	dendridicBranches		= 10;

	// processing
// 	firingThreshold			= 30.0f;
	potential			= 0.0f;
	potentialDecay			= 0.95f;

	// output
	output				= 0;
	waitoutput			= 0;

	// plasticity up & down
	isPlastic			= false;
// 	plasticityStrengthen		= 1.0f+(1.0f/100.0f);
// 	plasticityWeaken		= 1.0f-(1.0f/1000.0f);

	// SPECIALO optional reference that makes this a MOTOR neuron, but it depends on not being defined
	isMotor				= false;
	motorFunc			= 0;
}

void NeuronInterz::process()
{
	// potential decay
	potential = potential * potentialDecay;

	// make every connection do it's influence on the neuron's total potential
	unsigned int ssize = Synapses.size();
	for ( unsigned int i=0; i < ssize; i++ )
	{
		// lower synaptic weights
		if (isPlastic)
			Synapses[i].weight = Synapses[i].weight * plasticityWeaken;

		if ( *Synapses[i].ref != 0 )
			potential += (Synapses[i].weight * Synapses[i].dendriteBranch * *Synapses[i].ref);
	}

	if ( isInhibitory )
	{
		// do we spike/fire
		if ( potential <= -1.0f * firingThreshold )
		{
			// reset neural potential
			potential = 0.0f;
	
			// fire the neuron
			waitoutput = -1;

			// PLASTICITY: if neuron & synapse fire together, the synapse strenghtens
			if (isPlastic)
			{
				for ( unsigned int i=0; i < ssize; i++ )
				{
					// if synapse fired, strenghten the weight
					if ( (*Synapses[i].ref < 0.0f && Synapses[i].weight > 0.0f) || (*Synapses[i].ref > 0.0f && Synapses[i].weight < 0.0f) )
					{
// 						cerr << endl << "Inhibitory firing" << endl << "synref: " << *Synapses[i].ref << endl << "pre weight:  " << Synapses[i].weight << endl;
						Synapses[i].weight = Synapses[i].weight * plasticityStrengthen;
// 						cerr << "post weight: " << Synapses[i].weight << endl;
					}

					// if weight > max back to max
 					if	( Synapses[i].weight > 5.0f ) Synapses[i].weight = 5.0f;
 					else if ( Synapses[i].weight <-5.0f ) Synapses[i].weight =-5.0f;
				}
			}
		}
		// don't fire the neuron
		else
		{
			waitoutput = 0;
			// reset potential if < 0
			if ( potential > 0.0f ) potential = 0.0f;
		}
	}
	else
	{
		// do we spike/fire
		if ( potential >= firingThreshold )
		{
			// reset neural potential
			potential = 0.0f;
	
			// fire the neuron
			waitoutput = 1;

			// PLASTICITY: if neuron & synapse fire together, the synapse strenghtens
			if (isPlastic)
			{
				for ( unsigned int i=0; i < ssize; i++ )
				{
					// if synapse fired, strenghten the weight
					if ( (*Synapses[i].ref > 0.0f && Synapses[i].weight > 0.0f) || (*Synapses[i].ref < 0.0f && Synapses[i].weight < 0.0f) )
					{
// 						cerr << endl << "Excititory firing" << endl << "synref: " << *Synapses[i].ref << endl << "pre weight:  " << Synapses[i].weight << endl;
						Synapses[i].weight = Synapses[i].weight * plasticityStrengthen;
// 						cerr << "post weight: " << Synapses[i].weight << endl;
					}

					// if weight > max back to max
 					if	( Synapses[i].weight > 5.0f ) Synapses[i].weight = 5.0f;
 					else if ( Synapses[i].weight <-5.0f ) Synapses[i].weight =-5.0f;
				}
			}
		}
		// don't fire the neuron
		else
		{
			waitoutput = 0;
			// reset potential if < 0
			if ( potential < 0.0f ) potential = 0.0f;
		}
	}

}

void NeuronInterz::connec( float *output, unsigned int dendriteBranch, float synapticWeight )
//void NeuronInterz::connec( int *output, unsigned int dendriteBranch, float synapticWeight )
{
		Synapse s;
		s.ref = output;
		s.dendriteBranch = dendriteBranch;
		s.weight = synapticWeight;

		Synapses.push_back( s );

//		cerr << "I: " << Synapses.size()-1 << "=" << *Synapses[Synapses.size()-1].ref << "(" << Synapses[Synapses.size()-1].ref << ")";
//		cerr << *Synapses[0].ref << endl;
}

NeuronInterz::~NeuronInterz()
{
//	for ( unsigned int i=0; i < inputs.size(); i++ ) delete inputs[i];
}


