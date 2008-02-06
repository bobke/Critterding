#ifndef NEURONINTER_H
#define NEURONINTER_H

#include <vector>
#include <iostream>

using namespace std;

struct input
{
	unsigned int *ref;
	int weight;
};

class NeuronInter
{
	public:
		NeuronInter();
		~NeuronInter();

		unsigned int		output;
		unsigned int		waitoutput;
		int			fireThresh;
		unsigned int		iWeightRange;
		bool			isMotor;
		unsigned int		MotorFunc;

		void			process();
		void			connec(unsigned int *output, int weight);

		vector<struct input*>	inputs;

	private:
		int			potential;
		unsigned int		nofiretime;
		unsigned int		nofirecount;


};

#endif
