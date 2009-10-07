#include "container.h"

Container::Container()
{
	isContainer = true;
}

void Container::draw()
{
	if ( active )
		drawChildren();
}

void Container::drawChildren()
{
	for( childit = children.begin(); childit != children.end(); childit++ )
		childit->second->draw();
}

void Container::registerWidget( const string& name, Widget* nwidget )
{
	children[name] = nwidget;
	children[name]->parent = this;
}

bool Container::mouseOverChild(Widget** fWidget, int x, int y)
{
	for( childit = children.begin(); childit != children.end(); childit++ )
		if ( childit->second->active && childit->second->mouseOver(x, y) )
		{
			// FIXME RECURSIVE SUBCONTAINERS
			*fWidget = childit->second;
			return true;
		}
	return false;
}

Container::~Container()
{
	for( childit = children.begin(); childit != children.end(); childit++ )
		delete childit->second;
}
