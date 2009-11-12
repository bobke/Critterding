#ifndef MAINCANVAS_H
#define MAINCANVAS_H

#include "container.h"

#include "helpinfo.h"
#include "textmessage.h"
#include "statsgraph.h"
#include "infobar.h"
#include "infostats.h"
#include "textverbosemessage.h"
#include "exitpanel.h"
#include "settingspanel.h"
#include "settingsbrainpanel.h"
#include "hud.h"

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
		
		void swapChild(const string& child);

	private:
		unsigned int oldx;
		unsigned int oldy;
		
		bool hasPickedwidget;
		Widget* pickedwidget;

		Widget* focussedwidget;

		vector<string> sortedindices;

		void	drawChildren();
		bool	mouseOverChild( Widget** fWidget, int x, int y );
		void	raisePanel(Widget* w);
};

#endif
