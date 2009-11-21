#ifndef CRITTERVIEW_H
#define CRITTERVIEW_H

#include "panel.h"
#include "../scenes//entities/worldb.h"
#include "../utils/critterselection.h"
#include "../scenes/entities/critterb.h"

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
};

#endif
