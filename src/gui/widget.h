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

		Vector2i		position;

		virtual void		draw();
		virtual void		click();
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

		unsigned int*		v_heightP;
		unsigned int*		v_widthP;
	protected:
		Settings*		settings;
		Textprinter*		textprinter;

		// width and height
		unsigned int		v_height;
		unsigned int		v_width;

		void			updateAbsPosition();
		Vector2i		absPosition;

	private:
		
// 		vector<Widget*>		children;
};

#endif
