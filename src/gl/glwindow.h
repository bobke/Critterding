#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <SDL/SDL.h>
// #include <SDL/SDL_opengl.h>
// #include <GL/glx.h>

#include "../gui/textprinter.h"
#include "../utils/displaylists.h"
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
		void runGLScene(GLScene* glscene);

	private:
		//	Resize Window
		void resize();
		void toggleFs();
		unsigned int w_bpp;		// Bits Per Pixel. With XFree86, highest = 24
		int w_width;
		int w_height;
		int n_width;
		int n_height;
		unsigned int fs;
		SDL_Surface* surface;
		const SDL_VideoInfo* vidInfo;
		int vidFlags;
		bool hwaccel;
		const unsigned int*	settingsfs;
		int mousex;
		int mousey;
		SDL_Event event;

};

#endif	// GLWINDOW_H
