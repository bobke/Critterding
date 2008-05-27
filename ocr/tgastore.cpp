#include "tgastore.h"

tgastore::tgastore()
{
}

unsigned int tgastore::load(const char *filename)
{
	vector<int>	picture;

	TGA *t = new TGA;
	if (!t->texture(filename)) {
		cerr << "could not load tga: " << filename << endl;
		exit(0);
	}

	int rowlength = t->size_x * t->channels;
	int items = t->size_x * t->size_y * t->channels;

// 	//convert to mono & revert, save in vector
// 	cerr << rowlength << "<>" << items << endl;
// 	for ( int h=items-rowlength; h >= 0; h -= rowlength )
// 	{
// 		for ( int w=h; w < (t->size_x*t->channels)+h; w += t->channels )
// 		{
// 			int total = 0;
// 
// 			if (t->channels) total = t->data[w+2] + t->data[w+1] + t->data[w];
// 
// 			if ( !total )
// 			{
// 				cerr << "X";
// 				picture.push_back(1);
// 			}
// 			else
// 			{
// 				cerr << ".";
// 				picture.push_back(0);
// 			}
// 		}
// 		cerr << "" << endl;
// 	}
// 	cerr << "" << endl;
// 	delete t;

	// save in vector
// 	cerr << rowlength << "<>" << items << endl;
	for ( int h=items-rowlength; h >= 0; h -= rowlength )
	{
		for ( int w=h; w < (t->size_x*t->channels)+h; w += t->channels )
		{
			//t->data[w+2] + t->data[w+1] + t->data[w];
			picture.push_back( t->data[w+2] );
			picture.push_back( t->data[w+1] );
			picture.push_back( t->data[w] );

// 			if ( t->data[w+2] > 0 ) cerr << "\e[0;31mR\e[0;0m";
// 			else cerr << ".";
// 			if ( t->data[w+1] > 0 ) cerr << "\e[0;32mG\e[0;0m";
// 			else cerr << ".";
// 			if ( t->data[w] > 150 ) cerr << "\e[0;34mB\e[0;0m";
// 			else cerr << ".";

		}
// 		cerr << "" << endl;
	}
// 	cerr << "" << endl;
	delete t;

	pictures.push_back(picture);
	return pictures.size()-1;
}

tgastore::~tgastore()
{
}


