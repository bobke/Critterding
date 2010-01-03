#ifndef HUD_H
#define HUD_H

#include <vector>
#include "panel.h"
#include "../entities/worldb.h"
#include "../../utils/critterselection.h"

using namespace std;

class Hud : public Panel
{
	public:
		Hud();
		~Hud();
		void		draw();
		WorldB*		world;
		
	private:
		void		drawBorders();
		Critterselection	*critterselection;
		vector<Widget*>		cbuttons;
		btScalar viewposition[16];
};

#endif
