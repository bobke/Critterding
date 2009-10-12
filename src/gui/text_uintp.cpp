#include "text_uintp.h"

Text_uintp::Text_uintp()
{
	content = 0;
}

void Text_uintp::draw()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	textprinter->print( absPosition, content );
}

Text_uintp::~Text_uintp()
{
}
