#ifndef CRITTERVIEW_H
#define CRITTERVIEW_H

#include "panel.h"
#include "../scenes//entities/worldb.h"
#include "../utils/critterselection.h"
#include "../math/vector2f.h"
#include "../scenes/entities/critterb.h"

using namespace std;

class Critterview : public Panel
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
		Critterview();
		~Critterview();

		void draw();
		WorldB*		world;
	private:
		Critterselection* critterselection;
		Widget* viewbutton;
		Widget* bviewbutton;
		btScalar viewposition[16];
		CritterB* currentCritter;

		vector<neuron> neurons;
		vector<sensor> sensors;
};

#endif
