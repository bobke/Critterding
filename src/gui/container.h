#ifndef CONTAINER_H
#define CONTAINER_H

#include "../utils/execcmd.h"
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

		Execcmd		cmd;
	protected:
		void		drawChildren();

		void		addWidgetPanel( const string& name, Widget* nwidget );
		void		addWidgetText( const string& name, unsigned int posx, unsigned int posy, const string& textstring );
		void		addWidgetButton( const string& name, unsigned int posx, unsigned int posy, const string& textstring, const cmdsettings& cmds );
	
	private:
		// children map iterator
		typedef map <string, Widget*>::const_iterator children_iterator;
		children_iterator	childit;

};

#endif
