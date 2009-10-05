#include "widget.h"

Widget::Widget()
{
	settings = Settings::Instance();

	v_widthP = &v_width;
	v_heightP = &v_height;
	
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
