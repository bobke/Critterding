#include "text_uintp.h"

Text_uintp::Text_uintp()
{
	content = 0;
}

void Text_uintp::draw()
{
	textprinter->print( absPosition, content );
}

Text_uintp::~Text_uintp()
{
}
