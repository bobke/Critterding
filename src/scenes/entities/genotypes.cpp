#include "genotypes.h"

Genotypes* Genotypes::Instance () 
{
	static Genotypes t;
	return &t;
}

Genotypes::Genotypes()
{
}

Genotype* Genotypes::newg()
{
	Genotype* gt = new Genotype();

	gt->count=1;
	
	list.push_back(gt);
// 	cerr << " new genotype " << list.size() << endl;
	return gt;
}

void Genotypes::add(Genotype* gt)
{
	gt->count++;
// 	cerr << " added genotype " << list.size() << endl;
}

Genotype* Genotypes::copy(Genotype* gt)
{
	Genotype* newgt = newg();
	newgt->bodyArch->copyFrom(gt->bodyArch);
	newgt->brainzArch->copyFrom(gt->brainzArch);
// 	cerr << " copied genotype " << list.size() << endl;
	return newgt;
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
