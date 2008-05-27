#ifndef FILE_H
#define FILE_H

#include <string>
#include <fstream>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

using namespace std;

class File
{
	public:
		File();
		~File();

		void		save(string &filename, string &content);
		void		save(string &filename, string* content);
		void		open(string &filename, string &content);
};

#endif
