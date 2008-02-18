#include "brain.h"

Brain::Brain()
{

	// brain properties
	symmetric		= true;

	// neural properties
	percentSensoryConns	= 10;
	percentMotor		= 10;

	absmaxneurons		= 150;
	absmaxconns		= 150;

	minneurons		= 20;

	minconns		= 1;

	mutatepercent		= 2;
}

void Brain::process()
{
	neuronsfired = 0;

	// clear Motor Outputs
	for ( unsigned int i=0; i < totalOutputs; i++ ) Outputs[i]->output = 0;

	for ( unsigned int i=0; i < totalneurons; i++ )
	{
		NeuronInter *n = Neurons[i];

		n->process();

		// if neuron fires
		if ( n->waitoutput != 0 )
		{
			neuronsfired++;

			// motor neuron check & exec
			if ( n->isMotor )
			{
				Outputs[n->MotorFunc]->output++;
				//cerr << "neuron " << i << " fired, motor is " << Neurons[i]->MotorFunc << " total now " << Outputs[Neurons[i]->MotorFunc]->output << endl;
			}
		}
	}

	// commit outputs at the end
	for ( unsigned int i=0; i < totalneurons; i++ ) Neurons[i]->output = Neurons[i]->waitoutput;
}

void Brain::setupInputs(unsigned int number)
{
	Inputs.clear();
	for ( unsigned int i=0; i < number; i++ ) Inputs.push_back( new NeuronSensor() );
	totalInputs = number;
}

void Brain::setupOutputs(unsigned int number)
{
	Outputs.clear();
	for ( unsigned int i=0; i < number; i++ ) Outputs.push_back( new NeuronSensor() );
	totalOutputs = number;
}

void Brain::setupArchitecture()
{
	Neurons.clear();

	totalneurons = 0;
	totalconnections = 0;

	// count neurons, which is neuronArch size
	totalneurons = NeuronArch.size();

	// first create all neurons
	for ( unsigned int i=0; i < totalneurons; i++ )
	{
		NeuronInter *n = new NeuronInter;
		n->fireThresh	= NeuronArch[i]->fireThresh;
		n->iWeightRange	= NeuronArch[i]->iWeightRange;
		n->isMotor	= NeuronArch[i]->isMotor;
		n->MotorFunc	= NeuronArch[i]->MotorFunc;
		Neurons.push_back( n );
	}

	for ( unsigned int i=0; i < totalneurons; i++ )
	{
		ArchNeuron *an = NeuronArch[i];
		NeuronInter *n = Neurons[i];
		for ( unsigned int j=0; j < an->connections.size(); j++ )
		{
			if ( an->connections[j]->type == 'n' )
			{
				n->connec( &Neurons[ an->connections[j]->id ]->output, an->connections[j]->weight );
			}
			else if ( an->connections[j]->id < totalInputs )
			{
				if ( an->connections[j]->type == 's' )
				{
					n->connec( &Inputs[ an->connections[j]->id ]->output, an->connections[j]->weight );
				}
			}
			else
			{
				cerr << "error, cannot link to input neuron " << an->connections[j]->id << endl;
			}

			// count connections
			totalconnections++;
		}
	}
}

void Brain::randomArchitecture()
{
	NeuronArch.clear();

	// random amount of neurons
	unsigned int nAmount = randgen.get( minneurons, absmaxneurons );

	// create the neurons
	for ( unsigned i = 0; i < nAmount; i++ ) addRandomArchNeuron();

	// link the neurons
	for ( unsigned i = 0; i < nAmount; i++ )
	{
		// random amount of connections
		unsigned int cAmount = randgen.get( minconns, absmaxconns );

		for ( unsigned j = 0; j < cAmount; j++ ) addRandomArchConnection(i);
	}
}

unsigned int Brain::addRandomArchNeuron()
{
	unsigned int ThreshMin = 10;
	unsigned int ThreshMax = 100;
	unsigned int MaxWeightRange = 20;

	ArchNeuron *n = new ArchNeuron;
	n->fireThresh	= randgen.get( ThreshMin, ThreshMax );
	n->iWeightRange	= randgen.get( 1, MaxWeightRange );
	n->isMotor = false;

	if ( randgen.get( 1, 100 ) <= percentMotor )
	{
		n->isMotor = true;
		n->MotorFunc = randgen.get( 0, totalOutputs-1 );
	}

	NeuronArch.push_back( n );
 	return (NeuronArch.size()-1);
}

