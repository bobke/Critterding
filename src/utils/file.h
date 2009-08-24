#ifndef FILE_H
#define FILE_H

#include <string>
#include <fstream>
#include <iostream>

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

		bool		exists(string &file);
		bool		exists(const char* file);
		void		save(const string &filename, const string& content);
		void		save(const string &filename, string* content);
		bool		open(const string &filename, string& content);
		bool		open(const char* filename, string &content);
};

#endif
