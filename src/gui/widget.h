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

		bool			active;
		// movable (pickable) object
		bool			isMovable;
		// types
		bool			isContainer;

		// width/height accessors
		unsigned int		height();
		unsigned int		width();
		
		// pointer to parent
		Widget*			parent;

		// is mouse over widget
		bool			mouseOver( int x, int y );

		// widget ops
		void			translate( int x, int y );

	protected:
		Settings*		settings;
		Textprinter*		textprinter;
		Vector2i		position;

		// width and height
		unsigned int		v_height;
		unsigned int		v_width;
		unsigned int*		v_heightP;
		unsigned int*		v_widthP;

	private:
		
// 		vector<Widget*>		children;
};

#endif
