#ifndef HEADLESS_H
#define HEADLESS_H

#include "../utils/settings.h"
#include "../gl/glscene.h"

class Headless {

	public:
		Headless();
		~Headless();

		//	create the XFree86 window, with a GLX context.
		void create();
		//	Main loop for the program.
		void runGLScene(GLScene* glscene);
	private:
		int w_width;
		int w_height;
};

#endif	// GLWINDOW_H
