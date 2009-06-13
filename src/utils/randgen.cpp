#include "randgen.h"

RandGen* RandGen::Instance () 
{
	static RandGen t;
	return &t; // _instance isn't needed in this case
}

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
		if (++count > 100)
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
