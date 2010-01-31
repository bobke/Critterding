#ifndef CRITTERVIEW_H
#define CRITTERVIEW_H

#include "../entities/worldb.h"
#include "../../gui/panel.h"
#include "../../utils/critterselection.h"
#include "../../math/vector2f.h"
#include "../entities/critterb.h"

using namespace std;

class Critterview : public Panel
{
	public:
		Critterview();
		~Critterview();

		void draw();
		WorldB*		world;
	private:
		Critterselection* critterselection;
		Widget* viewbutton;
		btScalar viewposition[16];
		CritterB* currentCritter;
		
		// drawing helpers
		int v_spacer;
		int v_space;
// 		int v_radius;
// 		int v_diam;
// 		int spacing;
// 		int column;
// 		int row;
// 		int rowlength;
};

#endif
