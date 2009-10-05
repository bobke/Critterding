#include "panel.h"

Panel::Panel()
{
}

void Panel::draw()
{
	drawBackground();
	drawBorders();
	drawChildren();
}

void Panel::drawBackground()
{
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glColor4f(0.05f, 0.05f, 0.05f, 0.9f);
	glBegin(GL_QUADS);
		glVertex2f(position.x,         position.y+v_height);
		glVertex2f(position.x,         position.y);
		glVertex2f(position.x+v_width, position.y);
		glVertex2f(position.x+v_width, position.y+v_height);
	glEnd();
	glDisable(GL_BLEND);
}

void Panel::drawBorders()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex2f(position.x,         position.y+v_height);
		glVertex2f(position.x,         position.y);

		glVertex2f(position.x,         position.y);
		glVertex2f(position.x+v_width, position.y);

		glVertex2f(position.x+v_width, position.y);
		glVertex2f(position.x+v_width, position.y+v_height);

		glVertex2f(position.x+v_width, position.y+v_height);
		glVertex2f(position.x,         position.y+v_height);
	glEnd();
}

Panel::~Panel()
{
}
