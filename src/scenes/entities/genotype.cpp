#include "genotype.h"

Genotype::Genotype()
{
	bodyArch = new BodyArch();
	brainzArch = new BrainzArch();

	count = 0;
}

Genotype::~Genotype()
{
	delete bodyArch;
	delete brainzArch;
}


