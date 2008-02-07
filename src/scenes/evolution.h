#ifndef EVOLUTION_H
#define EVOLUTION_H

#include "../gl/glscene.h"
#include "entities/camera.h"
#include "entities/sleeper.h"
#include "entities/world.h"


using std::cerr;
using std::endl;


class Evolution : public GLScene {

	public:
		Evolution();
		~Evolution();

		void draw();

		// glwindow passes events to the scene
		void handlekey(const KeySym& key);

		Camera camera;

	private:
		Sleeper sleeper;

		World world;

		bool drawCVNeurons;
};

#endif
