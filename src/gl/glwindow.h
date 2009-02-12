#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <GL/glx.h>

#include "../utils/settings.h"
#include "glscene.h"

struct Structure {
	Display 			*dpy;		// The display. In X Windows, a display considers everything. Monitor, Mouse, Keyboard.
	int				screen;		// Window we are rendering too
	Window				win;		// Drawable surrface
	GLXContext			ctx;		// Stores information about our OpenGL Context
	XSetWindowAttributes		attr;
	int				x,y;
	unsigned int			width, height;	// Width/Height of the window
	unsigned int			bpp;		// Bits Per Pixel. With XFree86, highest = 24
	unsigned int			owidth, oheight;// Original Width/Height of the window
};

class GLWindow {

	public:
		GLWindow();
		~GLWindow();

		struct Structure GLWin;

		//	create the XFree86 window, with a GLX context.
		void create(const char* title, int width, int height, int bpp);
		//	Destroy window and OpenGL Context, close the Display
		void destroy();
		//	Main loop for the program.
		void runGLScene(GLScene &glscene);

	private:
		//	Resize Window
		void resize();
};

#endif	// GLWINDOW_H
