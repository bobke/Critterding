#ifndef HELPINFO_H
#define HELPINFO_H

#include <string>
#include <iostream>
#include <sstream>
#include <GL/gl.h>
#include "fps.h"
#include "settings.h"
#include <stdarg.h>

using namespace std;

class Helpinfo
{
	public:
		Helpinfo();
		~Helpinfo();

		void draw();
		void swap();

	private:
		bool active;

		void printInfoLine(float heightpos, float widthpos1, float widthpos2, const char* key, const char* expl);
		void printGLf(const char *fmt, ...);
};

#endif
