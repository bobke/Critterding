#include "corpse.h"

Corpse::Corpse()
{
	settings	= Settings::Instance();
	totalFrames	= 0;
	isCarried	= false;
}

void Corpse::resize()
{
	// spillover failsafe
	if ( energy > settings->corpse_maxenergy )
		energy = settings->corpse_maxenergy;

	size = (settings->corpse_size / settings->corpse_maxenergy) * energy;

//  	size = settings->corpse_size;

	halfsize	= (size / 2.0f);
	straal		= (size * 1.4142136f)/2.0f;

	// change position according to height
	position.y = halfsize;
}

Corpse::~Corpse()
{
}


