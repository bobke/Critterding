#ifndef MAINCANVAS_H
#define MAINCANVAS_H

#include "widget.h"
#include "helpinfo.h"

using namespace std;

class Maincanvas : public Widget
{
	public:
		Maincanvas();
		~Maincanvas();

		void draw();
		void moveMouse(unsigned int x, unsigned int y);

		bool mouseFocus;

		void buttonPress();
		void buttonRelease();
	private:
		unsigned int oldx;
		unsigned int oldy;
		
		bool hasPickedWidget;
		Widget* pickedwidget;

		Widget* focussedWidget;
};

#endif
