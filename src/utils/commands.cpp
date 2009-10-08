#include "commands.h"

Commands* Commands::Instance () 
{
	static Commands t;
	return &t;
}

Commands::Commands()
{
	registerCmd("loadcritters", 0, &WorldB::loadAllCritters);
}

void Commands::registerCmd(string name, unsigned int type, void (WorldB::*pt2Func)())
{
	cmd* c = new cmd();
	c->commandtype = type;
	c->worldMember = pt2Func;
	cmdlist[name] = c;
}

void Commands::execCmd(string name)
{
	if ( cmdlist[name]->commandtype == 0 )
	{
		(world->*cmdlist[name]->worldMember)();
	}
}

Commands::~Commands()
{
	for( cmdit = cmdlist.begin(); cmdit != cmdlist.end(); cmdit++ )
	{
		delete cmdit->second;
		cmdlist.erase(cmdit->first);
	}
}
