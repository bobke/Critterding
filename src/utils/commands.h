#ifndef COMMANDS_H
#define COMMANDS_H

#include <map>
#include <string>
#include "execcmd.h"
#include "../scenes/entities/worldb.h"
#include "settings.h"
#include "../gui/maincanvas.h"

using namespace std;

class Commands
{
	struct cmd
	{
		cmdtype commandtype;
		cmdargtype argtype;
		void (WorldB::*worldMember)();
		void (Commands::*commandsMember)();
		void (Maincanvas::*canvasMember)();
		void (Maincanvas::*canvasMember_string)(const string&);
		void (*member)(int);
	};


	public:
		static Commands* Instance();
		~Commands();

		WorldB* world;
		Maincanvas* canvas;
		void execCmd(const string& name);
		void execCmd(const string& name, const string& str);
		void execCmd(const cmdsettings& cmds);
	protected:
		Commands();
	private:
		static Commands* _instance;

		void registerCmd(string name, void (Commands::*pt2Func)());
		void registerCmd(string name, void (WorldB::*pt2Func)());
		void registerCmd(string name, void (Maincanvas::*pt2Func)(const string&));

		void quit();
		
		map<string, cmd*> cmdlist;
		typedef map <string, cmd*>::const_iterator cmdlist_iterator;
		cmdlist_iterator cmdit;
};

#endif
