#include "maincanvas.h"

Maincanvas::Maincanvas()
{
	active = true;

	registerWidget( "helpinfo", new Helpinfo() );


	v_widthP = settings->winWidth;
	v_heightP = settings->winHeight;
	
	parent = 0;
}

void Maincanvas::draw()
{
	if ( active )
	{
		drawChildren();
	}
}

Maincanvas::~Maincanvas()
{
}
