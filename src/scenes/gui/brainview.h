#ifndef BRAINVIEW_H
#define BRAINVIEW_H

#include "../../gui/settingspanel.h"
// #include "../entities/worldb.h"
#include "../../utils/critterselection.h"
#include "../../math/vector2f.h"
#include "../entities/critterb.h"

using namespace std;

class Brainview : public Settingspanel
{
	struct neuron
	{
		NeuronInterz* nPointer;
		Vector2f position;
		Vector2f newposition;
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
// 		WorldB*		world;
	private:
		Critterselection* critterselection;
		Widget* viewbutton;
		Widget* brainview;
// 		btScalar viewposition[16];
		CritterB* currentCritter;
		
		// drawing helpers
		int v_spacer;
		int v_space;
		float v_radius;
		float v_diam;
		int spacing;
		int column;
		int row;
		int rowlength;

		// shortcuts to settings
		const unsigned int*	attractor1;
		const unsigned int*	attractor2;
		const unsigned int*	attractor3;
		const unsigned int*	attractor4;
		const unsigned int*	brain_maxfiringthreshold;

		vector<neuron> neurons;
		vector<sensor> sensors;
};

#endif
