#ifndef COMMANDS_H
#define COMMANDS_H

#include <map>
#include <string>
#include "../scenes/entities/worldb.h"

using namespace std;

class Commands
{
	struct cmd
	{
		unsigned int commandtype;
		void (WorldB::*worldMember)();
		void (Commands::*commandsMember)();
		void (*member)(int);
	};


	public:
		static Commands* Instance();
		~Commands();

		WorldB* world;
		void execCmd(const string& name);
	protected:
		Commands();
	private:
		static Commands* _instance;

		void registerCmd(string name, unsigned int type, void (Commands::*pt2Func)());
		void registerCmd(string name, unsigned int type, void (WorldB::*pt2Func)());

		void quit();
		
		map<string, cmd*> cmdlist;
		typedef map <string, cmd*>::const_iterator cmdlist_iterator;
		cmdlist_iterator cmdit;
		
};

#endif
