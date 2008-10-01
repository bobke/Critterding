#include "fps.h"

Fps::Fps()
{
 	active		= false;

	dispcounter	= 0;
	dispevery	= 100;
	dispsum		= 0.0f;
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
			cerr << endl << "FPS: " << (dispsum/dispevery) << endl << endl;
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
