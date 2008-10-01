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
		void swap();

	private:

		bool		active;

		int		dispcounter;
		int		dispevery;
		float		dispsum;
};

#endif
