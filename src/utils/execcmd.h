#ifndef EXECCMD_H
#define EXECCMD_H

#include <string>

using namespace std;

	enum cmdtype {
		T_COMMAND = 1,
		T_WORLD,
		T_CANVAS
	};

	enum cmdargtype {
		A_NOARG = 1,
		A_INT,
		A_STRING
	};
	
	struct cmdsettings
	{
		string name;
		cmdargtype argtype;
		int argi;
		string args;
	};

	class Execcmd
	{
		public:
			Execcmd();
			~Execcmd();

			cmdsettings gen(const string& name);
			cmdsettings gen(const string& name, const string& str);
		private:
	};

#endif
