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
		unsigned int hsp;
		unsigned int vsp;

		unsigned int barheight;

// 		unsigned int halfboxwidth;
// 		unsigned int halfboxheight;

		bool active;
};

#endif
