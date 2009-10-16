#ifndef EVOLUTION_H
#define EVOLUTION_H

#include <SDL/SDL.h>
#include "../gl/glscene.h"
#include "../utils/timer.h"
#include "../utils/sleeper.h"
#include "../utils/fps.h"
#include "../utils/settings.h"
#include "../utils/events.h"
#include "entities/worldb.h"
#include "modes/race.h"
#include "modes/testworld1.h"

// #include <sstream>
// #include <stdio.h>
// #include <stdarg.h>
// #include <math.h>
// #include <GL/gl.h>

#include "../gui/maincanvas.h"
#include "../utils/commands.h"
#include "../utils/execcmd.h"

using std::cerr;
using std::endl;

class Evolution : public GLScene {

	public:
		Evolution();
		~Evolution();

		bool pause;

		void draw();

		// glwindow passes events to the scene
		void handlekeyPressed(const SDLKey& key);
		void handlekeyReleased(const SDLKey& key);
		void handlemousebuttonPressed(int x, int y, const int&);
		void handlemousebuttonReleased(int x, int y, const int&);
		void handleMouseMotionRel(int x, int y);
		void handleMouseMotionAbs(int x, int y);

		WorldB* world;
		Execcmd execcmd;

	private:
		Settings *settings;
		Commands *cmd;
		Events *events;
		Sleeper sleeper;

		Maincanvas canvas;

		int mouse_x;
		int mouse_y;
		int oldx;
		int oldy;

		bool mouselook;
		
		// events
		void		handleEvents();
};

#endif
