#include "maincanvas.h"

Maincanvas::Maincanvas()
{
	active = true;

	// mouse focus
	mouseFocus = false;
	focussedwidget = 0;

	// movable widget picking
	hasPickedwidget = false;
	pickedwidget = 0;

	// register subwidgets of maincanvas
	addWidgetPanel( "helpinfo", new Helpinfo() );
	addWidgetPanel( "textmessage", new Textmessage() );
	addWidgetPanel( "statsgraph", new Statsgraph() );
	addWidgetPanel( "infobar", new Infobar() );
	addWidgetPanel( "infostats", new Infostats() );
	addWidgetPanel( "textverbosemessage", Textverbosemessage::Instance() );
	addWidgetPanel( "exitpanel", new Exitpanel() );
	addWidgetPanel( "settingspanel", new Settingspanel() );
	addWidgetPanel( "settingsbrainpanel", new Settingsbrainpanel() );

	// set default z axises to panels
	unsigned int panelc = 0;
	for( childit = children.begin(); childit != children.end(); childit++ )
	{
		static_cast<Panel*>(childit->second)->zaxis = panelc;
		// update sorted drawing/clicking vector
		sortedindices.push_back(childit->first);
		panelc++;
	}

	// point the widget width/height pointers to the window's width/height
	v_widthP = settings->winWidth;
	v_heightP = settings->winHeight;

	// set parent pointer to 0
	parent = 0;
}

void Maincanvas::moveMouse(unsigned int x, unsigned int y)
{
	if ( hasPickedwidget && pickedwidget->isMovable )
	{
		pickedwidget->translate( (int)x-oldx, (int)y-oldy );
	}
	else
	{
		mouseFocus = false;
		if ( mouseOverChild( &focussedwidget, x, y ) )
			mouseFocus = true;
	}
	oldx = x;
	oldy = y;
}

void Maincanvas::buttonPress()
{
	if ( mouseFocus )
	{
		pickedwidget = focussedwidget;
		pickedwidget->click();
		hasPickedwidget = true;

		// raise panel?
		raisePanel(pickedwidget);
	}
}

void Maincanvas::raisePanel(Widget* w)
{
	Panel* rp = static_cast<Panel*>(w);
	if ( rp->zaxis > 0 )
	{
		// the other lower zaxis values get ++
		for( childit = children.begin(); childit != children.end(); childit++ )
		{
			Panel* p = static_cast<Panel*>(childit->second);
			if ( p->zaxis < rp->zaxis )
				p->zaxis++;
		}
		// this zaxis goes to 0
		rp->zaxis = 0;

		// resort sortedindices
		for ( int i = sortedindices.size(); i>0; i--  )
			for ( int j = 0; j < i-1; j++  )
				if ( static_cast<Panel*>(children[sortedindices[j]])->zaxis < static_cast<Panel*>(children[sortedindices[j+1]])->zaxis )
				{
					string	keepS		= sortedindices[j];
					sortedindices[j]	= sortedindices[j+1];
					sortedindices[j+1]	= keepS;
				}
	}
}

void Maincanvas::buttonRelease()
{
	if ( hasPickedwidget )
	{
		pickedwidget->release();
		hasPickedwidget = false;
	}
}

void Maincanvas::draw()
{
	if ( active )
		drawChildren();
}

void Maincanvas::drawChildren()
{
	for( unsigned int i=0; i < sortedindices.size(); i++ )
		children[sortedindices[i]]->draw();
}

bool Maincanvas::mouseOverChild(Widget** fWidget, int x, int y)
{
	for ( int i = sortedindices.size()-1; i >= 0; i--  )
 	{
		Widget* w = children[sortedindices[i]];
		if ( (w->isTouchable && w->active && w->mouseOver(x, y)) || !w->isTouchable )
		{
			// RECURSIVE INTO CONTAINERS
			if ( w->isContainer )
			{
				Container* c = static_cast<Container*>(w);
				if ( c->mouseOverChild( fWidget, x, y ) )
				{
					return true;
				}
				else if ( w->isTouchable )
				{
					*fWidget = w;
					return true;
				}
			}
			else if ( w->isTouchable )
			{
				*fWidget = w;
				return true;
			}
		}
	}
	return false;
}

void Maincanvas::swapChild(const string& child)
{
// 	cerr << "swapping child" << endl;
	children[child]->swap();
	if ( children[child]->active )
		raisePanel(children[child]);

	if ( children[child]->isMovable )
	{
		if ( children[child] == pickedwidget )
			hasPickedwidget = false;
	}
	moveMouse(oldx, oldy);
}

Maincanvas::~Maincanvas()
{
}
