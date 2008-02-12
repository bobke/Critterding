#ifndef BRAIN_H
#define BRAIN_H

#include "neuronsensor.h"
#include "neuroninter.h"
#include "archneuron.h"

class Brain
{
	public:
		Brain();
		~Brain();

	private:
		vector<ArchNeuron*>	NeuronArch;
		vector<NeuronSensor*>	SensorNeurons;
		vector<NeuronInter*>	Neurons;

		unsigned int		percentSensoryConns;
		unsigned int		percentMotor;

		unsigned int		addRandomArchConnection(unsigned int parentneuron);
		unsigned int		addRandomArchNeuron();
		void			setupArchitecture();
		void			doNeuronConnCount();

		void			setArch(string &content);
		string			getArch();

		void			process();

};

#endif
