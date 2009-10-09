#include "commands.h"

Commands* Commands::Instance () 
{
	static Commands t;
	return &t;
}

Commands::Commands()
{
	settings = Settings::Instance();
	registerCmd("quit", &Commands::quit);
	registerCmd("loadcritters", &WorldB::loadAllCritters);
	registerCmd("gui_togglepanel", &Maincanvas::swapChild);
	registerCmd("settings_increase", &Settings::increaseCVar);
	registerCmd("settings_decrease", &Settings::decreaseCVar);
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

void Commands::registerCmd(string name, void (Settings::*pt2Func)(const string&))
{
	cmd* c = new cmd();
	c->commandtype		= T_SETTINGS;
	c->argtype		= A_STRING;
	c->settingsMember_string= pt2Func;
	cmdlist[name]		= c;
}

// fixme private
void Commands::execCmd(const string& name)
{
	if ( cmdlist[name]->commandtype == T_COMMAND )
	{
		(this->*cmdlist[name]->commandsMember)();
	}
	else if ( cmdlist[name]->commandtype == T_WORLD )
	{
		(world->*cmdlist[name]->worldMember)();
	}
/*	else if ( cmdlist[name]->commandtype == T_CANVAS )
	{
		(canvas->*cmdlist[name]->canvasMember)();
	}
	else if ( cmdlist[name]->commandtype == T_SETTINGS )
	{
		(settings->*cmdlist[name]->settingsMember)();
	}*/
}

void Commands::execCmd(const string& name, const string& str)
{
	if ( cmdlist[name]->commandtype == T_CANVAS )
	{
		(canvas->*cmdlist[name]->canvasMember_string)(str);
	}
	else if ( cmdlist[name]->commandtype == T_SETTINGS )
	{
		(settings->*cmdlist[name]->settingsMember_string)(str);
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
