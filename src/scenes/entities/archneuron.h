#ifndef ARCHNEURON_H
#define ARCHNEURON_H

#include <vector>
using namespace std;

struct ArchConnection
{
	char type;
	unsigned int id;
	int weight;
};

class ArchNeuron
{
	public:
		ArchNeuron();
		~ArchNeuron();

		unsigned int			fireThresh;
		unsigned int			iWeightRange;
		unsigned int			nofiretime;

		bool				isMotor;
		unsigned int			MotorFunc;

		bool				isPlastic;
		unsigned int			plasticity;

		vector<struct ArchConnection*>	connections;

};

#endif
