#include "widget.h"

Widget::Widget()
{
	settings = Settings::Instance();
	textprinter = Textprinter::Instance();

	v_widthP = &v_width;
	v_heightP = &v_height;
	
	isMovable = false;
	active = false;
}

void Widget::draw()
{
	if ( active )
		drawChildren();
}

void Widget::drawChildren()
{
	for( childit = children.begin(); childit != children.end(); childit++ )
		childit->second->draw();
}

void Widget::registerWidget( const string& name, Widget* nwidget )
{
	children[name] = nwidget;
	children[name]->parent = this;
}

bool Widget::mouseOver(int x, int y)
{
	if ( active && x > position.x && x < position.x+*v_widthP && y > position.y && y < position.y+*v_heightP )
		return true;
	return false;
}

bool Widget::mouseOverChild(Widget** fWidget, int x, int y)
{
	for( childit = children.begin(); childit != children.end(); childit++ )
		if ( childit->second->active && childit->second->mouseOver(x, y) )
		{
			*fWidget = childit->second;
			return true;
		}
	return false;
}

void Widget::translate(int x, int y)
{
	position.x += x;
	position.y += y;
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
