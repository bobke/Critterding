#include "sleeper.h"

Sleeper::Sleeper()
{
 	active		= false;
	optimal		= 30;
	stepsize	= 500;
	sleeptime	= 10000;
	cps		= optimal;

/*	dispcounter	= 0;
	dispevery	= 100;
	dispsum		= 0.0f;*/
}

void Sleeper::mark()
{
	if ( active )
	{
		Timer *t = Timer::Instance();
	
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

void Sleeper::swap()
{
	active =! active;
}

Sleeper::~Sleeper()
{
}
