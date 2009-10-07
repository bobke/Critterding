#include "panel.h"

Panel::Panel()
{
}

void Panel::draw()
{
	updateAbsPosition();
	drawBackground();
	drawBorders();
	drawChildren();
}

void Panel::drawBackground()
{
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glColor4f(0.05f, 0.05f, 0.05f, 0.75f);
	glBegin(GL_QUADS);
		glVertex2f(absPosition.x,         absPosition.y+v_height);
		glVertex2f(absPosition.x,         absPosition.y);
		glVertex2f(absPosition.x+v_width, absPosition.y);
		glVertex2f(absPosition.x+v_width, absPosition.y+v_height);
	glEnd();
	glDisable(GL_BLEND);
}

void Panel::drawBorders()
{
	glColor3f(0.7f, 0.7f, 0.7f);
	glBegin(GL_LINES);
		glVertex2f(absPosition.x,         absPosition.y+v_height);
		glVertex2f(absPosition.x,         absPosition.y);

		glVertex2f(absPosition.x,         absPosition.y);
		glVertex2f(absPosition.x+v_width, absPosition.y);

		glVertex2f(absPosition.x+v_width, absPosition.y);
		glVertex2f(absPosition.x+v_width, absPosition.y+v_height);

		glVertex2f(absPosition.x+v_width, absPosition.y+v_height);
		glVertex2f(absPosition.x,         absPosition.y+v_height);
	glEnd();
}

Panel::~Panel()
{
}
