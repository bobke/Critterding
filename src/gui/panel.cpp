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

void Panel::drawBackground()
{
/*	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glColor4f(0.05f, 0.05f, 0.05f, 0.9f);
	glBegin(GL_QUADS);
		glVertex2f(halfwidth-halfboxwidth, halfheight+halfboxheight);
		glVertex2f(halfwidth-halfboxwidth, halfheight-halfboxheight);
		glVertex2f(halfwidth+halfboxwidth, halfheight-halfboxheight);
		glVertex2f(halfwidth+halfboxwidth, halfheight+halfboxheight);
	glEnd();
	glDisable(GL_BLEND);*/
}

void Panel::drawBorders()
{
}

Panel::~Panel()
{
}
