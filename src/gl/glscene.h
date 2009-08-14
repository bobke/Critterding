#ifndef GLSCENE_H
#define GLSCENE_H

// Standard OpenGL/GLX header files
#include <GL/gl.h>

/* Headers needed for keys used in the program */
#include <X11/Xlib.h>
#include <X11/keysym.h>

class GLScene {
	public:
		GLScene();
		virtual ~GLScene();

		virtual void init();
		// This is the drawing function. Whatever needs to be drawn, goes in this function
		virtual void draw();
		// glwindow passes events to the scene
		virtual void handlekeyPressed(const KeySym& key);
		virtual void handlekeyReleased(const KeySym& key);

		virtual void clean();
};

#endif	// GLSCENE_H
