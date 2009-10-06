#include "maincanvas.h"

Maincanvas::Maincanvas()
{
	active = true;

	mouseFocus = false;
	focussedWidget = 0;

	hasPickedWidget = false;
	pickedwidget = 0;

	
	registerWidget( "helpinfo", new Helpinfo() );


	v_widthP = settings->winWidth;
	v_heightP = settings->winHeight;
	
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
