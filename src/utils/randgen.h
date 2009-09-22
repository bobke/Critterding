#ifndef RANDGEN_H
#define RANDGEN_H

#ifdef _WIN32
	#include <time.h>
	#include <windows.h>
#endif

#include <cstdlib>
#include "timer.h"

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

		unsigned int		count;
};

#endif
