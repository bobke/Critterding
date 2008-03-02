#ifndef NEURONINTER_H
#define NEURONINTER_H

#include <vector>
#include <iostream>

using namespace std;

struct input
{
	unsigned int *ref;
	float weight;
};

class NeuronInter
{
	public:
		NeuronInter();
		~NeuronInter();

		unsigned int		output;
		unsigned int		waitoutput;
		unsigned int		maxconns;

		int			fireThresh;
		unsigned int		iWeightRange;
		unsigned int		nofiretime;

		bool			isMotor;
		unsigned int		MotorFunc;

		bool			isPlastic;
		unsigned int		plasticity;

		void			process();
		void			connec(unsigned int *output, int weight);

		vector<struct input*>	inputs;

	private:
		float			potential;
		unsigned int		nofirecount;


};

#endif
