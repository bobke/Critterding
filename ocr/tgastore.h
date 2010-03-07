#ifndef TGASTORE_H
#define TGASTORE_H

#include <vector>
#include <tga.h>

class tgastore
{
	public:
	tgastore();
	~tgastore();

	unsigned int		load(const char *filename);
	vector<vector<int> >	pictures;

	
};

#endif
