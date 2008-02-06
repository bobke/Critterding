#ifndef INFOBAR_H
#define INFOBAR_H

#include <string>
#include <iostream>
#include "GL/gl.h"
#include <GL/glut.h>
#include <GL/glu.h>

using namespace std;
using std::cerr;
using std::endl;

class Infobar
{
	public:
		static Infobar* instance();

		void draw(string text);

	private:
		Infobar() {}
		~Infobar() {}
		static Infobar* trueSelf;
};
#endif
