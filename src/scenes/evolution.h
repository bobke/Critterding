#ifndef EVOLUTION_H
#define EVOLUTION_H

#include <SDL/SDL.h>
#include "../gl/glscene.h"
#include "../utils/timer.h"
#include "../utils/sleeper.h"
#include "../utils/fps.h"
#include "../utils/settings.h"
#include "../utils/infobar.h"
#include "../utils/infostats.h"
#include "../utils/helpinfo.h"
#include "../utils/textmessage.h"
#include "../utils/textverbosemessage.h"
#include "../utils/events.h"
// #include "entities/camera.h"
#include "entities/worldb.h"

#include <sstream>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
// #include <GL/glx.h>
#include <GL/gl.h>
// #include <GL/glu.h>
//#include <X11/extensions/xf86vmode.h>
// #include <X11/keysym.h>


using std::cerr;
using std::endl;


class Evolution : public GLScene {

	public:
		Evolution();
		~Evolution();

		bool pause;

		void draw();

		// glwindow passes events to the scene
		void handlekeyPressed(const KeySym& key);
		void handlekeyReleased(const KeySym& key);
		void handlemousebuttonPressed(int x, int y, const int&);
		void handlemousebuttonReleased(int x, int y, const int&);
		void handleMouseMotionRel(int x, int y);
		void handleMouseMotionAbs(int x, int y);

// 		Camera camera;
		WorldB world;

	private:
		Settings *settings;
		Events *events;
		Sleeper sleeper;
		Infobar infobar;
		Infostats infostats;
		Helpinfo helpinfo;

		int mouse_x;
		int mouse_y;
		bool mouselook;
		
		// events
// 		float		elapsed;
		void		handleEvents();

		const unsigned int*	camerasensitivity;
};

#endif
