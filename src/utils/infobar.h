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

		unsigned int critters;
		unsigned int food;
		unsigned int corpses;
		unsigned int bullets;

		void draw();
		void swap();

	private:
		Fps fps;

		bool active;
};

#endif
