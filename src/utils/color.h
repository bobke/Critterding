#ifndef COLOR_H
#define COLOR_H

#include "randgen.h"
using namespace std;

class Color
{
	public:
		Color();
		~Color();
		
		float r;
		float g;
		float b;
		float a;
		
		Color randomColorRGB();
		void normalize(Color* c );
		Color& operator=(const Color& other);
		Color normalized();
	private:
		RandGen			*randgen;
};

#endif
