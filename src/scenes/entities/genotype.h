#ifndef GENOTYPE_H
#define GENOTYPE_H

#include "bodyarch.h"
#include "../../brainz/brainzarch.h"
using namespace std;

class Genotype
{
	public:
		Genotype();
		~Genotype();
		BodyArch* bodyArch;
		BrainzArch* brainzArch;
		
		unsigned int count;
	private:
};

#endif
