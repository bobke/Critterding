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
		void	draw();

		// children map, publically accessible
		map<string, Widget*>	children;
		bool	mouseOverChild( Widget** fWidget, int x, int y );

		Execcmd		cmd;
	protected:
		void	drawChildren();

		void	addWidgetPanel( const string& name, Widget* nwidget );
		void	addWidgetText( const string& name, unsigned int posx, unsigned int posy, const string& textstring );
		void	addWidgetText( const string& name, unsigned int posx, unsigned int posy, const unsigned int* uintp );
		void	addWidgetButton( const string& name, const Vector2i& pos, const Vector2i& dimensions, const string& textstring, const Vector2i& textpos, const cmdsettings& cmds, unsigned int responsetime, unsigned int minfresponsetime, unsigned int fresponseinterval );
		
		void	updateAbsPosition();
	
		// children map iterator
		typedef map <string, Widget*>::const_iterator children_iterator;
		children_iterator	childit;

	private:

};

#endif
