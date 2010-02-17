#include "brainz.h"
#include <cstdio>

Brainz::Brainz()
{
		neuronsFired					= 0;

	// build time defaults

		numberOfInputs					= 0;
		numberOfOutputs					= 0;
}

// BUILD TIME

	void Brainz::registerInput(unsigned int id)
	{
		Inputs.push_back( sensorNeuron() );
		Inputs[numberOfInputs].id = id;
		numberOfInputs++;
	}

	void Brainz::registerOutput(bool* var, unsigned int id)
	{
		Outputs.push_back( motorNeuron() );
		Outputs[numberOfOutputs].output = var;
		Outputs[numberOfOutputs].id = id;
		numberOfOutputs++;
	}

	void Brainz::wireArch(BrainzArch* brainzArch)
	{

		// clear everything
			Neurons.clear();
			Inputs.clear();
			Outputs.clear();

			// we know the amount of neurons already, reset totalsynapses for the count later
			totalNeurons = brainzArch->ArchNeurons.size();
			totalSynapses = 0;

		// create all runtime neurons
			for ( unsigned int i=0; i < totalNeurons; i++ )
			{
				NeuronInterz ni;

				ni.isInhibitory		= brainzArch->ArchNeurons[i].isInhibitory;
				ni.firingThreshold	= brainzArch->ArchNeurons[i].firingThreshold;

				ni.isMotor		= brainzArch->ArchNeurons[i].isMotor;
				if (ni.isMotor)
					ni.motorFunc		= brainzArch->findMotorNeuron(brainzArch->ArchNeurons[i].motorID);

				ni.isPlastic		= brainzArch->ArchNeurons[i].isPlastic;
				ni.plasticityStrengthen	= 1.0f+(1.0f/brainzArch->ArchNeurons[i].plasticityStrengthen);
				ni.plasticityWeaken	= 1.0f-(1.0f/brainzArch->ArchNeurons[i].plasticityWeaken);

				Neurons.push_back( ni );
			}
		// create their synapses & link them to their inputneurons
			for ( unsigned int i=0; i < totalNeurons; i++ )
			{
				// count connections
				totalSynapses += brainzArch->ArchNeurons[i].ArchSynapses.size();

				for ( unsigned int j=0; j < brainzArch->ArchNeurons[i].ArchSynapses.size(); j++ )
				{
					if ( brainzArch->ArchNeurons[i].ArchSynapses[j].isSensorNeuron )
					{
						brainzArch->ArchNeurons[i].ArchSynapses[j].realneuronID = brainzArch->findSensorNeuron(brainzArch->ArchNeurons[i].ArchSynapses[j].neuronID);
						Neurons[i].connec( &Inputs[ brainzArch->ArchNeurons[i].ArchSynapses[j].realneuronID ].output, 
							brainzArch->ArchNeurons[i].ArchSynapses[j].dendriteBranch, brainzArch->ArchNeurons[i].ArchSynapses[j].weight );
					}
					else
						Neurons[i].connec( &Neurons[ brainzArch->ArchNeurons[i].ArchSynapses[j].neuronID ].output, 
							brainzArch->ArchNeurons[i].ArchSynapses[j].dendriteBranch, brainzArch->ArchNeurons[i].ArchSynapses[j].weight );
				}
			}
			//cerr << "total neurons: " << totalNeurons << "total synapses: " << totalSynapses << endl;
	}


// RUN TIME

	void Brainz::clearInputs()
	{
		for ( unsigned int i=0; i < numberOfInputs; i++ )
		{
			Inputs[i].output = 0;
		}
	}

	void Brainz::process()
	{
		// reset fired neurons counter
		neuronsFired = 0;
		motorneuronsFired = 0;
		// clear Motor Outputs
		for ( unsigned int i=0; i < numberOfOutputs; i++ )
		{
			*Outputs[i].output = false;
		}
	
		for ( unsigned int i=0; i < totalNeurons; i++ )
		{
			NeuronInterz *n = &Neurons[i];
	
			n->process();
	
			// if neuron fires
			if ( n->waitoutput != 0 )
			{
				neuronsFired++;
				//cerr << "neuron " << i << " fired " << n->waitoutput << endl;

				// motor neuron check & exec
				if ( n->isMotor )
				{
					motorneuronsFired++;
					*Outputs[n->motorFunc].output = true;
					//cerr << "neuron " << i << " fired, motor is " << Neurons[i]->MotorFunc << " total now " << Outputs[Neurons[i]->MotorFunc]->output << endl;
				}
			}
		}
	
		// commit outputs at the end
		for ( unsigned int i=0; i < totalNeurons; i++ ) Neurons[i].output = Neurons[i].waitoutput;
	}

	void Brainz::processTillAnswer()
	{
//		neuronsFired = 0;
	
		// clear Motor Outputs
		for ( unsigned int i=0; i < numberOfOutputs; i++ )
			Outputs[i].output = false;
	
		// clear Neurons
		for ( unsigned int i=0; i < totalNeurons; i++ )
		{
			Neurons[i].output = 0;
			Neurons[i].potential = 0.0f;
		}
	
		unsigned int counter = 0;
		bool motorFired = false;
	
		while ( counter < 1000 && !motorFired )
		{
			for ( unsigned int i=0; i < totalNeurons; i++ )
			{
				NeuronInterz* n = &Neurons[i];
		
				n->process();
		
				// if neuron fires
				if ( n->waitoutput != 0 )
				{
					neuronsFired++;
		
					// motor neuron check & exec
					if ( n->isMotor )
					{
						motorFired = true;
						*Outputs[n->motorFunc].output = true;
						//cerr << "neuron " << i << " fired, motor is " << Neurons[i]->MotorFunc << " total now " << Outputs[Neurons[i]->MotorFunc]->output << endl;
					}
				}
			}
			// commit outputs at the end
			for ( unsigned int i=0; i < totalNeurons; i++ ) Neurons[i].output = Neurons[i].waitoutput;
	
			counter++;
		}
	}

Brainz::~Brainz()
{
}
