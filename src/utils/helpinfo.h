#ifndef HELPINFO_H
#define HELPINFO_H

#include "textprinter.h"

using namespace std;

class Helpinfo
{
	public:
		Helpinfo();
		~Helpinfo();

		void draw();
		void swap();

	private:
		Textprinter *textprinter;
		bool active;

		unsigned int halfboxwidth;
		unsigned int halfboxheight;

		void printInfoLine(float heightpos, float widthpos1, float widthpos2, const char* key, const char* expl);
};

#endif
