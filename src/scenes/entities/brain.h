#ifndef BRAIN_H
#define BRAIN_H

#include <sstream>

#include "neuronsensor.h"
#include "neuroninter.h"
#include "archneuron.h"
#include "../../utils/randgen.h"
#include "../../utils/parser.h"

class Brain
{
	public:
		Brain();
		~Brain();

		vector<NeuronSensor*>	Inputs;
		vector<NeuronSensor*>	Outputs;

		unsigned int		absmaxneurons;
		unsigned int		absmaxconns;

		unsigned int		totalneurons;
		unsigned int		totalconnections;

		unsigned int		neuronsfired;

		void			process();
		void			setupInputs(unsigned int number);
		void			setupOutputs(unsigned int number);
		void			randomArchitecture();
		void			setupArchitecture();
		void			mutate();

		void			setArch(string &content);
		string			getArch();

	private:
		Parser			parseH;
		RandGen			randgen;

		vector<ArchNeuron*>	NeuronArch;
		vector<NeuronInter*>	Neurons;

		unsigned int		totalInputs;
		unsigned int		totalOutputs;

		unsigned int		percentSensoryConns;
		unsigned int		percentMotor;

		unsigned int		mutatepercent;

		unsigned int		newNmaxconns;

		unsigned int		minneurons;

		unsigned int		minconns;

		unsigned int		addRandomArchConnection(unsigned int parentneuron);
		unsigned int		addRandomArchNeuron();


};

#endif
