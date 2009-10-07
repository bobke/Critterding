#ifndef INFOBAR_H
#define INFOBAR_H

#include "../utils/fps.h" // FIXME howso this is here?
#include "panel.h"

using namespace std;

class Infobar : public Panel
{
	public:
		Infobar();
		~Infobar();

		void draw();

	private:
		Fps fps;

		// horizontal/vertical spacers (padding)
		unsigned int hsp;
		unsigned int vsp;
};

#endif
