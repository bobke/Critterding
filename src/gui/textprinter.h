#ifndef TEXTPRINTER_H
#define TEXTPRINTER_H

#include <stdarg.h>
#include <string>

#include "../utils/settings.h"
#include "../utils/file.h"
#include "../math/vector2i.h"

// #define FTGL_TEXTURE 5
#include "../utils/ftgl/FTGL/ftgl.h"

using namespace std;

class Textprinter
{
	public:
		static Textprinter* Instance();
		void printTextprinter();

		// get bounding boxes
// 		FTPoint getBBox(const string& str);
// 		FTPoint getBBox(const char *fmt, ...);
		unsigned int getWidth(const char *fmt, ...);
		unsigned int getWidth(const string& str);
		Vector2i getDimensions(const string& str);

		string getFormattedString(const char *fmt, ...);

		// print left aligned
		void print(int x, int y, const char *fmt, ...);
		void print(int x, int y, const string& str);
		void print(int x, int y, const long unsigned int& longuint);
		void print(const Vector2i& pos, const string& str);
		void print(const Vector2i& pos, const unsigned int* num);
		// print right aligned
		void printR(float x, float y, const char *fmt, ...);

		void setUpFonts();

	protected:
		Textprinter();
	private:
		FTFont** fonts;
		File file;
		
		va_list ap;     /* our argument pointer */
		char text[256];

};

#endif
