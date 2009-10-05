#ifndef STATSGRAPH_H
#define STATSGRAPH_H

#include "textprinter.h"
#include "../utils/statsbuffer.h"

using namespace std;

class Statsgraph
{
	public:
		Statsgraph();
		~Statsgraph();

		unsigned int barheight;
		unsigned int height();
		
		void draw( unsigned int posY );
		void swap();

	private:
		Settings* settings;
		Statsbuffer* statsBuffer;
		bool active;

		unsigned int boxwidth;
		unsigned int boxheight;
};

#endif
