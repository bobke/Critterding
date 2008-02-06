#ifndef DIR_H
#define DIR_H

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <dirent.h>
// #include <stdio.h>
// #include <stdlib.h>

#include <string>
#include <sstream>
#include <vector>


using namespace std;

class Dir
{
	public:
		Dir();
		~Dir();

		bool		exists(string &directory);
		void		make(string &directory);

		void		listContents(string dir, vector<string> &files);
		void		listContentsFull(string dir, vector<string> &files);

};

#endif
