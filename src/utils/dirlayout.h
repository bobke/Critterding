#ifndef DIRLAYOUT_H
#define DIRLAYOUT_H

#include "dir.h"
#include <iostream>
#include <string>

using namespace std;

class Dirlayout
{
	public:
		static Dirlayout* Instance();
		void createDirs();

		string			homedir;
		string			progdir;
		string			savedir;
		string			loaddir;

	protected:
		Dirlayout();
	private:
		static Dirlayout* _instance;

		Dir			dirH;
};

#endif
