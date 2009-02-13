#include "fps.h"

Fps::Fps()
{
 	active		= true;

	dispcounter	= 0;
	dispevery	= 10;
	dispsum		= 0.0f;
	currentfps	= 0.0f;
}

void Fps::mark()
{
	if ( active )
	{
		Timer *t = Timer::Instance();
	
		if ( t->elapsed != 0.0f )
			dispsum += (1/t->elapsed);

		if ( ++dispcounter == dispevery )
		{
			currentfps = dispsum/dispevery;
			//cerr << "FPS: " << currentfps << endl;
			dispcounter = 0;
			dispsum = 0.0f;
		}
	}
}

void Fps::swap()
{
	active = !active;
	dispcounter = 0;
	dispsum = 0.0f;
}

Fps::~Fps()
{
}
