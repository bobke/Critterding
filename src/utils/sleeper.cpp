#include "sleeper.h"

Sleeper::Sleeper()
{
 	active		= false;
	optimal		= 10000;
	stepsize	= 250;
	sleeptime	= 10000;
	cps		= optimal;

	dispcounter	= 0;
	dispevery	= 100;
	dispsum		= 0.0f;
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

		dispsum += cps;
		dispcounter++;
		if ( dispcounter == dispevery )
		{
			cerr << endl << "FPS: " << (dispsum/dispevery) << endl << endl;
			dispcounter = 0;
			dispsum = 0.0f;
		}
	}
}

void Sleeper::swap()
{
	if ( active )	active = false;
	else
	{
		active = true;
		dispcounter = 0;
		dispsum = 0.0f;
	}
}

Sleeper::~Sleeper()
{
}
