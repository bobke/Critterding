#include "genotypes.h"

Genotypes* Genotypes::Instance () 
{
	static Genotypes t;
	return &t;
}

Genotypes::Genotypes()
{
}

Genotype* Genotypes::newg(const unsigned int& retinasize)
{
// cerr << " gentotype start" << endl;
	Genotype* gt = new Genotype();
	gt->bodyArch->buildArch();
	gt->registerBrainInputOutputs(retinasize);
	gt->brainzArch->buildArch();

	gt->count=1;
	gt->speciescolor = colorH.randomColorRGB().normalized();

	list.push_back(gt);
// 	cerr << " new genotype " << list.size() << endl;
	return gt;
}

Genotype* Genotypes::newg(string& passToBody, string& passToBrain, const unsigned int& retinasize)
{
// cerr << " gentotype start" << endl;
	Genotype* gt = new Genotype();
	gt->bodyArch->setArch(&passToBody);
	gt->registerBrainInputOutputs(retinasize);
	gt->brainzArch->setArch(&passToBrain);

	gt->count=1;
	gt->speciescolor = colorH.randomColorRGB().normalized();

	list.push_back(gt);
// 	cerr << " new genotype " << list.size() << endl;
// cerr << " gentotype end" << endl;
	return gt;
}

void Genotypes::add(Genotype* gt)
{
	gt->count++;
// 	cerr << " added genotype " << list.size() << endl;
}

Genotype* Genotypes::copy(Genotype* gt, bool brainmutant, unsigned int brruns, bool bodymutant, unsigned int boruns, const unsigned int& retinasize)
{
// cerr << " gentotype copy start" << endl;
	if ( bodymutant || brainmutant )
	{
		Genotype* newgt = new Genotype();

		newgt->bodyArch->copyFrom(gt->bodyArch);

		if ( bodymutant )
		{
			unsigned int runs = RandGen::Instance()->get(1, boruns);
			newgt->bodyArch->mutate( runs );
		}

		newgt->registerBrainInputOutputs(retinasize);
		newgt->brainzArch->copyFrom(gt->brainzArch);

		if ( bodymutant )
			newgt->brainzArch->removeObsoleteMotorsAndSensors();

		if ( brainmutant )
		{
			unsigned int runs = RandGen::Instance()->get(1, brruns);
			newgt->brainzArch->mutate( runs );
		}

		newgt->count=1;
		newgt->speciescolor = colorH.randomColorRGB().normalized();

		list.push_back(newgt);
// cerr << " gentotype copy end" << endl;
		return newgt;
	}
	else
	{
		add(gt);
// cerr << " gentotype copy end" << endl;
		return gt;
	}

	
// 	cerr << " copied genotype " << list.size() << endl;
}


void Genotypes::remove(Genotype* gt)
{
// 	cerr << gt->count << endl;
	if ( gt->count > 1 )
		gt->count--;
	else
	{
		for ( unsigned int i=0; i < list.size(); i++ )
			if ( list[i] == gt )
			{
				delete gt;
				list.erase(list.begin()+i);
// 				cerr << " removing genotype " << list.size() << endl;
				return;
			}
	}
}

Genotypes::~Genotypes()
{
	for (unsigned int i=0; i<list.size(); i++) delete list[i];
}
