#include "food.h"

Food::Food()
{
	settings	= Settings::Instance();
	totalFrames	= 0;
	isCarried	= false;
}

void Food::resize()
{
	// spillover failsafe
	if ( energy > settings->food_maxenergy )
		energy = settings->food_maxenergy;

	size = settings->food_lifeenergyratio * energy;

	halfsize = size / 2.0f;

	// change position according to height
	position.y = halfsize;
}

Food::~Food()
{
}


