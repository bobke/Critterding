#include "sleeper.h"

Sleeper::Sleeper()
{
 	active		= false;
	optimal		= 3000;
	stepsize	= 250;
	sleeptime	= 10000;
	cps		= optimal;

	dispcounter	= 0;
	dispevery	= 100;
	dispsum		= 0.0f;

	// calc lasttiem for first time
	gettimeofday(&lasttime, &timer_tz);
}

void Sleeper::mark()
{
	if ( active )
	{

		// get now
		timeval now;
		gettimeofday(&now, &timer_tz);
	
		// calc diff between now and lasttime
		float elapsed = ( (float)((now.tv_sec - lasttime.tv_sec) * 1000000 + (now.tv_usec - lasttime.tv_usec)) / 1000000);
	
		if ( elapsed == 0 ) cps = 0;
		else cps = (1/elapsed);
	
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
	
		// lasttime becomes now
		lasttime = now;
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
