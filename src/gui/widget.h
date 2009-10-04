#ifndef WIDGET_H
#define WIDGET_H

#include <vector>

#include "../utils/textprinter.h"

using namespace std;

class Widget
{
	public:
		Widget();
		~Widget();

		void draw();
		void swap();
		unsigned int height();
		unsigned int width();
	private:
		Settings*		settings;
		// horizontal/vertical spacers (padding)
		unsigned int v_height;
		unsigned int v_width;
		bool active;
};

#endif
