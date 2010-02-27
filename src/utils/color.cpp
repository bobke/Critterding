#include "color.h"

Color::Color()
{
	r = 0.0f;
	g = 0.0f;
	b = 0.0f;
	a = 0.0f;
}

Color Color::randomColorRGB()
{
	Color c;
	c.r = (float)RandGen::Instance()->get( 1,100 ) / 100.0f;
	c.g = (float)RandGen::Instance()->get( 1,100 ) / 100.0f;
	c.b = (float)RandGen::Instance()->get( 1,100 ) / 100.0f;
	c.a = 0.0f;
	
	return c;
}

void Color::normalize(Color* c)
{
	float highest = c->r;
	if ( c->g > highest )
		highest = c->g;
	if ( c->b > highest )
		highest = c->b;
	if ( c->a > highest )
		highest = c->a;

	c->r /= highest;
	c->g /= highest;
	c->b /= highest;
	c->a /= highest;
}

Color Color::getNormalized()
{
	float highest = r;
	if ( g > highest )
		highest = g;
	if ( b > highest )
		highest = b;
	if ( a > highest )
		highest = a;

	Color c;
	c.r = r/highest;
	c.g = g/highest;
	c.b = b/highest;
	c.a = a/highest;
	
	return c;
}

void Color::normalize()
{
	float highest = r;
	if ( g > highest )
		highest = g;
	if ( b > highest )
		highest = b;
	if ( a > highest )
		highest = a;

	r /= highest;
	g /= highest;
	b /= highest;
	a /= highest;
}

Color& Color::operator=(const Color& other)
{
	r = other.r;
	g = other.g;
	b = other.b;
	a = other.a;
	return (*this);
}

Color::~Color()
{
}


