#ifndef RANDGEN_H
#define RANDGEN_H

#include <cstdlib>
#include <sys/time.h>	// for the seed

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

		struct timezone		timer_tz;
		struct timeval		now;

		unsigned int		count;
};

#endif
