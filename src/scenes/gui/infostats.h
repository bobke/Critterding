#ifndef INFOSTATS_H
#define INFOSTATS_H

#include "../../gui/panel.h"

using namespace std;

class Infostats : public Panel
{
	public:
		Infostats();
		~Infostats();

		void draw();
	private:
		// horizontal/vertical spacers (padding)
		unsigned int hsp;
		unsigned int vsp;
};

#endif
