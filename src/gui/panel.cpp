#include "panel.h"

Panel::Panel()
{
	cerr << "hey" << endl;
}

void Panel::draw()
{
	drawBackground();
	drawBorders();
	drawChildren();
}

Panel::~Panel()
{
}
