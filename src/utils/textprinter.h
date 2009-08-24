#ifndef TEXTPRINTER_H
#define TEXTPRINTER_H

#include <stdarg.h>
#include <string>

#include "settings.h"
#include "file.h"

#define FTGL_TEXTURE 5
#include "ftgl/FTGL/ftgl.h"

using namespace std;

class Textprinter
{
	public:
		static Textprinter* Instance();
		void printTextprinter();

		// get bounding boxes
		FTPoint getBBox(const string& str);
		FTPoint getBBox(const char *fmt, ...);

		string getFormattedString(const char *fmt, ...);

		// print left aligned
		void print(float x, float y, const char *fmt, ...);
		void print(float x, float y, const string& str);
		// print right aligned
		void printR(float x, float y, const char *fmt, ...);

	protected:
		Textprinter();
	private:
		FTFont** fonts;
		void setUpFonts();
		File file;
};

#endif
