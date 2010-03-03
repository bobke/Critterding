#ifndef INFOBAR_H
#define INFOBAR_H

#include "../../utils/fps.h"
#include "../../utils/statsbuffer.h"
#include "../../gui/panel.h"

using namespace std;

class Infobar : public Panel
{
	public:
		Infobar();
		~Infobar();

		void draw();

	private:
		Fps fps;
		Statsbuffer*		statsBuffer;

		// horizontal/vertical spacers (padding)
		unsigned int hsp;
		unsigned int vsp;
		const unsigned int*	energy;
};

#endif
