#ifndef SLEEPER_H
#define SLEEPER_H

#include "../../utils/settings.h"
#include "timer.h"

class Sleeper
{
	public:
		Sleeper();
		~Sleeper();

		void mark();
		void swap();
		bool isRenderTime();

	private:
		Timer *t;
		bool		active;
		unsigned int	optimal;
		unsigned int	stepsize;
		unsigned int	sleeptime;
		float		cps;

		float timeSinceLastRender;
		Settings*		settings;
};

#endif