unsigned int Brain::addRandomArchConnection(unsigned int parentneuron)
{
	ArchConnection *c = new ArchConnection;

	// type
	c->type = 'n';
	if ( randgen.get( 1, 100 ) <= percentSensoryConns ) c->type = 's';

	// id
	if ( c->type == 's' ) c->id = randgen.get( 0, totalInputs-1 );
	else if ( c->type == 'n' )
	{
		c->id = randgen.get( 0, NeuronArch.size()-1 );
		while ( c->id == parentneuron )
		{
			c->id = randgen.get( 0, NeuronArch.size()-1 );
		}
	}
	else exit(0);

	// weight
	c->weight = randgen.get( 1, NeuronArch[parentneuron]->iWeightRange );

	// reverse 1 in 2;
	if ( randgen.get(1,2)==1 ) c->weight = (c->weight * -1);

	NeuronArch[parentneuron]->connections.push_back( c );
 	return (NeuronArch[parentneuron]->connections.size()-1);
}

void Brain::mutate()
{
	// have to do count cuz setupArch not done yet
	totalneurons		= NeuronArch.size();
	totalconnections	= 0;
	for ( unsigned int i = 0; i < totalneurons; i++ ) totalconnections += NeuronArch[i]->connections.size();

	unsigned int runs = randgen.get(1, (int)(totalconnections/(100/mutatepercent)));
	for ( unsigned int i=0; i < runs; i++ )
	{

		unsigned int mode = randgen.get(1,30);

		// remove a neuron
			if ( mode == 1 )
			{
				// don't go under minimum neurons
				//if ( NeuronArch.size() > minneurons )
				//{
					// pick a random neuron
					unsigned int nid = randgen.get( 0, NeuronArch.size()-1 );
					//cerr << "\t-N " << nid << endl;

					// first remove all connections to this neuron, FIXME remove neuron too if no connections are left
					for ( unsigned int i=0; i < NeuronArch.size(); i++ )
					{
						for ( unsigned int j=0; j < NeuronArch[i]->connections.size(); j++ )
						{
							if ( NeuronArch[i]->connections[j]->type == 'n' )
							{
								if ( NeuronArch[i]->connections[j]->id == nid )
								{
									delete NeuronArch[i]->connections[j];
									NeuronArch[i]->connections.erase(NeuronArch[i]->connections.begin()+j);
									j--;
								}
								// if higher id drop one
								else if ( NeuronArch[i]->connections[j]->id > nid )
								{
									NeuronArch[i]->connections[j]->id--;
								}
							}
						}
					}

					// remove the neuron itself, and all its connections
//					for ( unsigned int c=0; c < NeuronArch[nid]->connections.size(); c++ ) delete NeuronArch[nid]->connections[c];
					delete NeuronArch[nid];
					NeuronArch.erase(NeuronArch.begin()+nid);
				//}
			}

		// add a new neuron
			else if ( mode == 2 )
			{
				if ( NeuronArch.size() < absmaxneurons )
				{
					//cerr << "\t+N " << nid << endl;
					unsigned int nid = addRandomArchNeuron();

					// random amount of connections
					unsigned int cAmount = randgen.get( minconns, absmaxconns );
					for ( unsigned j = 0; j < cAmount; j++ )
					{
						addRandomArchConnection(nid);
					}
				}
			}

		// do something to a random input
			else
			{
				// pick a random neuron
				unsigned int nid = randgen.get( 0, NeuronArch.size()-1 );

				unsigned int imode = randgen.get(1,2);

				// add a new connection
				if ( imode == 1 )
				{
					// don't go over maximum connections
					if ( NeuronArch[nid]->connections.size() < absmaxconns )
					{
						//cerr << "\t+C " << nid << endl;
						addRandomArchConnection(nid);
					}
				}
				// remove a random connection
				else
				{
					// don't go under minimum connections
					if ( NeuronArch[nid]->connections.size() > minconns )
					{
						//cerr << "\t-C " << nid << endl;
						unsigned int connid = randgen.get(0, NeuronArch[nid]->connections.size()-1);
						delete NeuronArch[nid]->connections[connid];
						NeuronArch[nid]->connections.erase(NeuronArch[nid]->connections.begin()+connid);
					}
				}

			}

	}
}

