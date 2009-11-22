#include "brainz.h"
#include <cstdio>

Brainz::Brainz()
{

		neuronsFired					= 0;

	// build time defaults

		maxNeurons					= 150;
		minSynapses					= 1;
		maxSynapses					= 150;

		totalNeurons					= 0;
		totalSynapses					= 0;

		numberOfInputs					= 0;
		numberOfOutputs					= 0;

		minNeuronsAtBuildtime				= 10;
		maxNeuronsAtBuildtime				= 150;

		// mutatables

		minSynapsesAtBuildtime				= 1;
		maxSynapsesAtBuildtime				= 50;

		percentChanceInhibitoryNeuron			= 50;
			mutate_percentChanceInhibitoryNeuron	= false;

		percentChanceConsistentSynapses			= 50;
			mutate_percentChanceConsistentSynapses	= false;

		percentChanceInhibitorySynapses			= 50;
			mutate_percentChanceInhibitorySynapses	= false;

		percentChanceMotorNeuron			= 50;
			mutate_percentChanceMotorNeuron		= false;

		percentChancePlasticNeuron			= 50;
			mutate_percentChancePlasticNeuron	= false;

		minPlasticityStrengthen				= 100;
		maxPlasticityStrengthen				= 1000;
		minPlasticityWeaken				= 1000;
		maxPlasticityWeaken				= 10000;
			mutate_PlasticityFactors		= false;

		percentChanceSensorySynapse			= 50;
			mutate_percentChanceSensorySynapse	= false;

		minFiringThreshold				= 10;
			mutate_minFiringThreshold		= false;

		maxFiringThreshold				= 100;
			mutate_maxFiringThreshold		= false;

		maxDendridicBranches				= 20;
			mutate_maxDendridicBranches		= false;

		percentMutation					= 1;
			mutate_percentMutation			= false;

		// 90 % > 10 for mutatables
		percentMutateEffectAddNeuron			= 5;
		percentMutateEffectRemoveNeuron			= 5;
		percentMutateEffectAlterNeuron			= 5;
		percentMutateEffectAddSynapse			= 40;
		percentMutateEffectRemoveSynapse		= 40;
		percentMutateEffectAlterMutable			= 5;
			mutate_MutateEffects			= false;
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
// 		Outputs.push_back( var );
		numberOfOutputs++;
	}

	void Brainz::removeObsoleteMotorsAndSensors()
	{
// 		cerr << endl << "removing obsolete brainstuff" << endl;
		for ( int i = 0; i < (int)ArchNeurons.size(); i++ )
		{
			ArchNeuronz* an = &ArchNeurons[i];
			// disable motor neurons
			if ( an->isMotor )
			{
				if ( findMotorNeuron( an->motorID ) == -1 )
				{
					an->isMotor = false;
				}
			}

			// disable sensor inputs
			for ( int j = 0; j < (int)an->ArchSynapses.size(); j++ )
			{
				ArchSynapse* as = &an->ArchSynapses[j];
				if ( as->isSensorNeuron )
				{
					if ( findSensorNeuron( as->neuronID ) == -1 )
					{
						an->ArchSynapses.erase( an->ArchSynapses.begin()+j );
						j--;
					}
				}
			}
		}
// 		cerr << "done removing obsolete brainstuff" << endl << endl;
	}


	void Brainz::buildArch()
	{
		// clear architecture by removing all architectural neurons
			ArchNeurons.clear();
	
		// determine number of neurons this brain will start with
			unsigned int NeuronAmount = randgen->Instance()->get( minNeuronsAtBuildtime, maxNeuronsAtBuildtime );
	
		// create the architectural neurons
			for ( unsigned i = 0; i < NeuronAmount; i++ )
				addRandomArchNeuron();
	
		// create architectural synapses
			for ( unsigned neuronID = 0; neuronID < NeuronAmount; neuronID++ )
			{
				// determine amount of synapses this neuron will start with
					unsigned int SynapseAmount = randgen->Instance()->get( minSynapsesAtBuildtime, maxSynapsesAtBuildtime );

				// create the architectural neurons
					for ( unsigned j = 0; j < SynapseAmount; j++ ) addRandomArchSynapse(neuronID);
			}
	}

	void Brainz::addRandomArchNeuron()
	{
		// new architectural neuron
			ArchNeuronz an;

		// is it inhibitory ?
			if ( randgen->Instance()->get(1,100) <= percentChanceInhibitoryNeuron )
				an.isInhibitory = true;

		// if not, is it motor ?
			else if ( randgen->Instance()->get(1,100) <= percentChanceMotorNeuron )
			{
				unsigned int motorID = Outputs[ randgen->Instance()->get( 0, numberOfOutputs-1 ) ].id;

				// check if motor already used
				bool proceed = true;
				for ( unsigned int i=0; i < ArchNeurons.size() && proceed; i++ )
					if ( ArchNeurons[i].isMotor && ArchNeurons[i].motorID == motorID )
						proceed = false;

				if ( proceed )
				{
					an.isMotor = true;
					an.motorID = motorID;
				}
			}

		// does it have synaptic plasticity ?
			if ( randgen->Instance()->get(1,100) <= percentChancePlasticNeuron )
			{
				an.isPlastic = true;
				an.plasticityStrengthen = randgen->Instance()->get( minPlasticityStrengthen, maxPlasticityStrengthen );
				an.plasticityWeaken = randgen->Instance()->get( minPlasticityWeaken, maxPlasticityWeaken );
			}

		// does it have consistent synapses ?
			if ( randgen->Instance()->get(1,100) <= percentChanceConsistentSynapses )
			{
				an.hasConsistentSynapses = true;

				// if so, does it have inhibitory synapses ?
					if ( randgen->Instance()->get(1,100) <= percentChanceInhibitorySynapses )
						an.hasInhibitorySynapses = true;
			}

		// determine firing threshold
			if ( an.isMotor ) an.firingThreshold = maxFiringThreshold;
			else an.firingThreshold = randgen->Instance()->get( minFiringThreshold, maxFiringThreshold );

		// determine dendritic branches
			if ( an.isMotor ) an.dendridicBranches = maxDendridicBranches;
			else an.dendridicBranches = randgen->Instance()->get( 1, maxDendridicBranches );
			

		// push it on the vector
			ArchNeurons.push_back( an );
	}

	unsigned int Brainz::addRandomArchSynapse(unsigned int parentneuron)
	{
		// new architectural synapse
			ArchSynapse as;
	
		// is it connected to a sensor neuron ?
										// < 2 because if only 1 archneuron, it can't connect to other one
			if ( randgen->Instance()->get( 1, 100 ) <= percentChanceSensorySynapse || ArchNeurons.size() < 2 )
			{
				as.isSensorNeuron = true;

				// sensor neuron id synapse is connected to
				as.neuronID = Inputs[ randgen->Instance()->get( 0, numberOfInputs-1 ) ].id;

			}
		// if not determine inter neuron id
	 		else
			{
				// as in real life, neurons can connect to themselves
				as.neuronID = randgen->Instance()->get( 0, ArchNeurons.size()-1 );
	 		}
	
		// dendrite branch number
			as.dendriteBranch = randgen->Instance()->get( 1, ArchNeurons[parentneuron].dendridicBranches );

		// synaptic weight
			if ( ArchNeurons[parentneuron].hasConsistentSynapses )
			{
				if ( ArchNeurons[parentneuron].hasInhibitorySynapses )
					as.weight	=-1.0f;
				else
					as.weight	=1.0f;
			}
			else
			{
				if ( randgen->Instance()->get(1,100) <= percentChanceInhibitorySynapses )
					as.weight	=-1.0f;
				else
					as.weight	=1.0f;
			}

		// push it on the vector
			ArchNeurons[parentneuron].ArchSynapses.push_back( as );

		// return it's id
			return (ArchNeurons[parentneuron].ArchSynapses.size()-1);
	}

	void Brainz::wireArch()
	{

		// clear everything
			Neurons.clear();
			Inputs.clear();
			Outputs.clear();

			// we know the amount of neurons already, reset totalsynapses for the count later
			totalNeurons = ArchNeurons.size();
			totalSynapses = 0;

// 		// init inputs
// 			for ( unsigned int i=0; i < numberOfInputs; i++ )
// 			{
// 				//NeuronSensorz ns;
// 				Inputs.push_back( sensorNeuron() );
// 			}

// 		// init outputs
// 			for ( unsigned int i=0; i < numberOfOutputs; i++ )
// 			{
// 				NeuronSensorz ns;
// 				Outputs.push_back( ns );
// 			}

		// create all runtime neurons
			for ( unsigned int i=0; i < totalNeurons; i++ )
			{
				NeuronInterz ni;

				ni.maxSynapses		= maxSynapses;
		
				ni.isInhibitory		= ArchNeurons[i].isInhibitory;
				ni.firingThreshold	= ArchNeurons[i].firingThreshold;

				ni.dendridicBranches	= ArchNeurons[i].dendridicBranches;

				ni.isMotor		= ArchNeurons[i].isMotor;
				if (ni.isMotor)
					ni.motorFunc		= findMotorNeuron(ArchNeurons[i].motorID);

				ni.isPlastic		= ArchNeurons[i].isPlastic;
				ni.plasticityStrengthen	= 1.0f+(1.0f/ArchNeurons[i].plasticityStrengthen);
				ni.plasticityWeaken	= 1.0f-(1.0f/ArchNeurons[i].plasticityWeaken);

				Neurons.push_back( ni );
			}
		// create their synapses & link them to their inputneurons
			for ( unsigned int i=0; i < totalNeurons; i++ )
			{
				// count connections
				totalSynapses += ArchNeurons[i].ArchSynapses.size();

				for ( unsigned int j=0; j < ArchNeurons[i].ArchSynapses.size(); j++ )
				{
					if ( ArchNeurons[i].ArchSynapses[j].isSensorNeuron )
					{
						ArchNeurons[i].ArchSynapses[j].realneuronID = findSensorNeuron(ArchNeurons[i].ArchSynapses[j].neuronID);
						Neurons[i].connec( &Inputs[ ArchNeurons[i].ArchSynapses[j].realneuronID ].output, ArchNeurons[i].ArchSynapses[j].dendriteBranch, ArchNeurons[i].ArchSynapses[j].weight );
					}
					else
						Neurons[i].connec( &Neurons[ ArchNeurons[i].ArchSynapses[j].neuronID ].output, ArchNeurons[i].ArchSynapses[j].dendriteBranch, ArchNeurons[i].ArchSynapses[j].weight );
				}
			}
			//cerr << "total neurons: " << totalNeurons << "total synapses: " << totalSynapses << endl;

	}

	int Brainz::findSensorNeuron( unsigned int id )
	{
		for ( unsigned int i=0; i < numberOfInputs; i++ )
			if ( Inputs[i].id == id )
				return i;

// 		cerr << "brain findSensorNeuron error for id: " << id << endl;
		return -1;
	}

	int Brainz::findMotorNeuron( unsigned int id )
	{
		for ( unsigned int i=0; i < numberOfOutputs; i++ )
			if ( Outputs[i].id == id )
				return i;

// 		cerr << "brain findMotorNeuron error for id: " << id << endl;
		return -1;
	}

	void Brainz::mutate(unsigned int runs)
	{
		// have to do count cuz wireArch not done yet
		totalNeurons		= ArchNeurons.size();
		totalSynapses		= 0;
		for ( unsigned int i = 0; i < totalNeurons; i++ ) totalSynapses += ArchNeurons[i].ArchSynapses.size();

		if ( runs == 0 )
		{
			runs = randgen->Instance()->get(1, (int)(totalSynapses/(100/percentMutation)));
		}

		for ( unsigned int i=0; i < runs; i++ )
		{
			unsigned int mode = randgen->Instance()->get(1,100);

		// add a new neuron
			if ( mode <= percentMutateEffectAddNeuron )
			{
				if ( ArchNeurons.size() < maxNeurons )
				{
					addRandomArchNeuron();
					unsigned int nid = ArchNeurons.size()-1;
					//cerr << "\t+N " << nid << endl;

					// random amount of connections, at mutation time we take the average syns / neuron *2 as a maximum
					unsigned int tNeurons = totalNeurons;
					if ( tNeurons == 0 )
						tNeurons = 1;

					int maxSynapsesAtMutation = (2*(totalSynapses/tNeurons)) + 1;

					unsigned int cAmount = randgen->Instance()->get( minSynapsesAtBuildtime, maxSynapsesAtMutation );
					for ( unsigned j = 0; j < cAmount; j++ )
						addRandomArchSynapse(nid);
				}
				else runs++;
			}

		// remove a neuron
			else if ( mode <= percentMutateEffectAddNeuron + percentMutateEffectRemoveNeuron )
			{
				if ( ArchNeurons.size() > 0 )
				{
					// pick a random neuron
					unsigned int nid = randgen->Instance()->get( 0, ArchNeurons.size()-1 );
					//cerr << "\t-N " << nid << endl;

					// first remove all connections to this neuron
					for ( unsigned int i=0; i < ArchNeurons.size(); i++ )
					{
						for ( unsigned int j=0; j < ArchNeurons[i].ArchSynapses.size(); j++ )
						{
							if ( !ArchNeurons[i].ArchSynapses[j].isSensorNeuron )
							{
								if ( ArchNeurons[i].ArchSynapses[j].neuronID == nid )
								{
									//delete ArchNeurons[i].ArchSynapses[j];
									ArchNeurons[i].ArchSynapses.erase(ArchNeurons[i].ArchSynapses.begin()+j);
									j--;
								}
								// if higher id drop one
								else if ( ArchNeurons[i].ArchSynapses[j].neuronID > nid )
								{
									ArchNeurons[i].ArchSynapses[j].neuronID--;
								}
							}
						}
					}
					ArchNeurons.erase(ArchNeurons.begin()+nid);
				}
				// make sure we mutate
				else runs++;
			}

		// alter a neuron
			else if ( mode <= percentMutateEffectAddNeuron + percentMutateEffectRemoveNeuron + percentMutateEffectAlterNeuron )
			{
				if ( ArchNeurons.size() > 0 )
				{

					// pick a random neuron
						unsigned int nid = randgen->Instance()->get( 0, ArchNeurons.size()-1 );

					// decide what to alter
						unsigned int jmode = randgen->Instance()->get(1,6);

					// inhibitory function
						if ( jmode == 1 )
						{
							// backup old
							bool old = ArchNeurons[nid].isInhibitory;

							// reset
							ArchNeurons[nid].isInhibitory = false;

							// redetermine
							if ( randgen->Instance()->get(1,100) <= percentChanceInhibitoryNeuron )
								ArchNeurons[nid].isInhibitory = true;

							// make sure we mutate
							if ( old == ArchNeurons[nid].isInhibitory ) runs++;
						}
					// motor neuron
						else if ( jmode == 2 )
						{
							// backup old
							bool old = ArchNeurons[nid].isMotor;
							unsigned int oldfunc = ArchNeurons[nid].motorID;

							// reset
							ArchNeurons[nid].isMotor = false;
							ArchNeurons[nid].motorID = 0;

							// redetermine
							if ( !ArchNeurons[nid].isInhibitory && randgen->Instance()->get(1,100) <= percentChanceMotorNeuron )
							{
								unsigned int motorID = Outputs[ randgen->Instance()->get( 0, numberOfOutputs-1 ) ].id;

								bool proceed = true;
								for ( unsigned int i=0; i < ArchNeurons.size() && proceed; i++ )
									if ( ArchNeurons[i].isMotor && ArchNeurons[i].motorID == motorID )
										proceed = false;
				
								if ( proceed )
								{
									ArchNeurons[nid].isMotor = true;
									ArchNeurons[nid].motorID = motorID;
								}
							}

							// make sure we mutate
							if ( old == ArchNeurons[nid].isMotor && oldfunc == ArchNeurons[nid].motorID )
								runs++;
						}
					// synaptic plasticity
						else if ( jmode == 3 )
						{
							// backup old
							bool old = ArchNeurons[nid].isPlastic;
							unsigned int olds = ArchNeurons[nid].plasticityStrengthen;
							unsigned int oldw = ArchNeurons[nid].plasticityWeaken;

							// reset
							ArchNeurons[nid].isPlastic = false;
							ArchNeurons[nid].plasticityStrengthen = 1;
							ArchNeurons[nid].plasticityWeaken = 1;

							// redetermine
							if ( randgen->Instance()->get(1,100) <= percentChancePlasticNeuron )
							{
								ArchNeurons[nid].isPlastic = true;
								ArchNeurons[nid].plasticityStrengthen = randgen->Instance()->get( minPlasticityStrengthen, maxPlasticityStrengthen );
								ArchNeurons[nid].plasticityWeaken = randgen->Instance()->get( minPlasticityWeaken, maxPlasticityWeaken );
							}

							// make sure we mutate
							if ( old == ArchNeurons[nid].isPlastic && olds == ArchNeurons[nid].plasticityStrengthen && oldw == ArchNeurons[nid].plasticityWeaken ) runs++;
						}

					// consistent synapses
						else if ( jmode == 4 )
						{
							// backup old
							bool old = ArchNeurons[nid].hasConsistentSynapses;
							bool oldi = ArchNeurons[nid].hasInhibitorySynapses;

							// reset
							ArchNeurons[nid].hasConsistentSynapses = false;

							// redetermine
							if ( randgen->Instance()->get(1,100) <= percentChanceConsistentSynapses )
							{
								ArchNeurons[nid].hasConsistentSynapses = true;
				
								// if so, does it have inhibitory synapses ?
									if ( randgen->Instance()->get(1,100) <= percentChanceInhibitorySynapses )
										ArchNeurons[nid].hasInhibitorySynapses = true;
							}

							// make sure we mutate
							if ( old == ArchNeurons[nid].hasConsistentSynapses && oldi == ArchNeurons[nid].hasInhibitorySynapses ) runs++;
						}

					// firing threshold
						else if ( jmode == 5 )
						{
							// backup old
							unsigned int old = ArchNeurons[nid].firingThreshold;

							ArchNeurons[nid].firingThreshold = randgen->Instance()->get( minFiringThreshold, maxFiringThreshold );

							// make sure we mutate
							if ( old == ArchNeurons[nid].firingThreshold ) runs++;
						}

					// dendritic branches
						else if ( jmode == 6 )
						{
							// backup old
							unsigned int old = ArchNeurons[nid].dendridicBranches;

							ArchNeurons[nid].dendridicBranches = randgen->Instance()->get( 1, maxDendridicBranches );

							// make sure we mutate
							if ( old == ArchNeurons[nid].dendridicBranches ) runs++;
						}

				}
			}

		// add a new synapse
			else if ( mode <= percentMutateEffectAddNeuron + percentMutateEffectRemoveNeuron + percentMutateEffectAlterNeuron + percentMutateEffectAddSynapse )
			{
				if ( ArchNeurons.size() > 0 )
				{
					// pick a random neuron
					unsigned int nid = randgen->Instance()->get( 0, ArchNeurons.size()-1 );

					// don't go over maximum connections
					if ( ArchNeurons[nid].ArchSynapses.size() < maxSynapses )
					{
						//cerr << "\t+C " << nid << endl;
						addRandomArchSynapse(nid);
					}
					else runs++;
				}
				else runs++;
			}

		// remove a synapse
			else if ( mode <= percentMutateEffectAddNeuron + percentMutateEffectRemoveNeuron + percentMutateEffectAlterNeuron + percentMutateEffectAddSynapse + percentMutateEffectRemoveSynapse )
			{
				if ( ArchNeurons.size() > 0 )
				{
					// pick a random neuron
					unsigned int nid = randgen->Instance()->get( 0, ArchNeurons.size()-1 );

					// don't go under minimum connections
					if ( ArchNeurons[nid].ArchSynapses.size() > minSynapses )
					{
						//cerr << "\t-C " << nid << endl;
						unsigned int sID = randgen->Instance()->get(0, ArchNeurons[nid].ArchSynapses.size()-1);
						//delete ArchNeurons[nid].ArchSynapses[connid];
						ArchNeurons[nid].ArchSynapses.erase(ArchNeurons[nid].ArchSynapses.begin()+sID);
					}
					else runs++;
				}
				else runs++;
			}

		// change a mutatable
			else if (  mode <= percentMutateEffectAddNeuron + percentMutateEffectRemoveNeuron + percentMutateEffectAlterNeuron + percentMutateEffectAddSynapse + percentMutateEffectRemoveSynapse + percentMutateEffectAlterMutable )
			{
				unsigned int imode = randgen->Instance()->get(1,12);

				if ( imode == 1 && mutate_percentChanceInhibitoryNeuron )
				{
					unsigned int jmode = randgen->Instance()->get(1,2);
					unsigned int factor = randgen->Instance()->get(1,5);

					if ( jmode == 1 && percentChanceInhibitoryNeuron < 100-factor )	percentChanceInhibitoryNeuron+=factor;
					else if ( percentChanceInhibitoryNeuron > 0+factor )		percentChanceInhibitoryNeuron-=factor;
				}

				else if ( imode == 2 && mutate_percentChanceConsistentSynapses )
				{
					unsigned int jmode = randgen->Instance()->get(1,2);
					unsigned int factor = randgen->Instance()->get(1,5);

					if ( jmode == 1 && percentChanceConsistentSynapses < 100-factor )	percentChanceConsistentSynapses+=factor;
					else if ( percentChanceConsistentSynapses > 0+factor )			percentChanceConsistentSynapses-=factor;
				}

				else if ( imode == 3 && mutate_percentChanceInhibitorySynapses )
				{
					unsigned int jmode = randgen->Instance()->get(1,2);
					unsigned int factor = randgen->Instance()->get(1,5);

					if ( jmode == 1 && percentChanceInhibitorySynapses < 100-factor )	percentChanceInhibitorySynapses+=factor;
					else if ( percentChanceInhibitorySynapses > 0+factor )			percentChanceInhibitorySynapses-=factor;
				}

				else if ( imode == 4 && mutate_percentChanceMotorNeuron )
				{
					unsigned int jmode = randgen->Instance()->get(1,2);
					unsigned int factor = randgen->Instance()->get(1,5);

					if ( jmode == 1 && percentChanceMotorNeuron < 100-factor )	percentChanceMotorNeuron+=factor;
					else if ( percentChanceMotorNeuron > 0+factor )			percentChanceMotorNeuron-=factor; // !!! > 1
				}

				else if ( imode == 5 && mutate_percentChancePlasticNeuron )
				{
					unsigned int jmode = randgen->Instance()->get(1,2);
					unsigned int factor = randgen->Instance()->get(1,5);

					if ( jmode == 1 && percentChancePlasticNeuron < 100-factor )	percentChancePlasticNeuron+=factor;
					else if ( percentChancePlasticNeuron > 0+factor )		percentChancePlasticNeuron-=factor;
				}

				else if ( imode == 6 && mutate_percentChanceSensorySynapse )
				{
					unsigned int jmode = randgen->Instance()->get(1,2);
					unsigned int factor = randgen->Instance()->get(1,5);

					if ( jmode == 1 && percentChanceSensorySynapse < 100-factor )	percentChanceSensorySynapse+=factor;
					else if ( percentChanceSensorySynapse > minSynapses+factor )	percentChanceSensorySynapse-=factor;
				}

				else if ( imode == 7 && mutate_minFiringThreshold )
				{
					unsigned int jmode = randgen->Instance()->get(1,2);
					unsigned int factor = randgen->Instance()->get(1,5);

					if ( jmode == 1 && minFiringThreshold < maxFiringThreshold-factor )	minFiringThreshold+=factor; // watch out idd
					else if ( minFiringThreshold > 1+factor )				minFiringThreshold-=factor; // !!! > 1
				}

				else if ( imode == 8 && mutate_maxFiringThreshold )
				{
					unsigned int jmode = randgen->Instance()->get(1,2);
					unsigned int factor = randgen->Instance()->get(1,5);

					if ( jmode == 1 && maxFiringThreshold < 1000-factor )		maxFiringThreshold+=factor;
					else if ( maxFiringThreshold > minFiringThreshold+factor )	maxFiringThreshold-=factor; // !!! > minFiringThreshold
				}

				else if ( imode == 9 && mutate_maxDendridicBranches )
				{
					unsigned int jmode = randgen->Instance()->get(1,2);
					unsigned int factor = randgen->Instance()->get(1,5);

					if ( jmode == 1 && maxDendridicBranches < 100-factor )	maxDendridicBranches+=factor;
					else if ( maxDendridicBranches > 1+factor )		maxDendridicBranches-=factor; // !!! > 1
				}

				else if ( imode == 10 && mutate_percentMutation )
				{
					unsigned int jmode = randgen->Instance()->get(1,2);
					unsigned int factor = randgen->Instance()->get(1,5);

					if ( jmode == 1 && percentMutation < 100-factor )	percentMutation+=factor;
					else if ( percentMutation > 1+factor )			percentMutation-=factor; // !!! > 1 or no more mutation at all
				}

				else if ( imode == 11 && mutate_MutateEffects )
				{
					// up or down
					unsigned int jmode = randgen->Instance()->get(1,2);

					// which of 5
					unsigned int kmode = randgen->Instance()->get(1,6);

					if ( jmode == 1 && percentMutateEffectAddNeuron + percentMutateEffectRemoveNeuron + percentMutateEffectAlterNeuron + percentMutateEffectAddSynapse + percentMutateEffectRemoveSynapse + percentMutateEffectAlterMutable <= 100 )
					{
						if ( kmode == 1 )	percentMutateEffectAddNeuron++;
						else if ( kmode == 2 )	percentMutateEffectRemoveNeuron++;
						else if ( kmode == 3 )	percentMutateEffectAlterNeuron++;
						else if ( kmode == 4 )	percentMutateEffectAddSynapse++;
						else if ( kmode == 5 )	percentMutateEffectRemoveSynapse++;
						else if ( kmode == 6 )	percentMutateEffectAlterMutable++;
					}
					else if ( jmode == 2 )
					{
						if ( kmode == 1 && percentMutateEffectAddNeuron > 0 )		percentMutateEffectAddNeuron--;
						else if ( kmode == 2 && percentMutateEffectRemoveNeuron > 0 )	percentMutateEffectRemoveNeuron--;
						else if ( kmode == 3 && percentMutateEffectAlterNeuron > 0 )	percentMutateEffectAlterNeuron--;
						else if ( kmode == 4 && percentMutateEffectAddSynapse > 0 )	percentMutateEffectAddSynapse--;
						else if ( kmode == 5 && percentMutateEffectRemoveSynapse > 0 )	percentMutateEffectRemoveSynapse--;
						else if ( kmode == 6 && percentMutateEffectAlterMutable > 0 )	percentMutateEffectAlterMutable--;
					}
				}

				else if ( imode == 12 && mutate_PlasticityFactors )
				{
					// up or down
					unsigned int jmode = randgen->Instance()->get(1,2);

					// which of 4
					unsigned int kmode = randgen->Instance()->get(1,4);

					// factor
					unsigned int factor = randgen->Instance()->get(10,1000);

					if ( jmode == 1 )
					{
						if ( kmode == 1 && minPlasticityStrengthen+factor < maxPlasticityStrengthen )	minPlasticityStrengthen+=factor;
						else if ( kmode == 2 && maxPlasticityStrengthen+factor < 1000000 )		maxPlasticityStrengthen+=factor;
						else if ( kmode == 3 && minPlasticityWeaken+factor < maxPlasticityWeaken )	minPlasticityWeaken+=factor;
						else if ( kmode == 4 && maxPlasticityWeaken+factor < 1000000 )			maxPlasticityWeaken+=factor;
					}
					else
					{
						if ( kmode == 1 && minPlasticityStrengthen > 10+factor  )				minPlasticityStrengthen-=factor;
						else if ( kmode == 2 && maxPlasticityStrengthen > minPlasticityStrengthen+factor )	maxPlasticityStrengthen-=factor;
						else if ( kmode == 3 && minPlasticityWeaken > 100+factor )				minPlasticityWeaken-=factor;
						else if ( kmode == 4 && maxPlasticityWeaken > minPlasticityWeaken+factor )		maxPlasticityWeaken-=factor;
					}
				}

				else runs++;
			}
			else runs++;
		}
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

	void Brainz::copyFrom(const Brainz& otherBrain)
	{
		maxNeurons				= otherBrain.maxNeurons;
		minSynapses				= otherBrain.minSynapses;
		maxSynapses				= otherBrain.maxSynapses;
		percentChanceInhibitoryNeuron		= otherBrain.percentChanceInhibitoryNeuron;
		mutate_percentChanceInhibitoryNeuron	= otherBrain.mutate_percentChanceInhibitoryNeuron;

		percentChanceMotorNeuron		= otherBrain.percentChanceMotorNeuron;
		mutate_percentChanceMotorNeuron		= otherBrain.mutate_percentChanceMotorNeuron;
		percentChancePlasticNeuron		= otherBrain.percentChancePlasticNeuron;
		mutate_percentChancePlasticNeuron	= otherBrain.mutate_percentChancePlasticNeuron;
		minPlasticityStrengthen			= otherBrain.minPlasticityStrengthen;
		maxPlasticityStrengthen			= otherBrain.maxPlasticityStrengthen;
		minPlasticityWeaken			= otherBrain.minPlasticityWeaken;
		maxPlasticityWeaken			= otherBrain.maxPlasticityWeaken;

		mutate_PlasticityFactors		= otherBrain.mutate_PlasticityFactors;
		minFiringThreshold			= otherBrain.minFiringThreshold;
		mutate_minFiringThreshold		= otherBrain.mutate_minFiringThreshold;
		maxFiringThreshold			= otherBrain.maxFiringThreshold;
		mutate_maxFiringThreshold		= otherBrain.mutate_maxFiringThreshold;
		maxDendridicBranches			= otherBrain.maxDendridicBranches;
		mutate_maxDendridicBranches		= otherBrain.mutate_maxDendridicBranches;
		percentChanceConsistentSynapses		= otherBrain.percentChanceConsistentSynapses;
		mutate_percentChanceConsistentSynapses	= otherBrain.mutate_percentChanceConsistentSynapses;
		percentChanceInhibitorySynapses		= otherBrain.percentChanceInhibitorySynapses;
		mutate_percentChanceInhibitorySynapses	= otherBrain.mutate_percentChanceInhibitorySynapses;
		percentChanceSensorySynapse		= otherBrain.percentChanceSensorySynapse;
		mutate_percentChanceSensorySynapse	= otherBrain.mutate_percentChanceSensorySynapse;
		percentMutateEffectAddNeuron		= otherBrain.percentMutateEffectAddNeuron;
		percentMutateEffectRemoveNeuron		= otherBrain.percentMutateEffectRemoveNeuron;
		percentMutateEffectAlterNeuron		= otherBrain.percentMutateEffectAlterNeuron;
		percentMutateEffectAddSynapse		= otherBrain.percentMutateEffectAddSynapse;
		percentMutateEffectRemoveSynapse	= otherBrain.percentMutateEffectRemoveSynapse;
		percentMutateEffectAlterMutable		= otherBrain.percentMutateEffectAlterMutable;
		mutate_MutateEffects			= otherBrain.mutate_MutateEffects;

		for ( unsigned int i = 0; i < otherBrain.ArchNeurons.size(); i++ )
		{
			ArchNeuronz an;
			const ArchNeuronz *oan = &otherBrain.ArchNeurons[i];

			an.isInhibitory = oan->isInhibitory;

			an.hasConsistentSynapses = oan->hasConsistentSynapses;
			an.hasInhibitorySynapses = oan->hasInhibitorySynapses;
			an.firingThreshold = oan->firingThreshold;
			an.dendridicBranches = oan->dendridicBranches;

			an.isMotor = oan->isMotor;
			an.motorID = oan->motorID;
			an.isPlastic = oan->isPlastic;
			an.isPlastic = oan->isPlastic;
			an.plasticityStrengthen = oan->plasticityStrengthen;
			an.plasticityWeaken = oan->plasticityWeaken;

			// inputs
			for ( unsigned int j = 0; j < oan->ArchSynapses.size(); j++ )
			{
				ArchSynapse as;
				const ArchSynapse *oas = &oan->ArchSynapses[j];

				as.isSensorNeuron	= oas->isSensorNeuron;
				as.neuronID		= oas->neuronID;
				as.dendriteBranch	= oas->dendriteBranch;
				as.weight		= oas->weight;
				an.ArchSynapses.push_back( as );
			}
			ArchNeurons.push_back( an );
		}
	}

	void Brainz::mergeFrom(const Brainz& otherBrain1, const Brainz& otherBrain2)
	{
		maxNeurons				= otherBrain1.maxNeurons;
		minSynapses				= otherBrain1.minSynapses;
		maxSynapses				= otherBrain1.maxSynapses;
		percentChanceInhibitoryNeuron		= otherBrain1.percentChanceInhibitoryNeuron;
		mutate_percentChanceInhibitoryNeuron	= otherBrain1.mutate_percentChanceInhibitoryNeuron;

		percentChanceMotorNeuron		= otherBrain1.percentChanceMotorNeuron;
		mutate_percentChanceMotorNeuron		= otherBrain1.mutate_percentChanceMotorNeuron;
		percentChancePlasticNeuron		= otherBrain1.percentChancePlasticNeuron;
		mutate_percentChancePlasticNeuron	= otherBrain1.mutate_percentChancePlasticNeuron;
		minPlasticityStrengthen			= otherBrain1.minPlasticityStrengthen;
		maxPlasticityStrengthen			= otherBrain1.maxPlasticityStrengthen;
		minPlasticityWeaken			= otherBrain1.minPlasticityWeaken;
		maxPlasticityWeaken			= otherBrain1.maxPlasticityWeaken;

		mutate_PlasticityFactors		= otherBrain1.mutate_PlasticityFactors;
		minFiringThreshold			= otherBrain1.minFiringThreshold;
		mutate_minFiringThreshold		= otherBrain1.mutate_minFiringThreshold;
		maxFiringThreshold			= otherBrain1.maxFiringThreshold;
		mutate_maxFiringThreshold		= otherBrain1.mutate_maxFiringThreshold;
		maxDendridicBranches			= otherBrain1.maxDendridicBranches;
		mutate_maxDendridicBranches		= otherBrain1.mutate_maxDendridicBranches;
		percentChanceConsistentSynapses		= otherBrain1.percentChanceConsistentSynapses;
		mutate_percentChanceConsistentSynapses	= otherBrain1.mutate_percentChanceConsistentSynapses;
		percentChanceInhibitorySynapses		= otherBrain1.percentChanceInhibitorySynapses;
		mutate_percentChanceInhibitorySynapses	= otherBrain1.mutate_percentChanceInhibitorySynapses;
		percentChanceSensorySynapse		= otherBrain1.percentChanceSensorySynapse;
		mutate_percentChanceSensorySynapse	= otherBrain1.mutate_percentChanceSensorySynapse;
		percentMutateEffectAddNeuron		= otherBrain1.percentMutateEffectAddNeuron;
		percentMutateEffectRemoveNeuron		= otherBrain1.percentMutateEffectRemoveNeuron;
		percentMutateEffectAlterNeuron		= otherBrain1.percentMutateEffectAlterNeuron;
		percentMutateEffectAddSynapse		= otherBrain1.percentMutateEffectAddSynapse;
		percentMutateEffectRemoveSynapse	= otherBrain1.percentMutateEffectRemoveSynapse;
		percentMutateEffectAlterMutable		= otherBrain1.percentMutateEffectAlterMutable;
		mutate_MutateEffects			= otherBrain1.mutate_MutateEffects;

		// take biggest
		unsigned int loops = otherBrain1.ArchNeurons.size();
		if ( otherBrain2.ArchNeurons.size() < loops ) loops = otherBrain2.ArchNeurons.size();

		bool even = false;
		for ( unsigned int i = 0; i < loops; i++ )
		{
			even = !even;
			ArchNeuronz an;

			const ArchNeuronz *oan;

			if ( i < otherBrain1.ArchNeurons.size() && even )
				oan = &otherBrain1.ArchNeurons[i];

			else //if ( i < otherBrain2.ArchNeurons.size() && !even )
				oan = &otherBrain2.ArchNeurons[i];

			an.isInhibitory = oan->isInhibitory;

			an.hasConsistentSynapses = oan->hasConsistentSynapses;
			an.hasInhibitorySynapses = oan->hasInhibitorySynapses;
			an.firingThreshold = oan->firingThreshold;
			an.dendridicBranches = oan->dendridicBranches;

			an.isMotor = oan->isMotor;
			an.motorID = oan->motorID;
			an.isPlastic = oan->isPlastic;
			an.isPlastic = oan->isPlastic;
			an.plasticityStrengthen = oan->plasticityStrengthen;
			an.plasticityWeaken = oan->plasticityWeaken;

			// inputs
			for ( unsigned int j = 0; j < oan->ArchSynapses.size(); j++ )
			{
				ArchSynapse as;
				const ArchSynapse *oas = &oan->ArchSynapses[j];

				as.isSensorNeuron	= oas->isSensorNeuron;
				as.neuronID		= oas->neuronID;
				as.dendriteBranch	= oas->dendriteBranch;
				as.weight		= oas->weight;
				an.ArchSynapses.push_back( as );
			}
			ArchNeurons.push_back( an );
		}
	}

// SERIALIZE FUNC

	void Brainz::setArch(string* content)
	{
		string contentCopy = *content;
		string line = parseH->Instance()->returnUntillStrip( "\n", contentCopy );
		while ( !line.empty() )
		{
			// neuron(ft=24|iwr=20|mtr=4|inputs(|s,78,6|s,186,-12|s,123,10|n,19,5|n,3,3|n,11,-19));

			if ( parseH->Instance()->beginMatchesStrip( "n(", line ) )
			{
				ArchNeuronz an;
//				unsigned int nid = (ArchNeurons.size()-1);
	
				if ( parseH->Instance()->beginMatchesStrip( "i=", line ) )
				{
					string II = parseH->Instance()->returnUntillStrip( "|", line );
					//cerr << "II: " << II  << endl;
					int isIt;
					if(EOF == sscanf(II.c_str(), "%d", &isIt))				cerr << "ERROR INSERTING CRITTER" << endl;
					if ( isIt == 1 ) an.isInhibitory = true;
				}

				if ( parseH->Instance()->beginMatchesStrip( "cs=", line ) )
				{
					string CS = parseH->Instance()->returnUntillStrip( "|", line );
					//cerr << "II: " << II  << endl;
					int isItC;
					if(EOF == sscanf(CS.c_str(), "%d", &isItC))				cerr << "ERROR INSERTING CRITTER" << endl;
					if ( isItC == 1 ) an.hasConsistentSynapses = true;

					if ( parseH->Instance()->beginMatchesStrip( "is=", line ) )
					{
						string IS = parseH->Instance()->returnUntillStrip( "|", line );
						//cerr << "II: " << II  << endl;
						int isIt;
						if(EOF == sscanf(IS.c_str(), "%d", &isIt))				cerr << "ERROR INSERTING CRITTER" << endl;
						if ( isIt == 1 ) an.hasInhibitorySynapses = true;
					}
				}

				if ( parseH->Instance()->beginMatchesStrip( "f=", line ) )
				{
					string FT = parseH->Instance()->returnUntillStrip( "|", line );
					//cerr << "FT: " << FT  << endl;
					if(EOF == sscanf(FT.c_str(), "%d", &an.firingThreshold))		cerr << "ERROR INSERTING CRITTER" << endl;
				}
	
				if ( parseH->Instance()->beginMatchesStrip( "d=", line ) )
				{
					string DB = parseH->Instance()->returnUntillStrip( "|", line );
					//cerr << "IWR: " << IWR  << endl;
					if(EOF == sscanf(DB.c_str(), "%d", &an.dendridicBranches))		cerr << "ERROR INSERTING CRITTER" << endl;
				}
	
				if ( parseH->Instance()->beginMatchesStrip( "m=", line ) )
				{
					string MTR = parseH->Instance()->returnUntillStrip( "|", line );
					//cerr << "MTR: " << MTR  << endl;
					if(EOF == sscanf(MTR.c_str(), "%d", &an.motorID))			cerr << "ERROR INSERTING CRITTER" << endl;
					an.isMotor = true;
				}

				if ( parseH->Instance()->beginMatchesStrip( "p=", line ) )
				{
					string PLAS = parseH->Instance()->returnUntillStrip( ",", line );
					string PLAW = parseH->Instance()->returnUntillStrip( "|", line );
					if(EOF == sscanf(PLAS.c_str(), "%d", &an.plasticityStrengthen))			cerr << "ERROR INSERTING CRITTER" << endl;
					if(EOF == sscanf(PLAW.c_str(), "%d", &an.plasticityWeaken))			cerr << "ERROR INSERTING CRITTER" << endl;
					an.isPlastic = true;
				}

				while ( parseH->Instance()->beginMatchesStrip( "s=", line ) )
				{
						ArchSynapse as;

						string SY = parseH->Instance()->returnUntillStrip( "|", line );
						string isSensorNeuron	= parseH->Instance()->returnUntillStrip( ",", SY );
						string neuronID		= parseH->Instance()->returnUntillStrip( ",", SY );
						string dendriteBranch	= parseH->Instance()->returnUntillStrip( ",", SY );
						string weight	= SY;

						int isIt;
						if(EOF == sscanf(isSensorNeuron.c_str(), "%d", &isIt))			cerr << "ERROR INSERTING CRITTER" << endl;
						if ( isIt == 1 ) as.isSensorNeuron = true;
	
						if(EOF == sscanf(neuronID.c_str(), "%d", &as.neuronID))			cerr << "ERROR INSERTING CRITTER" << endl;
						if(EOF == sscanf(dendriteBranch.c_str(), "%d", &as.dendriteBranch))	cerr << "ERROR INSERTING CRITTER" << endl;
						if(EOF == sscanf(weight.c_str(), "%f", &as.weight))			cerr << "ERROR INSERTING CRITTER" << endl;
						an.ArchSynapses.push_back( as );
				}

				ArchNeurons.push_back( an );
			}

// 			else if ( parseH->Instance()->beginMatchesStrip( "numberOfInputs=", line ) )
// 			{
// 				string Holder = parseH->Instance()->returnUntillStrip( ";", line );
// 				if(EOF == sscanf(Holder.c_str(), "%d", &numberOfInputs))				cerr << "ERROR INSERTING CRITTER" << endl;
// 			}

// 			else if ( parseH->Instance()->beginMatchesStrip( "numberOfOutputs=", line ) )
// 			{
// 				string Holder = parseH->Instance()->returnUntillStrip( ";", line );
// 				if(EOF == sscanf(Holder.c_str(), "%d", &numberOfOutputs))				cerr << "ERROR INSERTING CRITTER" << endl;
// 			}

			else if ( parseH->Instance()->beginMatchesStrip( "maxNeurons=", line ) )
			{
				string Holder = parseH->Instance()->returnUntillStrip( ";", line );
				if(EOF == sscanf(Holder.c_str(), "%d", &maxNeurons))					cerr << "ERROR INSERTING CRITTER" << endl;
			}

			else if ( parseH->Instance()->beginMatchesStrip( "minSynapses=", line ) )
			{
				string Holder = parseH->Instance()->returnUntillStrip( ";", line );
				if(EOF == sscanf(Holder.c_str(), "%d", &minSynapses))					cerr << "ERROR INSERTING CRITTER" << endl;
			}

			else if ( parseH->Instance()->beginMatchesStrip( "maxSynapses=", line ) )
			{
				string Holder = parseH->Instance()->returnUntillStrip( ";", line );
				if(EOF == sscanf(Holder.c_str(), "%d", &maxSynapses))					cerr << "ERROR INSERTING CRITTER" << endl;
			}

			else if ( parseH->Instance()->beginMatchesStrip( "percentChanceInhibitoryNeuron=", line ) )
			{
				string Holder = parseH->Instance()->returnUntillStrip( ";", line );
				if(EOF == sscanf(Holder.c_str(), "%d", &percentChanceInhibitoryNeuron))			cerr << "ERROR INSERTING CRITTER" << endl;
			}
				else if ( parseH->Instance()->beginMatchesStrip( "mutate_percentChanceInhibitoryNeuron=", line ) )
				{
					string Holder = parseH->Instance()->returnUntillStrip( ";", line );
					int result;
					if(EOF == sscanf(Holder.c_str(), "%d", &result))			cerr << "ERROR INSERTING CRITTER" << endl;
					if ( result == 1 )	mutate_percentChanceInhibitoryNeuron = true;
					else			mutate_percentChanceInhibitoryNeuron = false;
				}

			else if ( parseH->Instance()->beginMatchesStrip( "percentChanceConsistentSynapses=", line ) )
			{
				string Holder = parseH->Instance()->returnUntillStrip( ";", line );
				if(EOF == sscanf(Holder.c_str(), "%d", &percentChanceConsistentSynapses))		cerr << "ERROR INSERTING CRITTER" << endl;
			}
				else if ( parseH->Instance()->beginMatchesStrip( "mutate_percentChanceConsistentSynapses=", line ) )
				{
					string Holder = parseH->Instance()->returnUntillStrip( ";", line );
					int result;
					if(EOF == sscanf(Holder.c_str(), "%d", &result))			cerr << "ERROR INSERTING CRITTER" << endl;
					if ( result == 1 )	mutate_percentChanceConsistentSynapses = true;
					else			mutate_percentChanceConsistentSynapses = false;
				}

			else if ( parseH->Instance()->beginMatchesStrip( "percentChanceInhibitorySynapses=", line ) )
			{
				string Holder = parseH->Instance()->returnUntillStrip( ";", line );
				if(EOF == sscanf(Holder.c_str(), "%d", &percentChanceInhibitorySynapses))		cerr << "ERROR INSERTING CRITTER" << endl;
			}
				else if ( parseH->Instance()->beginMatchesStrip( "mutate_percentChanceInhibitorySynapses=", line ) )
				{
					string Holder = parseH->Instance()->returnUntillStrip( ";", line );
					int result;
					if(EOF == sscanf(Holder.c_str(), "%d", &result))			cerr << "ERROR INSERTING CRITTER" << endl;
					if ( result == 1 )	mutate_percentChanceInhibitorySynapses = true;
					else			mutate_percentChanceInhibitorySynapses = false;
				}

			else if ( parseH->Instance()->beginMatchesStrip( "percentChanceMotorNeuron=", line ) )
			{
				string Holder = parseH->Instance()->returnUntillStrip( ";", line );
				if(EOF == sscanf(Holder.c_str(), "%d", &percentChanceMotorNeuron))			cerr << "ERROR INSERTING CRITTER" << endl;
			}
				else if ( parseH->Instance()->beginMatchesStrip( "mutate_percentChanceMotorNeuron=", line ) )
				{
					string Holder = parseH->Instance()->returnUntillStrip( ";", line );
					int result;
					if(EOF == sscanf(Holder.c_str(), "%d", &result))			cerr << "ERROR INSERTING CRITTER" << endl;
					if ( result == 1 )	mutate_percentChanceMotorNeuron = true;
					else			mutate_percentChanceMotorNeuron = false;
				}

			else if ( parseH->Instance()->beginMatchesStrip( "percentChancePlasticNeuron=", line ) )
			{
				string Holder = parseH->Instance()->returnUntillStrip( ";", line );
				if(EOF == sscanf(Holder.c_str(), "%d", &percentChancePlasticNeuron))			cerr << "ERROR INSERTING CRITTER" << endl;
			}
				else if ( parseH->Instance()->beginMatchesStrip( "mutate_percentChancePlasticNeuron=", line ) )
				{
					string Holder = parseH->Instance()->returnUntillStrip( ";", line );
					int result;
					if(EOF == sscanf(Holder.c_str(), "%d", &result))			cerr << "ERROR INSERTING CRITTER" << endl;
					if ( result == 1 )	mutate_percentChancePlasticNeuron = true;
					else			mutate_percentChancePlasticNeuron = false;
				}

			else if ( parseH->Instance()->beginMatchesStrip( "percentChanceSensorySynapse=", line ) )
			{
				string Holder = parseH->Instance()->returnUntillStrip( ";", line );
				if(EOF == sscanf(Holder.c_str(), "%d", &percentChanceSensorySynapse))			cerr << "ERROR INSERTING CRITTER" << endl;
			}
				else if ( parseH->Instance()->beginMatchesStrip( "mutate_percentChanceSensorySynapse=", line ) )
				{
					string Holder = parseH->Instance()->returnUntillStrip( ";", line );
					int result;
					if(EOF == sscanf(Holder.c_str(), "%d", &result))			cerr << "ERROR INSERTING CRITTER" << endl;
					if ( result == 1 )	mutate_percentChanceSensorySynapse = true;
					else			mutate_percentChanceSensorySynapse = false;
				}

			else if ( parseH->Instance()->beginMatchesStrip( "minFiringThreshold=", line ) )
			{
				string Holder = parseH->Instance()->returnUntillStrip( ";", line );
				if(EOF == sscanf(Holder.c_str(), "%d", &minFiringThreshold))				cerr << "ERROR INSERTING CRITTER" << endl;
			}
				else if ( parseH->Instance()->beginMatchesStrip( "mutate_minFiringThreshold=", line ) )
				{
					string Holder = parseH->Instance()->returnUntillStrip( ";", line );
					int result;
					if(EOF == sscanf(Holder.c_str(), "%d", &result))			cerr << "ERROR INSERTING CRITTER" << endl;
					if ( result == 1 )	mutate_minFiringThreshold = true;
					else			mutate_minFiringThreshold = false;
				}

			else if ( parseH->Instance()->beginMatchesStrip( "maxFiringThreshold=", line ) )
			{
				string Holder = parseH->Instance()->returnUntillStrip( ";", line );
				if(EOF == sscanf(Holder.c_str(), "%d", &maxFiringThreshold))				cerr << "ERROR INSERTING CRITTER" << endl;
			}
				else if ( parseH->Instance()->beginMatchesStrip( "mutate_maxFiringThreshold=", line ) )
				{
					string Holder = parseH->Instance()->returnUntillStrip( ";", line );
					int result;
					if(EOF == sscanf(Holder.c_str(), "%d", &result))			cerr << "ERROR INSERTING CRITTER" << endl;
					if ( result == 1 )	mutate_maxFiringThreshold = true;
					else			mutate_maxFiringThreshold = false;
				}

			else if ( parseH->Instance()->beginMatchesStrip( "maxDendridicBranches=", line ) )
			{
				string Holder = parseH->Instance()->returnUntillStrip( ";", line );
				if(EOF == sscanf(Holder.c_str(), "%d", &maxDendridicBranches))				cerr << "ERROR INSERTING CRITTER" << endl;
			}
				else if ( parseH->Instance()->beginMatchesStrip( "mutate_maxDendridicBranches=", line ) )
				{
					string Holder = parseH->Instance()->returnUntillStrip( ";", line );
					int result;
					if(EOF == sscanf(Holder.c_str(), "%d", &result))			cerr << "ERROR INSERTING CRITTER" << endl;
					if ( result == 1 )	mutate_maxDendridicBranches = true;
					else			mutate_maxDendridicBranches = false;
				}

// 			else if ( parseH->Instance()->beginMatchesStrip( "percentMutation=", line ) )
// 			{
// 				string Holder = parseH->Instance()->returnUntillStrip( ";", line );
// 				if(EOF == sscanf(Holder.c_str(), "%d", &percentMutation))				cerr << "ERROR INSERTING CRITTER" << endl;
// 			}
// 				else if ( parseH->Instance()->beginMatchesStrip( "mutate_percentMutation=", line ) )
// 				{
// 					string Holder = parseH->Instance()->returnUntillStrip( ";", line );
// 					int result;
// 					if(EOF == sscanf(Holder.c_str(), "%d", &result))			cerr << "ERROR INSERTING CRITTER" << endl;
// 					if ( result == 1 )	mutate_percentMutation = true;
// 					else			mutate_percentMutation = false;
// 				}

			else if ( parseH->Instance()->beginMatchesStrip( "percentMutateEffectAddNeuron=", line ) )
			{
				string Holder = parseH->Instance()->returnUntillStrip( ";", line );
				if(EOF == sscanf(Holder.c_str(), "%d", &percentMutateEffectAddNeuron))				cerr << "ERROR INSERTING CRITTER" << endl;
			}

			else if ( parseH->Instance()->beginMatchesStrip( "percentMutateEffectRemoveNeuron=", line ) )
			{
				string Holder = parseH->Instance()->returnUntillStrip( ";", line );
				if(EOF == sscanf(Holder.c_str(), "%d", &percentMutateEffectRemoveNeuron))				cerr << "ERROR INSERTING CRITTER" << endl;
			}

			else if ( parseH->Instance()->beginMatchesStrip( "percentMutateEffectAlterNeuron=", line ) )
			{
				string Holder = parseH->Instance()->returnUntillStrip( ";", line );
				if(EOF == sscanf(Holder.c_str(), "%d", &percentMutateEffectAlterNeuron))				cerr << "ERROR INSERTING CRITTER" << endl;
			}

			else if ( parseH->Instance()->beginMatchesStrip( "percentMutateEffectAddSynapse=", line ) )
			{
				string Holder = parseH->Instance()->returnUntillStrip( ";", line );
				if(EOF == sscanf(Holder.c_str(), "%d", &percentMutateEffectAddSynapse))				cerr << "ERROR INSERTING CRITTER" << endl;
			}

			else if ( parseH->Instance()->beginMatchesStrip( "percentMutateEffectRemoveSynapse=", line ) )
			{
				string Holder = parseH->Instance()->returnUntillStrip( ";", line );
				if(EOF == sscanf(Holder.c_str(), "%d", &percentMutateEffectRemoveSynapse))				cerr << "ERROR INSERTING CRITTER" << endl;
			}

			else if ( parseH->Instance()->beginMatchesStrip( "percentMutateEffectAlterMutable=", line ) )
			{
				string Holder = parseH->Instance()->returnUntillStrip( ";", line );
				if(EOF == sscanf(Holder.c_str(), "%d", &percentMutateEffectAlterMutable))				cerr << "ERROR INSERTING CRITTER" << endl;
			}


				else if ( parseH->Instance()->beginMatchesStrip( "mutate_MutateEffects=", line ) )
				{
					string Holder = parseH->Instance()->returnUntillStrip( ";", line );
					int result;
					if(EOF == sscanf(Holder.c_str(), "%d", &result))			cerr << "ERROR INSERTING CRITTER" << endl;
					if ( result == 1 )	mutate_MutateEffects = true;
					else			mutate_MutateEffects = false;
				}

			else if ( parseH->Instance()->beginMatchesStrip( "minPlasticityStrengthen=", line ) )
			{
				string Holder = parseH->Instance()->returnUntillStrip( ";", line );
				if(EOF == sscanf(Holder.c_str(), "%d", &minPlasticityStrengthen))				cerr << "ERROR INSERTING CRITTER" << endl;
			}
			else if ( parseH->Instance()->beginMatchesStrip( "maxPlasticityStrengthen=", line ) )
			{
				string Holder = parseH->Instance()->returnUntillStrip( ";", line );
				if(EOF == sscanf(Holder.c_str(), "%d", &maxPlasticityStrengthen))				cerr << "ERROR INSERTING CRITTER" << endl;
			}
			else if ( parseH->Instance()->beginMatchesStrip( "minPlasticityWeaken=", line ) )
			{
				string Holder = parseH->Instance()->returnUntillStrip( ";", line );
				if(EOF == sscanf(Holder.c_str(), "%d", &minPlasticityWeaken))				cerr << "ERROR INSERTING CRITTER" << endl;
			}
			else if ( parseH->Instance()->beginMatchesStrip( "maxPlasticityWeaken=", line ) )
			{
				string Holder = parseH->Instance()->returnUntillStrip( ";", line );
				if(EOF == sscanf(Holder.c_str(), "%d", &maxPlasticityWeaken))				cerr << "ERROR INSERTING CRITTER" << endl;
			}

				else if ( parseH->Instance()->beginMatchesStrip( "mutate_PlasticityFactors=", line ) )
				{
					string Holder = parseH->Instance()->returnUntillStrip( ";", line );
					int result;
					if(EOF == sscanf(Holder.c_str(), "%d", &result))			cerr << "ERROR INSERTING CRITTER" << endl;
					if ( result == 1 )	mutate_PlasticityFactors = true;
					else			mutate_PlasticityFactors = false;
				}

			line = parseH->Instance()->returnUntillStrip( "\n", contentCopy );
		}
	}
	
	string* Brainz::getArch()
	{
			stringstream buf;
	
			buf << "maxNeurons="				<< maxNeurons << ";" << endl;
			buf << "minSynapses="				<< minSynapses << ";" << endl;
			buf << "maxSynapses="				<< maxSynapses << ";" << endl;

			buf << "percentChanceInhibitoryNeuron="		<< percentChanceInhibitoryNeuron << ";" << endl;
				buf << "mutate_percentChanceInhibitoryNeuron="	<< mutate_percentChanceInhibitoryNeuron << ";" << endl;
			buf << "percentChanceMotorNeuron="		<< percentChanceMotorNeuron << ";" << endl;
				buf << "mutate_percentChanceMotorNeuron="	<< mutate_percentChanceMotorNeuron << ";" << endl;
			buf << "percentChancePlasticNeuron="		<< percentChancePlasticNeuron << ";" << endl;
				buf << "mutate_percentChancePlasticNeuron="	<< mutate_percentChancePlasticNeuron << ";" << endl;
			buf << "minPlasticityStrengthen="		<< minPlasticityStrengthen << ";" << endl;
			buf << "maxPlasticityStrengthen="		<< maxPlasticityStrengthen << ";" << endl;
			buf << "minPlasticityWeaken="			<< minPlasticityWeaken << ";" << endl;
			buf << "maxPlasticityWeaken="			<< maxPlasticityWeaken << ";" << endl;
				buf << "mutate_PlasticityFactors="		<< mutate_PlasticityFactors << ";" << endl;

			buf << "minFiringThreshold="			<< minFiringThreshold << ";" << endl;
				buf << "mutate_minFiringThreshold="		<< mutate_minFiringThreshold << ";" << endl;
			buf << "maxFiringThreshold="			<< maxFiringThreshold << ";" << endl;
				buf << "mutate_maxFiringThreshold="		<< mutate_maxFiringThreshold << ";" << endl;
			buf << "maxDendridicBranches="			<< maxDendridicBranches << ";" << endl;
				buf << "mutate_maxDendridicBranches="		<< mutate_maxDendridicBranches << ";" << endl;
	
			buf << "percentChanceConsistentSynapses="	<< percentChanceConsistentSynapses << ";" << endl;
				buf << "mutate_percentChanceConsistentSynapses="<< mutate_percentChanceConsistentSynapses << ";" << endl;
			buf << "percentChanceInhibitorySynapses="	<< percentChanceInhibitorySynapses << ";" << endl;
				buf << "mutate_percentChanceInhibitorySynapses="<< mutate_percentChanceInhibitorySynapses << ";" << endl;
			buf << "percentChanceSensorySynapse="		<< percentChanceSensorySynapse << ";" << endl;
				buf << "mutate_percentChanceSensorySynapse="	<< mutate_percentChanceSensorySynapse << ";" << endl;

			buf << "percentMutateEffectAddNeuron="		<< percentMutateEffectAddNeuron << ";" << endl;
			buf << "percentMutateEffectRemoveNeuron="	<< percentMutateEffectRemoveNeuron << ";" << endl;
			buf << "percentMutateEffectAlterNeuron="	<< percentMutateEffectAlterNeuron << ";" << endl;
			buf << "percentMutateEffectAddSynapse="		<< percentMutateEffectAddSynapse << ";" << endl;
			buf << "percentMutateEffectRemoveSynapse="	<< percentMutateEffectRemoveSynapse << ";" << endl;
			buf << "percentMutateEffectAlterMutable="	<< percentMutateEffectAlterMutable << ";" << endl;

				buf << "mutate_MutateEffects="			<< mutate_MutateEffects << ";" << endl;
	
	
			// neuronal arch & connections
			for ( unsigned int i = 0; i < ArchNeurons.size(); i++ )
			{
				// neuron info
				buf << "n(";
	
				if ( ArchNeurons[i].isInhibitory )
					buf << "i=1|";
				else
					buf << "i=0|";
	
				if ( ArchNeurons[i].hasConsistentSynapses )
				{
					buf << "cs=1|";
					if ( ArchNeurons[i].hasInhibitorySynapses )
						buf << "is=1|";
					else
						buf << "is=0|";
				}
				else
					buf << "cs=0|";
	
				buf << "f=" << ArchNeurons[i].firingThreshold << "|";
				buf << "d=" << ArchNeurons[i].dendridicBranches << "|";
				if ( ArchNeurons[i].isMotor ) buf << "m=" << ArchNeurons[i].motorID << "|";
				if ( ArchNeurons[i].isPlastic ) buf << "p=" << ArchNeurons[i].plasticityStrengthen << "," << ArchNeurons[i].plasticityWeaken << "|";
		
				// inputs
				for ( unsigned int j = 0; j < ArchNeurons[i].ArchSynapses.size(); j++ )
				{
					buf << "s=";
						// sensor or inter neuron
						if ( ArchNeurons[i].ArchSynapses[j].isSensorNeuron )
							buf << "1";
						else
							buf << "0";
						buf << "," << ArchNeurons[i].ArchSynapses[j].neuronID;
						buf << "," << ArchNeurons[i].ArchSynapses[j].dendriteBranch;
						buf << "," << ArchNeurons[i].ArchSynapses[j].weight;
					buf << "|";
				}
				buf << ");\n";
			}

		archBuffer = buf.str();
		return &archBuffer;
	}

Brainz::~Brainz()
{
}
