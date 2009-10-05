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
	private:
};

#endif
