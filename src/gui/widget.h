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
		virtual void		click(const int& button);
		virtual void		release(const int& button);
		void			swap();

		bool			active;
		// movable (pickable) object
		bool			isMovable;
		// touchable object (allows ignoring containers as clickable)
		bool			isTouchable;
		// types
		bool			isContainer;

		// drawing
		bool			isTransparant;
		
		// width/height accessors
		unsigned int		height();
		unsigned int		width();

		Vector2i		absPosition;

		// pointer to parent
		Widget*			parent;

		// is mouse over widget
		bool			mouseOver( int x, int y );

		// widget ops
		virtual void		translate( int x, int y );

		int*			v_heightP;
		int*			v_widthP;

		bool			hcenter;
		bool			vcenter;

		virtual void		updateAbsPosition();
	protected:
		Settings*		settings;
		Textprinter*		textprinter;

		// width and height
		int			v_height;
		int			v_width;

	private:
};

#endif
