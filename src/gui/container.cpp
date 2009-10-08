#include "text.h"
#include "button.h"

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

void Container::addWidgetPanel( const string& name, Widget* nwidget )
{
	children[name] = nwidget;
	children[name]->parent = this;
}

void Container::addWidgetText( const string& name, unsigned int posx, unsigned int posy, const string& textstring )
{
	Text* t = new Text();
	t->parent = this;
	t->position.x = posx;
	t->position.y = posy;
	t->v_string = textstring;
	t->active = true;
	children[name] = t;
}

void Container::addWidgetButton( const string& name, unsigned int posx, unsigned int posy, const string& textstring )
{
	Button* t = new Button();
	t->parent = this;
	t->position.x = posx;
	t->position.y = posy;
	t->addWidgetText( "btext", 10, 20, textstring );
	t->active = true;
	
// 	t->v_string = textstring;
	children[name] = t;
}

void Container::addWidgetButton( const string& name, unsigned int posx, unsigned int posy, const string& textstring, const string& command )
{
	Button* t = new Button();
	t->parent = this;
	t->position.x = posx;
	t->position.y = posy;
	t->addWidgetText( "btext", 10, 20, textstring );
	t->command = command;
	t->active = true;
	
// 	t->v_string = textstring;
	children[name] = t;
}

bool Container::mouseOverChild(Widget** fWidget, int x, int y)
{
	for( childit = children.begin(); childit != children.end(); childit++ )
	{
		if ( childit->second->active && childit->second->mouseOver(x, y) )
		{
			// RECURSIVE INTO CONTAINERS
			if ( childit->second->isContainer )
			{
				Container* c = static_cast<Container*>(childit->second);
				if ( c->mouseOverChild( fWidget, x, y ) )
				{
					return true;
				}
				else
				{
					*fWidget = childit->second;
					return true;
				}
			}
			else
			{
				*fWidget = childit->second;
				return true;
			}
		}
	}
	return false;
}

Container::~Container()
{
	for( childit = children.begin(); childit != children.end(); childit++ )
		delete childit->second;
}
