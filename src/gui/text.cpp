#include "text.h"

Text::Text()
{
	v_string = "";
}

void Text::draw()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	textprinter->print( absPosition, v_string );
}

Text::~Text()
{
}
