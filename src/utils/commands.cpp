#include "commands.h"

Commands* Commands::Instance () 
{
	static Commands t;
	return &t;
}

Commands::Commands()
{
	registerCmd("quit", &Commands::quit);
	registerCmd("loadcritters", &WorldB::loadAllCritters);
	registerCmd("gui_togglepanel", &Maincanvas::swapChild);
}

void Commands::registerCmd(string name, void (Commands::*pt2Func)())
{
	cmd* c = new cmd();
	c->commandtype		= T_COMMAND;
	c->argtype		= A_NOARG;
	c->commandsMember	= pt2Func;
	cmdlist[name]		= c;
}

void Commands::registerCmd(string name, void (WorldB::*pt2Func)())
{
	cmd* c = new cmd();
	c->commandtype		= T_WORLD;
	c->argtype		= A_NOARG;
	c->worldMember		= pt2Func;
	cmdlist[name]		= c;
}

void Commands::registerCmd(string name, void (Maincanvas::*pt2Func)(const string&))
{
	cmd* c = new cmd();
	c->commandtype		= T_CANVAS;
	c->argtype		= A_STRING;
	c->canvasMember_string	= pt2Func;
	cmdlist[name]		= c;
}

// fixme private
void Commands::execCmd(const string& name)
{
	if ( cmdlist[name]->commandtype == 1 )
	{
		(this->*cmdlist[name]->commandsMember)();
	}
	else if ( cmdlist[name]->commandtype == 2 )
	{
		(world->*cmdlist[name]->worldMember)();
	}
	else if ( cmdlist[name]->commandtype == 3 )
	{
		(canvas->*cmdlist[name]->canvasMember)();
	}
}

void Commands::execCmd(const string& name, const string& str)
{
	if ( cmdlist[name]->commandtype == 3 )
	{
		(canvas->*cmdlist[name]->canvasMember_string)(str);
	}
}

// fixme public
void Commands::execCmd(const cmdsettings& cmds)
{
	// first check if called function exists
	if ( cmdlist[cmds.name] )
	{
		// check if expected types match
		if ( cmdlist[cmds.name]->argtype == cmds.argtype )
		{
			if ( cmds.argtype == A_NOARG )
				execCmd(cmds.name);
			else if ( cmds.argtype == A_STRING )
				execCmd(cmds.name, cmds.args);
		}
		else
		{
			cerr << "command '" << cmds.name << "'s args do not match: got " << cmds.argtype << " but expected " << cmdlist[cmds.name]->argtype << endl;
		}
	}
	else
	{
		cerr << "command '" << cmds.name << "does not exist" << endl;
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
