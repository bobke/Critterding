#ifndef PANEL_H
#define PANEL_H

#include "container.h"

using namespace std;

class Panel : public Container
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
