#include "commands.h"

Commands* Commands::Instance () 
{
	static Commands t;
	return &t;
}

Commands::Commands()
{
	registerCmd("quit", 0, &Commands::quit);
	registerCmd("loadcritters", 1, &WorldB::loadAllCritters);
}

void Commands::registerCmd(string name, unsigned int type, void (Commands::*pt2Func)())
{
	cmd* c = new cmd();
	c->commandtype = type;
	c->commandsMember = pt2Func;
	cmdlist[name] = c;
}

void Commands::registerCmd(string name, unsigned int type, void (WorldB::*pt2Func)())
{
	cmd* c = new cmd();
	c->commandtype = type;
	c->worldMember = pt2Func;
	cmdlist[name] = c;
}

void Commands::execCmd(const string& name)
{
	if ( cmdlist[name] )
	{
		if ( cmdlist[name]->commandtype == 0 )
			(this->*cmdlist[name]->commandsMember)();
		else if ( cmdlist[name]->commandtype == 1 )
			(world->*cmdlist[name]->worldMember)();
	}
}

void Commands::quit()
{
	exit(0);
}

Commands::~Commands()
{
	for( cmdit = cmdlist.begin(); cmdit != cmdlist.end(); cmdit++ )
	{
		delete cmdit->second;
		cmdlist.erase(cmdit->first);
	}
}
