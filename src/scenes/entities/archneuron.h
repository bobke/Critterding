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

		unsigned int fireThresh;
		unsigned int iWeightRange;
		bool isMotor;
		unsigned int MotorFunc;
		vector<struct ArchConnection*> connections;

};

#endif
