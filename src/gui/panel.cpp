#include "panel.h"

Panel::Panel()
{
	isTouchable = true;
	isTransparant = true;
	zaxis = 0;
}

void Panel::draw()
{
	if (active)
	{
		drawBackground();
		drawBorders();
		drawChildren();
	}
}

void Panel::drawBackground()
{
	if (isTransparant)
	{
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}

	glColor4f(0.05f, 0.05f, 0.05f, 0.75f);
	glBegin(GL_QUADS);
		glVertex2f(absPosition.x,         absPosition.y+v_height);
		glVertex2f(absPosition.x,         absPosition.y);
		glVertex2f(absPosition.x+v_width, absPosition.y);
		glVertex2f(absPosition.x+v_width, absPosition.y+v_height);
	glEnd();

	if (isTransparant)
		glDisable(GL_BLEND);
}

void Panel::drawBorders()
{
	glColor3f(0.5f, 0.5f, 0.5f);
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
