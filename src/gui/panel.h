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
		unsigned int	zaxis;
		bool		isAlwaysOnTop;

	protected:
		virtual void	drawBackground();
		virtual void	drawBorders();
	private:

};

#endif
