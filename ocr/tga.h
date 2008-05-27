/*
	www.morrowland.com
	apron@morrowland.com
*/

#ifndef _INCLUDED_RENDER_TGA_H__
#define _INCLUDED_RENDER_TGA_H__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define TGA_RGB		2
#define TGA_A		3
#define TGA_RLE		10

class TGA
{
	public:
		TGA();
		~TGA();

		int channels;
		int size_x;	
		int size_y;
		unsigned char *data;

		bool texture(const char *filename);

	private:
		//static image *load(const char *filename);
		bool load(const char *filename);
};

#endif //_INCLUDED_RENDER_TGA_H__
