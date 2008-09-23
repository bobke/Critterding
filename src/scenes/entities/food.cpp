#include "food.h"

Food::Food()
{
	maxsize		= 0.0f;
 	maxenergy	= 0.0f;

	size		= maxsize;
 	energy		= maxenergy;

	totalFrames	= 0;

	isCarried	= false;
}

void Food::resize()
{
	// spillover failsafe
	if ( energy > maxenergy ) energy = maxenergy;

	size = (maxsize / maxenergy) * energy;

	halfsize = size / 2.0f;

	// change position according to height
	position.y = halfsize;
}

Food::~Food()
{
}


