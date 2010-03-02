/*#ifdef _WIN32
	#include <unistd.h>
#endif*/
#include "sleeper.h"

Sleeper::Sleeper()
{
	settings = Settings::Instance();
	t = Timer::Instance();

	active		= false;
	optimal		= Settings::Instance()->getCVarPtr("fpslimit");
	stepsize	= 500;
	sleeptime	= 10000;
	cps		= *optimal;

	timeSinceLastRender = 1.0f;
}

void Sleeper::mark()
{
	if ( active )
	{
		if ( t->elapsed == 0 ) cps = 0;
		else cps = t->bullet_ms;
	
		if ( cps > *optimal ) sleeptime += stepsize;
		else if ( cps < *optimal )
		{
			if ( sleeptime >= stepsize )	sleeptime -= stepsize;
			else 				sleeptime = 0;
		}
// 		if (sleeptime > 0 ) usleep(sleeptime);
		if (sleeptime > 0 ) SDL_Delay(sleeptime*0.01f);
	}
}

bool Sleeper::isRenderTime()
{
	if ( active )
		return true;

	timeSinceLastRender += t->elapsed;
	if ( timeSinceLastRender >= (1.0f / *optimal ) )
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
