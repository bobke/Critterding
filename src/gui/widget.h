#ifndef WIDGET_H
#define WIDGET_H

#include <vector>
#include <map>

#include "textprinter.h"
#include "../math/vector2i.h"

using namespace std;

class Widget
{
	public:
		Widget();
		~Widget();

		virtual void		draw();
		void			swap();

		// movable (pickable) object
		bool			isMovable;

		// width/height accessors
		unsigned int		height();
		unsigned int		width();
		
		// children map, publically accessible
		map<string, Widget*>	children;
		// pointer to parent
		Widget*			parent;

		// is mouse over widget
		bool			mouseOver( int x, int y );
		bool			mouseOverChild( Widget** fWidget, int x, int y );

		// widget ops
		void			translate( int x, int y );


	protected:
		Settings*		settings;
		Textprinter*		textprinter;
		bool			active;
		Vector2i		position;

		void			registerWidget( const string& name, Widget* nwidget );
		void			drawChildren();

		// width and height
		unsigned int		v_height;
		unsigned int		v_width;
		unsigned int*		v_heightP;
		unsigned int*		v_widthP;

		// children map iterator
		typedef map <string, Widget*>::const_iterator children_iterator;
		children_iterator	childit;

	private:
		
// 		vector<Widget*>		children;
};

#endif
