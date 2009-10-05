#include "widget.h"

Widget::Widget()
{
	settings = Settings::Instance();

	active = false;
}

void Widget::draw()
{
	drawChildren();
}

void Widget::drawChildren()
{
	for ( unsigned int i=0; i < children.size(); i++ )
		children[i]->draw();
}

void Widget::swap()
{
	active = !active;
}

unsigned int Widget::height()
{
	if ( active )
		return v_height;
	return 0;
}

unsigned int Widget::width()
{
	if ( active )
		return v_width;
	return 0;
}

Widget::~Widget()
{
}
