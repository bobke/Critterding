#ifndef HUD_H
#define HUD_H

#include <vector>
#include "panel.h"
#include "../scenes//entities/worldb.h"
#include "../utils/critterselection.h"

using namespace std;

class Hud : public Panel
{
	public:
		Hud();
		~Hud();
		void		draw();
		void		updateAbsPosition();
		WorldB*		world;
		
	private:
		void		drawBorders();
		void		updateAbsPositionReal();
		Critterselection	*critterselection;
		vector<Widget*>		cbuttons;
};

#endif
