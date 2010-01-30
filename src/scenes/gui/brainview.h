#ifndef BRAINVIEW_H
#define BRAINVIEW_H

#include "panel.h"
#include "../entities/worldb.h"
#include "../../utils/critterselection.h"
#include "../../math/vector2f.h"
#include "../entities/critterb.h"

using namespace std;

class Brainview : public Panel
{
	struct neuron
	{
		NeuronInterz* nPointer;
		Vector2f position;
	};
	struct sensor
	{
		sensorNeuron* sPointer;
		Vector2f position;
	};

	public:
		Brainview();
		~Brainview();

		void draw();
		WorldB*		world;
	private:
		Critterselection* critterselection;
		Widget* viewbutton;
		Widget* brainview;
		btScalar viewposition[16];
		CritterB* currentCritter;
		
		// drawing helpers
		int v_spacer;
		int v_space;
		int v_radius;
		int v_diam;
		int spacing;
		int column;
		int row;
		int rowlength;


		vector<neuron> neurons;
		vector<sensor> sensors;
};

#endif
