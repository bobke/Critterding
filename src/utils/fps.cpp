#include "fps.h"

Fps::Fps()
{
	t = Timer::Instance();

	dispcounter	= 0;
	dispevery	= 25;
	dispsum		= 0.0f;
	currentfps	= 0.0f;
}

void Fps::mark()
{
	if ( t->elapsed > 0.0f )
	{
		dispsum += t->bullet_ms;

		if ( ++dispcounter == dispevery )
		{
			currentfps = dispsum/dispevery;
/*			cerr << "FPS: " << currentfps << endl;*/
			dispcounter = 0;
			dispsum = 0.0f;
		}
	}
}

Fps::~Fps()
{
}
