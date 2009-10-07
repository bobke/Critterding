#ifndef CONTAINER_H
#define CONTAINER_H

#include "widget.h"

using namespace std;

class Container : public Widget
{
	public:
		Container();
		~Container();
		void		draw();

		// children map, publically accessible
		map<string, Widget*>	children;
		bool			mouseOverChild( Widget** fWidget, int x, int y );

	protected:
		void		drawChildren();

		void		addWidgetPanel( const string& name, Widget* nwidget );
		void		addWidgetText( const string& name, unsigned int posx, unsigned int posy, const string& textstring );
		void		addWidgetButton( const string& name, unsigned int posx, unsigned int posy, const string& textstring );
	
	private:
		// children map iterator
		typedef map <string, Widget*>::const_iterator children_iterator;
		children_iterator	childit;

};

#endif
