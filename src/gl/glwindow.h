#ifndef GLWINDOW_H
#define GLWINDOW_H


/* Standard OpenGL/GLX header files */
#include <GL/glx.h>
#include <GL/gl.h>
/* Headers needed for keys used in the program */
#include <X11/Xlib.h>
#include <X11/extensions/xf86vmode.h>
#include <X11/keysym.h>
/* Standard C header files */
#include <iostream>
#include <cstring>

#include "glscene.h"

using std::cerr;
using std::endl;


struct Structure {

	Display 			*dpy;		// The display. In X Windows, a display considers everything. Monitor, Mouse, Keyboard.
	int				screen;		// Window we are rendering too
	Window				win;		// Drawable surrface
	GLXContext			ctx;		// Stores information about our OpenGL Context
	XSetWindowAttributes		attr;
	BOOL				fs;		// Fullscreen flag
	XF86VidModeModeInfo		deskMode;	
	int				x,y;
	unsigned int			width, height;	// Width/Height of the window
	unsigned int			bpp;		// Bits Per Pixel. With XFree86, highest = 24
	unsigned int			owidth, oheight;// Original Width/Height of the window
// 	unsigned int			obpp;		// Original Bits Per Pixel, no need yet

};


class GLWindow {

		//	Resize Window
		void resize();

	public:
		GLWindow();
		~GLWindow();

		struct Structure GLWin;

		//	create the XFree86 window, with a GLX context.
		void create(const char* title, int width, int height, int bpp, BOOL fsflag);
		//	Destroy window and OpenGL Context, close the Display
		void destroy();

		//	Main loop for the program.
		void runGLScene(GLScene &glscene);

};

#endif	// GLWINDOW_H
