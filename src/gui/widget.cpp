#include "widget.h"

Widget::Widget()
{
	settings = Settings::Instance();
	textprinter = Textprinter::Instance();

	v_widthP = &v_width;
	v_heightP = &v_height;
	
	isMovable = false;
	isContainer = false;
	active = false;
}

void Widget::draw()
{
}

bool Widget::mouseOver(int x, int y)
{
	if ( active && x > position.x && x < position.x+(int)*v_widthP && y > position.y && y < position.y+(int)*v_heightP )
		return true;
	return false;
}

void Widget::translate(int x, int y)
{
	position.x += x;
	position.y += y;
}

void Widget::updateAbsPosition()
{
	absPosition.x = position.x;
	absPosition.y = position.y;
	if ( parent )
	{
		absPosition.x += parent->absPosition.x;
		absPosition.y += parent->absPosition.y;
	}
}

void Widget::swap()
{
	active = !active;
}

unsigned int Widget::height()
{
	if ( active )
		return *v_heightP;
	return 0;
}

unsigned int Widget::width()
{
	if ( active )
		return *v_widthP;
	return 0;
}

Widget::~Widget()
{
}
