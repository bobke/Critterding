#include "randgen.h"

RandGen* RandGen::Instance () 
{
	static RandGen t;
	return &t;
}

RandGen::RandGen()
{
	srand(Timer::Instance()->lasttime.tv_usec);
	count = 0;
}

unsigned int RandGen::get(unsigned int minimum, unsigned int maximum)
{
	if ( maximum > minimum )
	{
		if (++count > 1000)
		{
			srand(Timer::Instance()->lasttime.tv_usec);
			count = 0;
		}
	
		return ((rand() % (maximum-minimum+1)) + minimum);
	}
	else
	{
		return minimum;
	}
}
