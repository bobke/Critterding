#ifdef _WIN32
	#include <unistd.h>
#endif
#include "sleeper.h"

Sleeper::Sleeper()
{
	t = Timer::Instance();

	active		= false;
	optimal		= 30;
	stepsize	= 500;
	sleeptime	= 10000;
	cps		= optimal;

	timeSinceLastRender = 1.0f;
}

void Sleeper::mark()
{
	if ( active )
	{
		if ( t->elapsed == 0 ) cps = 0;
		else cps = (1/t->elapsed);
	
		if ( cps > optimal ) sleeptime += stepsize;
		else if ( cps < optimal )
		{
			if ( sleeptime >= stepsize )	sleeptime -= stepsize;
			else 				sleeptime = 0;
		}
		if (sleeptime > 0 ) usleep(sleeptime);
	}
}

bool Sleeper::isRenderTime()
{
	if ( active )
		return true;

	timeSinceLastRender += t->elapsed;
	if ( timeSinceLastRender >= (1.0f/optimal) )
	{
		timeSinceLastRender = 0.0f;
		return true;
	}
		
//  	cerr << "returning false" << endl;
	return false;
}

void Sleeper::swap()
{
	active =! active;
}

Sleeper::~Sleeper()
{
}
