#ifndef INFOBAR_H
#define INFOBAR_H

#include "../utils/fps.h" // FIXME howso this is here?
#include "textprinter.h"

using namespace std;

class Infobar
{
	public:
		Infobar();
		~Infobar();

		unsigned int barheight;

		void draw();
		void swap();
		unsigned int height();

	private:
		Settings		*settings;
		Fps fps;

		// horizontal/vertical spacers (padding)
		unsigned int hsp;
		unsigned int vsp;

		bool active;
};

#endif
