#ifndef INFOBAR_H
#define INFOBAR_H

#include "fps.h"
#include "textprinter.h"

using namespace std;

class Infobar
{
	public:
		Infobar();
		~Infobar();

		unsigned int critters;
		unsigned int food;
		unsigned int corpses;
		unsigned int bullets;

		float barheight;

		void draw();
// 		void printInfoLine(float heightpos, float widthpos1, float widthpos2, const char* key, string& str);
		void printInfoLine(float heightpos, float widthpos1, float widthpos2, const char* key, const char *fmt, ...);
		void swap();
		unsigned int height();

	private:
		Fps fps;

		// horizontal/vertical spacers (padding)
		float hsp;
		float vsp;

		bool active;
};

#endif
