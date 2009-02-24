#ifndef TEXTPRINTER_H
#define TEXTPRINTER_H

#include <stdarg.h>
#include <string>

#include "settings.h"

#define FTGL_TEXTURE 5

#include "ftgl/FTGL/ftgl.h"

using namespace std;

class Textprinter
{
	public:
		static Textprinter* Instance();
		void printTextprinter();

		// get bounding boxes
		FTPoint getBBox(string& str);
		FTPoint getBBox(const char *fmt, ...);

		string getFormattedString(const char *fmt, ...);

		// print left aligned
		void print(float x, float y, const char *fmt, ...);
		void print(float x, float y, string& str);
		// print right aligned
		void printR(float x, float y, const char *fmt, ...);

		void setUpFonts();
	protected:
		Textprinter();
	private:
		FTFont** fonts;
};

#endif
