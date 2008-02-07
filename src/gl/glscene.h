#ifndef GLSCENE_H
#define GLSCENE_H


// Standard OpenGL/GLX header files
#include <GL/gl.h>

/* Headers needed for keys used in the program */
#include <X11/Xlib.h>
#include <X11/extensions/xf86vmode.h>
#include <X11/keysym.h>
// Standard C header files
#include <iostream>
#include <cmath>

using std::cerr;
using std::endl;


class GLScene {
	public:
		GLScene();
		virtual ~GLScene();

		virtual void init();
		// This is the drawing function. Whatever needs to be drawn, goes in this function
		virtual void draw();
		// glwindow passes events to the scene
		virtual void handlekey(const KeySym& key);

		virtual void clean();

		unsigned int *width;
		unsigned int *height;
};

#endif	// GLSCENE_H
