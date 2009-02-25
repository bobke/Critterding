#ifndef INFOSTATS_H
#define INFOSTATS_H

#include "textprinter.h"

using namespace std;

class Infostats
{
	public:
		Infostats();
		~Infostats();

		void draw( unsigned int posY );
		void swap();
		unsigned int height();

	private:
		// horizontal/vertical spacers (padding)
		float hsp;
		float vsp;

		unsigned int barheight;

		float halfboxwidth;
		float halfboxheight;

		bool active;
};

#endif
