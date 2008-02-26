#include "neuroninter.h"

NeuronInter::NeuronInter()
{
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

	// SPECIALO optional reference that makes this a motor neuron, but it depends on not being defined
	isMotor		= false;
	MotorFunc	= 0;


}

void NeuronInter::process()
{
	// make every connection do it's influence on the neuron's total potential
	unsigned int isize = inputs.size();
	for ( unsigned int i=0; i < isize; i++ )
	{
		if ( *inputs[i]->ref > 0 )
//		{
			potential += inputs[i]->weight;

//			// neuron plasticity test
// 			if ( inputs[i]->weight < 0 && inputs[i]->weight > (-1*(int)iWeightRange) ) inputs[i]->weight--;
// 			else if ( inputs[i]->weight > 0 && inputs[i]->weight < (int)iWeightRange ) inputs[i]->weight++;
// 		}
// 		else
// 		{
// 			// neuron plasticity test
// 			if ( inputs[i]->weight < 0 && inputs[i]->weight > (-1*(int)iWeightRange) ) inputs[i]->weight++;
// 			else if ( inputs[i]->weight > 0 && inputs[i]->weight < (int)iWeightRange ) inputs[i]->weight--;
// 		}

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


