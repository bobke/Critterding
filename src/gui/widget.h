#ifndef WIDGET_H
#define WIDGET_H

#include <vector>

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

		// width/height accessors
		unsigned int		height();
		unsigned int		width();
		
	protected:
		Settings*		settings;
		bool			active;
		Vector2i		position;

		void			drawChildren();

		// width and height
		unsigned int		v_height;
		unsigned int		v_width;
	private:
		
		vector<Widget*>		children;
		Widget*			parent;
};

#endif
