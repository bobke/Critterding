#include "maincanvas.h"

Maincanvas::Maincanvas()
{
	active = true;

	// mouse focus
	mouseFocus = false;
	focussedWidget = 0;

	// movable widget picking
	hasPickedWidget = false;
	pickedwidget = 0;

	// register subwidgets of maincanvas
	addWidgetPanel( "helpinfo", new Helpinfo() );
	addWidgetPanel( "textmessage", Textmessage::Instance() );
	addWidgetPanel( "statsgraph", new Statsgraph() );
	addWidgetPanel( "infobar", new Infobar() );
	addWidgetPanel( "infostats", new Infostats() );
	addWidgetPanel( "textverbosemessage", Textverbosemessage::Instance() );
	addWidgetPanel( "exitpanel", new Exitpanel() );

	// point the widget width/height pointers to the window's width/height
	v_widthP = settings->winWidth;
	v_heightP = settings->winHeight;

	// set parent pointer to 0
	parent = 0;
}

void Maincanvas::moveMouse(unsigned int x, unsigned int y)
{
	if ( hasPickedWidget )
	{
		pickedwidget->translate( (int)x-oldx, (int)y-oldy );
	}
	else
	{
		mouseFocus = false;
		if ( mouseOverChild( &focussedWidget, x, y ) )
			mouseFocus = true;
	}
	oldx = x;
	oldy = y;
}

void Maincanvas::buttonPress()
{
	if ( mouseFocus )
	{
		if ( focussedWidget->isMovable )
		{
			pickedwidget = focussedWidget;
			hasPickedWidget = true;
		}
		focussedWidget->click();
	}
}

void Maincanvas::buttonRelease()
{
	hasPickedWidget = false;
}

void Maincanvas::draw()
{
	if ( active )
		drawChildren();
}

void Maincanvas::swapChild(const string& child)
{
	children[child]->swap();

	if ( children[child]->isMovable )
	{
		if ( children[child] == pickedwidget )
			hasPickedWidget = false;
	}
}

Maincanvas::~Maincanvas()
{
}
