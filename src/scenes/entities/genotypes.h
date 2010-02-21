#ifndef GENOTYPES_H
#define GENOTYPES_H

#include "genotype.h"
#include "../../utils/color.h"

#include <vector>
#include <iostream>
using std::cerr;
using std::endl;

class Genotypes
{
	public:
		static Genotypes* Instance();
		Genotype* newg(const unsigned int& retinasize);
		Genotype* newg(string& passToBody, string& passToBrain, const unsigned int& retinasize);
		void add(Genotype* gt);
		Genotype* copy(Genotype* gt, bool brainmutant, unsigned int brruns, bool bodymutant, unsigned int boruns, const unsigned int& retinasize);
		void remove(Genotype* gt);
		Color			colorH;
	protected:
		Genotypes();
		~Genotypes();
	private:
		static Genotypes* _instance;

		vector<Genotype*>	list;
};

#endif
