#ifndef INFOBAR_H
#define INFOBAR_H

#include <string>
#include <iostream>
#include <sstream>
#include <GL/gl.h>
#include "fps.h"
#include "settings.h"

using namespace std;

class Infobar
{
	public:
		Infobar();
		~Infobar();

		unsigned int critters;
		unsigned int food;
		unsigned int corpses;

		void draw();
		void swap();

	private:
		Settings *settings;
		Fps fps;

		bool active;

		void printGLf(const char *fmt, ...);
};

#endif
