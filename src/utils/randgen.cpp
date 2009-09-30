#include "randgen.h"

RandGen* RandGen::Instance () 
{
	static RandGen t;
	return &t;
}

RandGen::RandGen()
{
	unsigned int n1 = Timer::Instance()->lasttime.tv_usec;
	usleep(10000);
	Timer::Instance()->mark();

	unsigned int n2 = Timer::Instance()->lasttime.tv_usec;
	usleep(10000);
	Timer::Instance()->mark();

	unsigned int n3 = Timer::Instance()->lasttime.tv_usec;

// 	cerr << (n1*n2)-n3 << endl;

	srand( (n1*n2)-n3 );
	count = 0;
}

unsigned int RandGen::get(unsigned int minimum, unsigned int maximum)
{
	if ( maximum > minimum )
	{
		if (++count > 1000)
		{
			unsigned int newseed = Timer::Instance()->lasttime.tv_usec;
			if ( newseed > 0 )
				srand( newseed + (rand() % (maximum-minimum+1)) + minimum );
			count = 0;
		}
	
		return ((rand() % (maximum-minimum+1)) + minimum);
	}
	else
	{
		return minimum;
	}
}
