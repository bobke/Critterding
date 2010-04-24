#ifndef EVOLUTION_H
#define EVOLUTION_H

#include <SDL/SDL.h>
#include "../gl/glscene.h"
#include "../utils/fps.h"
#include "../utils/settings.h"
#include "../utils/events.h"
#include "entities/worldb.h"
#include "modes/race.h"
#include "modes/roundworld.h"

// #include <sstream>
// #include <stdio.h>
// #include <stdarg.h>
// #include <math.h>
// #include <GL/gl.h>

#include "gui/maincanvas.h"
#include "../utils/commands.h"
#include "../utils/execcmd.h"

using std::cerr;
using std::endl;

class Evolution : public GLScene {

	public:
		Evolution();
		~Evolution();

		void draw();

		// glwindow passes events to the scene
		void handlekeyPressed(const SDLKey& key);
		void handlekeyReleased(const SDLKey& key);
		void handlemousebuttonPressed(const int&);
		void handlemousebuttonReleased(const int&);
		void handleMouseMotionRel(int x, int y);
		void handleMouseMotionAbs(int x, int y);

		WorldB* world;
		Execcmd execcmd;

	private:
		Settings *settings;
		const unsigned int* drawscene;
		const unsigned int* benchmark;
		Commands *cmd;
		Events *events;

		Maincanvas canvas;
		
		long long	frameCounter;
};

#endif
