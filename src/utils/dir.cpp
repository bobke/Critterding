#include "dir.h"

Dir::Dir()
{
}

bool Dir::exists(string &directory)
{
	DIR *pdir;
	pdir = opendir(directory.c_str());
	if (pdir)
	{
		closedir(pdir);
		return true;
	}
	else		return false;
}

void Dir::make(string &directory)
{
	mkdir( directory.c_str(), 0755 );
}

void Dir::listContents(string dir, vector<string> &files)
{
	DIR *dp;
	struct dirent *dirp;
	if((dp  = opendir(dir.c_str())) != NULL)
	{
		while ((dirp = readdir(dp)) != NULL)
		{
			if ( string(dirp->d_name) != "." && string(dirp->d_name) != ".." )
			{
				files.push_back(string(dirp->d_name));
			}
		}
		closedir(dp);
	}
}

void Dir::listContentsFull(string dir, vector<string> &files)
{
	DIR *dp;
	struct dirent *dirp;
	if((dp  = opendir(dir.c_str())) != NULL)
	{
		while ((dirp = readdir(dp)) != NULL)
		{
			if ( string(dirp->d_name) != "." && string(dirp->d_name) != ".." )
			{
				string fulldir = dir;
				fulldir.append("/");
				fulldir.append(dirp->d_name);
				files.push_back(fulldir);
			}
		}
		closedir(dp);
	}
}


Dir::~Dir()
{
}


