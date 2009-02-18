#ifndef TEXTPRINTER_H
#define TEXTPRINTER_H

#include <stdarg.h>
#include <string>

#include "settings.h"

#define FTGL_TEXTURE 5

//#include <FTGL/ftgl.h>

#include "ftgl/FTGL/ftgl.h"

using namespace std;

class Textprinter
{
	public:
		static Textprinter* Instance();
		void printTextprinter();
/*		void printGLf(const char *fmt, ...);*/
		void print(float x, float y, const char *fmt, ...);
		void print(float x, float y, string *str);
		void setUpFonts();
	protected:
		Textprinter();
	private:
		FTFont** fonts;
};

#endif