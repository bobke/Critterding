#include "wall.h"

Wall::Wall()
{
	size		= 0.1f;
 	energy		= 1000.0f;
	resize(size);

	disabled	= false;
}
void Wall::resize(float newsize)
{
	size = newsize;
	halfsize = (newsize / 2.0f);

	// change position according to height
	position.y = halfsize;
}

void Wall::toggle()
{
	disabled = !disabled;
}

Wall::~Wall()
{
}


