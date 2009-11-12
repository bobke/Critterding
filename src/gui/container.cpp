#include "text.h"
#include "text_uintp.h"
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
	children[name]->translate(0, 0);
}

void Container::addWidgetText( const string& name, unsigned int posx, unsigned int posy, const string& textstring )
{
	Text* t = new Text();
	t->parent = this;
	t->translate(posx, posy);
	t->v_string = textstring;
	t->active = true;
	children[name] = t;
}

void Container::addWidgetText( const string& name, unsigned int posx, unsigned int posy, const unsigned int* uintp )
{
	Text_uintp* t = new Text_uintp();
	t->parent = this;
	t->translate(posx, posy);
	t->content = uintp;
	t->active = true;
	children[name] = t;
}

Widget* Container::addWidgetButton( const string& name, const Vector2i& pos, const Vector2i& dimensions, const string& textstring, const Vector2i& textpos, const cmdsettings& cmds, unsigned int responsetime, unsigned int minfresponsetime, unsigned int fresponseinterval )
{
	Button* t = new Button();
	t->parent = this;
	t->translate(pos.x, pos.y);
	t->v_width = dimensions.x;
	t->v_height = dimensions.y;
	t->addWidgetText( "btext", textpos.x, textpos.y, textstring );
// 	t->command = cmds;
	t->genEvent(name, cmds, responsetime, minfresponsetime, fresponseinterval);
	t->active = true;
	children[name] = t;
	
	return children[name];
}

bool Container::mouseOverChild(Widget** fWidget, int x, int y)
{
	for( childit = children.begin(); childit != children.end(); childit++ )
	{
		if ( (childit->second->isTouchable && childit->second->active && childit->second->mouseOver(x, y)) || !childit->second->isTouchable )
		{
			// RECURSIVE INTO CONTAINERS
			if ( childit->second->isContainer )
			{
				Container* c = static_cast<Container*>(childit->second);
				if ( c->mouseOverChild( fWidget, x, y ) )
				{
					return true;
				}
				else if ( childit->second->isTouchable )
				{
					*fWidget = childit->second;
					return true;
				}
			}
			else if ( childit->second->isTouchable )
			{
				*fWidget = childit->second;
				return true;
			}
		}
	}
	return false;
}

void Container::updateAbsPosition()
{
	absPosition.x = position.x;
	absPosition.y = position.y;
	if ( parent )
	{
		absPosition.x += parent->absPosition.x;
		absPosition.y += parent->absPosition.y;
	}

	// adjust children aswell
	for( childit = children.begin(); childit != children.end(); childit++ )
		childit->second->updateAbsPosition();
}

Container::~Container()
{
	for( childit = children.begin(); childit != children.end(); childit++ )
		delete childit->second;
}