void Brain::setArch(string &content)
{
	string line = parseH.returnUntillStrip( "\n", content );
	while ( !line.empty() )
	{
		// neuron(ft=24|iwr=20|mtr=4|inputs(|s,78,6|s,186,-12|s,123,10|n,19,5|n,3,3|n,11,-19));

		if ( parseH.beginMatchesStrip( "neuron(", line ) )
		{
			ArchNeuron *n = new ArchNeuron;
			NeuronArch.push_back( n );
			unsigned int nid = (NeuronArch.size()-1);

			if ( parseH.beginMatchesStrip( "ft=", line ) )
			{
				string FT = parseH.returnUntillStrip( "|", line );
				//cerr << "FT: " << FT  << endl;
				if(EOF == sscanf(FT.c_str(), "%d", &NeuronArch[nid]->fireThresh)) cerr << "ERROR INSERTING CRITTER" << endl;
			}

			if ( parseH.beginMatchesStrip( "iwr=", line ) )
			{
				string IWR = parseH.returnUntillStrip( "|", line );
				//cerr << "IWR: " << IWR  << endl;
				if(EOF == sscanf(IWR.c_str(), "%d", &NeuronArch[nid]->iWeightRange)) cerr << "ERROR INSERTING CRITTER" << endl;
			}

			if ( parseH.beginMatchesStrip( "mtr=", line ) )
			{
				string MTR = parseH.returnUntillStrip( "|", line );
				//cerr << "MTR: " << MTR  << endl;
				if(EOF == sscanf(MTR.c_str(), "%d", &NeuronArch[nid]->MotorFunc)) cerr << "ERROR INSERTING CRITTER" << endl;
				NeuronArch[nid]->isMotor = true;
			}

			if ( parseH.beginMatchesStrip( "inputs(|", line ) )
			{
				string INPUTS = parseH.returnUntillStrip( ")", line );
				INPUTS.append("|");
				//cerr << "INPUTS: " << INPUTS  << endl;

				string inp = parseH.returnUntillStrip( "|", INPUTS );
				while ( !inp.empty() )
				{
					ArchConnection *c = new ArchConnection;
					NeuronArch[nid]->connections.push_back( c );
					unsigned int cid = (NeuronArch[nid]->connections.size()-1);


					string TYPE = parseH.returnUntillStrip( ",", inp );
					string ID = parseH.returnUntillStrip( ",", inp );
					string WEIGHT = inp;
	//				cerr << "TYPE: " << TYPE  << endl;
	//				cerr << "ID: " << ID << endl;
	//				cerr << "WEIGHT: " << WEIGHT << endl;
					if(EOF == sscanf(TYPE.c_str(), "%c", &NeuronArch[nid]->connections[cid]->type)) cerr << "ERROR INSERTING CRITTER" << endl;
					if(EOF == sscanf(ID.c_str(), "%d", &NeuronArch[nid]->connections[cid]->id)) cerr << "ERROR INSERTING CRITTER" << endl;
					if(EOF == sscanf(WEIGHT.c_str(), "%d", &NeuronArch[nid]->connections[cid]->weight)) cerr << "ERROR INSERTING CRITTER" << endl;

					inp = parseH.returnUntillStrip( "|", INPUTS );
				}
			}
		}

		line = parseH.returnUntillStrip( "\n", content );
	}
}

// FIXME rename to save critter
string Brain::getArch()
{
	stringstream buf;

	// neuronal arch & connections
	for ( unsigned int i = 0; i < NeuronArch.size(); i++ )
	{
		// neuron info
		buf << "neuron(";
		buf << "ft=" << NeuronArch[i]->fireThresh;
		buf << "|iwr=" << NeuronArch[i]->iWeightRange;
		if ( NeuronArch[i]->isMotor ) buf << "|mtr=" << NeuronArch[i]->MotorFunc;

		// inputs
		buf << "|inputs(";
		for ( unsigned int j = 0; j < NeuronArch[i]->connections.size(); j++ )
		{
			buf << "|" << NeuronArch[i]->connections[j]->type << "," << NeuronArch[i]->connections[j]->id << "," << NeuronArch[i]->connections[j]->weight;
		}
		buf << "));\n";
	}

	return buf.str();
}

Brain::~Brain()
{
	for ( unsigned int i=0; i < NeuronArch.size(); i++ )	delete NeuronArch[i];
	for ( unsigned int i=0; i < Inputs.size(); i++ )	delete Inputs[i];
	for ( unsigned int i=0; i < Outputs.size(); i++ )	delete Outputs[i];
	for ( unsigned int i=0; i < Neurons.size(); i++ )	delete Neurons[i];
}
