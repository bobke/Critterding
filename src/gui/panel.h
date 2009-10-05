#ifndef PANEL_H
#define PANEL_H

#include <vector>

#include "widget.h"

using namespace std;

class Panel : public Widget
{
	public:
		Panel();
		~Panel();
		void		draw();
	protected:
		void		drawBackground();
		void		drawBorders();
	
	private:

};

#endif
