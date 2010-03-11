#ifndef RANDGEN_H
#define RANDGEN_H

#include <cstdlib>
#include "timer.h"
#include "settings.h"

using namespace std;

class RandGen
{
	public:
		static RandGen* Instance();

		unsigned int		get(unsigned int minimum, unsigned int maximum);
	protected:
		RandGen();
	private:
		static RandGen* _instance;

		unsigned int count;
		
/*		unsigned int rand1(unsigned int lim);
		unsigned int rand2(unsigned int lim);
		unsigned int rand3(unsigned int lim);
		unsigned int seed;
		unsigned int startseed;*/
};

#endif
