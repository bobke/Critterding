#ifdef _WIN32
	#include <unistd.h>
#endif
#include "randgen.h"

// good rng seeds for benchmark:
// 1063523561

RandGen* RandGen::Instance () 
{
	static RandGen t;
	return &t;
}

RandGen::RandGen()
{
// 	unsigned int n1 = Timer::Instance()->lasttime.tv_usec;
// 	usleep(10000);
// 	Timer::Instance()->mark();
// 
// 	unsigned int n2 = Timer::Instance()->lasttime.tv_usec;
// 	usleep(10000);
// 	Timer::Instance()->mark();
// 
// 	unsigned int startseed = (n1*n2)-Timer::Instance()->lasttime.tv_usec;
// 
// 	cerr << "start seed: " << startseed << endl;

	unsigned int startseed;
	// random seed
	if ( Settings::Instance()->getCVar("startseed") == 0 )
	{
		Timer::Instance()->mark();
		unsigned int n1 = Timer::Instance()->sdl_now;
		srand( n1 );
		unsigned int r1 = get( 2000, 20000 );
		for ( unsigned int i=0; i<r1; i++ ) srand( i );
	// 	cerr << "n1: " << n1 << endl;
	// 	cerr << "r1: " << r1 << endl;

		Timer::Instance()->mark();
		unsigned int n2 = Timer::Instance()->sdl_now;
		srand( n2 );
		unsigned int r2 = get( 2000, 20000 );
		for ( unsigned int i=0; i<r2; i++ )  srand( i );
	// 	cerr << "n2: " << n2 << endl;
	// 	cerr << "r2: " << r2 << endl;

		Timer::Instance()->mark();
		unsigned int n3 = Timer::Instance()->sdl_now;
		srand( n3 );
		unsigned int r3 = get( 2000, 20000 );
		for ( unsigned int i=0; i<r3; i++ )  srand( i );
	// 	cerr << "n3: " << n3 << endl;
	// 	cerr << "r3: " << r3 << endl;

		Timer::Instance()->mark();
		startseed = (n1*n2*n3*Timer::Instance()->sdl_now)+r1+r2+r3+Timer::Instance()->sdl_now;
	}
	else
	{
		// custom seed
		startseed = Settings::Instance()->getCVar("startseed"); // 420041141;
	}

	
	cerr << "start seed: " << startseed << endl;
	srand( startseed );
	count = 0;
}

unsigned int RandGen::get(unsigned int minimum, unsigned int maximum)
{
	if ( maximum > minimum )
	{
	  // commented out for benchmark, no reseeding
/*		if (++count > 1000)
		{
			unsigned int newseed = Timer::Instance()->sdl_lasttime;
			if ( newseed > 0 )
				srand( newseed + (rand() % (maximum-minimum+1)) + minimum );
			count = 0;
		}*/
	
		return ((rand() % (maximum-minimum+1)) + minimum);
	}
	else
	{
		return minimum;
	}
}
