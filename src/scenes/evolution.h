#ifndef EVOLUTION_H
#define EVOLUTION_H

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
#include "entities/camera.h"
#include "entities/worldb.h"

#include <sstream>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <GL/glx.h>
#include <GL/gl.h>
// #include <GL/glu.h>
//#include <X11/extensions/xf86vmode.h>
#include <X11/keysym.h>


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
		void resetCamera();

		Camera camera;

		WorldB world;

	private:
		Settings *settings;
		Sleeper sleeper;
		Infobar infobar;
		Infostats infostats;
		Helpinfo helpinfo;

// 		bool drawCVNeurons;

		
};

#endif
