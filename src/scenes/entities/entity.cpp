#include "entity.h"

Entity::Entity()
{
	type = CRITTER;
	color.r = 0.0f;
	color.g = 0.0f;
	color.b = 0.0f;
	color.a = 0.0f;
}

void Entity::draw()
{
}

void Entity::drawDimmed(float dim)
{
}

Entity::~Entity()
{
}


