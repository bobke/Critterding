#ifndef GENOTYPES_H
#define GENOTYPES_H

#include "genotype.h"

#include <vector>
#include <iostream>
using std::cerr;
using std::endl;

class Genotypes
{
	public:
		static Genotypes* Instance();
		Genotype* newg();
		void add(Genotype* gt);
		Genotype* copy(Genotype* gt);
		void remove(Genotype* gt);
	protected:
		Genotypes();
		~Genotypes();
	private:
		static Genotypes* _instance;

		vector<Genotype*>	list;
};

#endif
