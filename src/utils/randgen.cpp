#include "randgen.h"

RandGen::RandGen()
{
	gettimeofday(&now, &timer_tz);
	srand(now.tv_usec);
	count = 0;
}

unsigned int RandGen::get(unsigned int minimum, unsigned int maximum)
{
	if ( maximum > minimum )
	{
		if (++count > 5000)
		{
			gettimeofday(&now, &timer_tz);
			srand(now.tv_usec);
			count = 0;
		}
	
		return ((rand() % (maximum-minimum+1)) + minimum);
	}
	else
	{
		return minimum;
	}
}


RandGen::~RandGen()
{
}


