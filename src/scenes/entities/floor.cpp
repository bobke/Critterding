#include "floor.h"

Floor::Floor()
{
	gridsize	= 20;
	resize(gridsize);
}

void Floor::resize(int newsize)
{
	gridsize = newsize;
}

Floor::~Floor()
{
}


