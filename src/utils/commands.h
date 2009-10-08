#ifndef COMMANDS_H
#define COMMANDS_H

#include <map>
#include <string>
#include "../scenes/entities/worldb.h"

using namespace std;

struct cmd
{
	unsigned int commandtype;
	void (WorldB::*worldMember)();
};

class Commands
{
	public:
		static Commands* Instance();
		~Commands();

		WorldB* world;
		void execCmd(string name);
	protected:
		Commands();
	private:
		static Commands* _instance;

		void registerCmd(string name, unsigned int type, void (WorldB::*pt2Func)());

		map<string, cmd*> cmdlist;
		typedef map <string, cmd*>::const_iterator cmdlist_iterator;
		cmdlist_iterator cmdit;
		
};

#endif
