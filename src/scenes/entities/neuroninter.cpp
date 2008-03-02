#include "neuroninter.h"

NeuronInter::NeuronInter()
{

	maxconns	= 150;

	// input weight range, 5 = -5 <-> +5	-> 10 in total because 0 will be excluded
	iWeightRange	= 10;

	// processing
	fireThresh	= 30;
	potential	= 0;

	// forbidden firing time
	nofiretime	= 2;
	nofirecount	= 0;

	// output
	output		= 0;
	waitoutput	= 0;

	// SPECIALO optional reference that makes this a MOTOR neuron, but it depends on not being defined
	isMotor		= false;
	MotorFunc	= 0;

	// SPECIALO optional reference that makes this a PLASTIC neuron, but it depends on not being defined
	isPlastic	= false;
	plasticity	= 0;


}

void NeuronInter::process()
{
	// make every connection do it's influence on the neuron's total potential
	unsigned int isize = inputs.size();
	for ( unsigned int i=0; i < isize; i++ )
	{
		if ( *inputs[i]->ref > 0 )
			potential += inputs[i]->weight;
	}

	// do we spike/fire
	if ( potential >= fireThresh )
	{
		// we cannot fire "nofiretime" x after each other, so exception if output = 1
		if ( nofirecount == 0 )
		{
			// reset neural potential
			potential = 0;

			// fire the neuron
			waitoutput = 1;
			nofirecount = nofiretime;

			// SYNAPTIC PLASTICITY
			if ( isPlastic )
			{

				float proAm = ((float)iWeightRange/plasticity);
				float connAm = proAm / 100.0f;

				// loop all connections
				unsigned int isize = inputs.size();
				for ( unsigned int i=0; i < isize; i++ )
				{
					// this input fired
					if ( *inputs[i]->ref > 0 )
					{
						// this input was excitatory
						if ( inputs[i]->weight > 0.0f )
						{
							// increase weight if possible, else SPLIT THE INPUT
							inputs[i]->weight += proAm;
							if ( inputs[i]->weight > (float)iWeightRange )
							{

								if ( inputs[i]->weight > 1000.0f )
								{
									cerr << inputs[i]->weight << " yez " << (float)iWeightRange << endl;
									sleep (5);
								}

								if ( i > 160 )
								{
									cerr << i << " yez " << inputs.size() << endl;
									sleep (5);
								}

								if ( inputs.size() < maxconns )
								{
									//cerr << "splitting input " << i << endl;
									inputs[i]->weight = inputs[i]->weight/2.0f;
	
									input *in = new input;
									in->ref = inputs[i]->ref;
									in->weight = inputs[i]->weight;
									inputs.push_back( in );
								}
								else
								{
									inputs[i]->weight = (float)iWeightRange;
								}
							}
						}
					}
					// this input did not fire
					else
					{
						// this input was excitatory
						if ( inputs[i]->weight > 0.0f )
						{
							// decrease weight if possible, else REMOVE INPUT
							inputs[i]->weight -= connAm;
							if ( inputs[i]->weight < 0.0f )
							{
								cerr << "removing input " << i << endl;
								delete inputs[i];
								inputs.erase(inputs.begin()+i);
								i--;
								isize--;
							}
						}
					}

				}
			}

		}
		else
		{
			nofirecount--;
			waitoutput = 0;
		}
	}
	// don't fire the neuron
	else
	{
		waitoutput = 0;
		// reset potential if < 0
		if ( potential < 0 ) potential = 0;
	}

}

void NeuronInter::connec(unsigned int *output, int weight)
{
	if ( weight <= (int)iWeightRange && weight >= (int)(iWeightRange*-1) && weight != 0 )
	{
		input *i = new input;
		i->ref = output;
		i->weight = weight;
		inputs.push_back( i );

//		cerr << "I: " << inputs.size()-1 << "=" << *inputs[inputs.size()-1]->ref << "(" << inputs[inputs.size()-1]->ref << ")";
//		cerr << *inputs[0].ref << endl;
	}
	else
	{
		cerr << "illegal weight: " << weight << "while maximum: (-)" << iWeightRange << endl;
		exit(0);
	}
}

NeuronInter::~NeuronInter()
{
	for ( unsigned int i=0; i < inputs.size(); i++ ) delete inputs[i];
}


