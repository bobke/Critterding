#include "fps.h"

Fps::Fps()
{
	dispcounter	= 0;
	dispevery	= 25;
	dispsum		= 0.0f;
	currentfps	= 0.0f;
}

void Fps::mark()
{
	Timer *t = Timer::Instance();

	if ( t->elapsed > 0.0f )
	{
		dispsum += (1.0f/t->elapsed);

		if ( ++dispcounter == dispevery )
		{
			currentfps = dispsum/dispevery;
	//		cerr << "FPS: " << currentfps << endl;
			dispcounter = 0;
			dispsum = 0.0f;
		}
	}
}

Fps::~Fps()
{
}
