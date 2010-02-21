#ifndef GENOTYPE_H
#define GENOTYPE_H

#include "bodyarch.h"
#include "../../brainz/brainzarch.h"
#include "../../utils/color.h"

using namespace std;

class Genotype
{
	public:
		Genotype();
		~Genotype();

		unsigned int adamdist;
		Color speciescolor;
		
		BodyArch* bodyArch;
		BrainzArch* brainzArch;
		
		unsigned int count;
		void registerBrainInputOutputs();
		
		string saveGenotype();
	private:
};

#endif
