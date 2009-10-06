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
	registerWidget( "helpinfo", new Helpinfo() );
	registerWidget( "textmessage", Textmessage::Instance() );

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
			hasPickedWidget = true;
			pickedwidget = focussedWidget;
		}
// 		focussedWidget->click();
	}
}

void Maincanvas::buttonRelease()
{
	hasPickedWidget = false;
	pickedwidget = 0;
}

void Maincanvas::draw()
{
	if ( active )
		drawChildren();
}

Maincanvas::~Maincanvas()
{
}
