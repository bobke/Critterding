#ifndef SLEEPER_H
#define SLEEPER_H

#include "timer.h"
#include <iostream>

using std::cerr;
using std::endl;

class Sleeper
{
	public:
		Sleeper();
		~Sleeper();

		void mark();
		void swap();

	private:

		bool		active;
		unsigned int	optimal;
		unsigned int	stepsize;
		unsigned int	sleeptime;
		float		cps;

		int		dispcounter;
		int		dispevery;
		float		dispsum;

};

#endif
