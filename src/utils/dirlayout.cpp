#ifdef _WIN32
	#include <windows.h>
	#include <shlobj.h>
#endif
#include "dirlayout.h"

Dirlayout* Dirlayout::Instance () 
{
	static Dirlayout t;
	return &t; // _instance isn't needed in this case
}

Dirlayout::Dirlayout()
{
	createDirs();
}

void Dirlayout::createDirs()
{

#ifndef _WIN32
 	homedir = getenv("HOME");
 	if ( homedir.empty() ) {
		cout << "environment variable HOME not defined/detected" << endl;
		exit(0);
	}
	progdir = homedir;	progdir.append("/.critterding");
	savedir = progdir;	savedir.append("/save");
	loaddir = progdir;	loaddir.append("/load");
#else
	char mydoc[256];
	memset(mydoc, 0, sizeof(mydoc));

	SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, mydoc);
	homedir.assign(mydoc);
	progdir = homedir;	progdir.append("\\critterding");
	savedir = progdir;	savedir.append("\\save");
	loaddir = progdir;	loaddir.append("\\load");
#endif

//	cerr << progdir << endl;

	if ( !dirH.exists(progdir) ) dirH.make(progdir);
	if ( !dirH.exists(loaddir) ) dirH.make(loaddir);

}

