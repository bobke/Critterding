#ifndef EVOLUTION_H
#define EVOLUTION_H

#include "../gl/glscene.h"
#include "../utils/timer.h"
#include "../utils/fps.h"
#include "../utils/settings.h"
#include "entities/camera.h"
#include "entities/worldb.h"


using std::cerr;
using std::endl;


class Evolution : public GLScene {

	public:
		Evolution();
		~Evolution();

		bool pause;

		void draw();

		// glwindow passes events to the scene
		void handlekey(const KeySym& key);

		Camera camera;

		WorldB world;

	private:
		Settings *settings;
		Fps fps;

		bool drawCVNeurons;
};

#endif
