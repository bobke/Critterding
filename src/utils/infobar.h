#ifndef INFOBAR_H
#define INFOBAR_H

#include "fps.h"
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
		Fps fps;

		// horizontal/vertical spacers (padding)
		unsigned int hsp;
		unsigned int vsp;

		bool active;
};

#endif
