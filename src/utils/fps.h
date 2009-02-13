#ifndef FPS_H
#define FPS_H

#include "timer.h"
#include <iostream>

using std::cerr;
using std::endl;

class Fps
{
	public:
		Fps();
		~Fps();

		void mark();

		float		currentfps;

	private:

		int		dispcounter;
		int		dispevery;
		float		dispsum;
};

#endif
