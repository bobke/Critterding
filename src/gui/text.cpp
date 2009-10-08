#include "text.h"

Text::Text()
{
	v_string = "";
}

void Text::draw()
{
// 	Textprinter::Instance()->print( parent->position.x+position.x, parent->position.y+position.y, v_string );
	updateAbsPosition();
	Textprinter::Instance()->print( absPosition, v_string );
}

Text::~Text()
{
}
