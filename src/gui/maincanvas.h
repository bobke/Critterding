#ifndef MAINCANVAS_H
#define MAINCANVAS_H

#include "container.h"

#include "helpinfo.h"
#include "textmessage.h"
#include "statsgraph.h"
#include "infobar.h"
#include "infostats.h"
#include "textverbosemessage.h"

using namespace std;

class Maincanvas : public Container
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
