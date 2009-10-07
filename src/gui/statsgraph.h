#ifndef STATSGRAPH_H
#define STATSGRAPH_H

#include "panel.h"
#include "../utils/statsbuffer.h"

using namespace std;

class Statsgraph : public Panel
{
	public:
		Statsgraph();
		~Statsgraph();

		void draw();
		void swap();

	private:
		Settings* settings;
		Statsbuffer* statsBuffer;
};

#endif
