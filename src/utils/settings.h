#ifndef SETTINGS_H
#define SETTINGS_H

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include "file.h"
#include "parser.h"
#include "logbuffer.h"
#include "dirlayout.h"
// #include <GL/gl.h>

using namespace std;

enum cvartype {
	T_INT = 1,
	T_FLOAT,
	T_BOOL,
	T_STRING,
};

struct cvar
{
// 	string name;
	string comment;
	cvartype type;

	unsigned int int_val;
	unsigned int int_min;
	unsigned int int_max;
	bool loop;
	bool local;
};

class Settings
{
	public:
		static Settings* Instance();
		~Settings();

		void			registerCVar(const string& name, const unsigned int& defaultvalue, const unsigned int& min_val, const unsigned int& max_val, const string& comment);
		void			registerCVar(const string& name, const unsigned int& defaultvalue, const unsigned int& min_val, const unsigned int& max_val, bool loop, const string& comment);
		void			registerLocalCVar(const string& name, const unsigned int& defaultvalue, const unsigned int& min_val, const unsigned int& max_val, bool loop, const string& comment);

		void			unregisterCVar(const string& name);
		bool			isCVar(const string& name);

		unsigned int		getCVar(const string& name);
		const unsigned int*	getCVarPtr(const string& name);
		bool			setCVar(const string& name, const unsigned int& value);

		void			decreaseCVar(const string& name, const unsigned int& value);
		void			increaseCVar(const string& name, const unsigned int& value);

		void			decreaseCVar(const string& name);
		void			increaseCVar(const string& name);

		string profileName;

		int *winWidth;
		int *winHeight;

		// other vars
// 		float freeEnergyInfo;

		void doCommandLineOptions(int argc, char *argv[]);
		void loadProfile(char* filename);
		void saveProfile();
		
		string binarypath;

	protected:
		Settings();
	private:
		static Settings* _instance;

		File		fileH;
		Dir		dirH;
		Parser*		parseH;
		Dirlayout*	dirlayout;

		map<string, cvar*> cvarlist;
		typedef map <string, cvar*>::const_iterator cvarlist_iterator;
		cvarlist_iterator cvarit;

		stringstream helpinfo;
		void createHelpInfo();
};

#endif
