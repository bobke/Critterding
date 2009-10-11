#include "text.h"

Text::Text()
{
	v_string = "";
}

void Text::draw()
{
	textprinter->print( absPosition, v_string );
}

Text::~Text()
{
}
