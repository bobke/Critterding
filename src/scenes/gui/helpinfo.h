#ifndef HELPINFO_H
#define HELPINFO_H

#include "../../gui/panel.h"

using namespace std;

class Helpinfo : public Panel
{
	public:
		Helpinfo();
		~Helpinfo();

		void draw();
	private:
		unsigned int halfboxwidth;
		unsigned int halfboxheight;

		void printInfoLine(float heightpos, float widthpos1, float widthpos2, const char* key, const char* expl);
};

#endif
