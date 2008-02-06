#include "randgen.h"

RandGen::RandGen()
{
	gettimeofday(&now, &timer_tz);
	count = 0;
}

unsigned int RandGen::get(unsigned int minimum, unsigned int maximum)
{
	count += 7;
	if (count > 200)
	{
		srand(now.tv_usec + count);
		gettimeofday(&now, &timer_tz);
		count = 0;
	}

	return ((rand() % (maximum-minimum+1)) + minimum);
}


RandGen::~RandGen()
{
}


