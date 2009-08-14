#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <SDL/SDL.h>
// #include <SDL/SDL_opengl.h>
// #include <GL/glx.h>

#include "../utils/settings.h"
#include "glscene.h"

class GLWindow {

	public:
		GLWindow();
		~GLWindow();

		//	create the XFree86 window, with a GLX context.
		void create(const char* title, int width, int height, int bpp);
		//	Destroy window and OpenGL Context, close the Display
		void destroy();
		//	Main loop for the program.
		void runGLScene(GLScene &glscene);

	private:
		//	Resize Window
		void resize();
		unsigned int w_bpp;		// Bits Per Pixel. With XFree86, highest = 24
		unsigned int w_width;
		unsigned int w_height;
};

#endif	// GLWINDOW_H
