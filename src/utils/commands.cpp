#include "commands.h"

Commands* Commands::Instance () 
{
	static Commands t;
	return &t;
}

Commands::Commands()
{
	settings = Settings::Instance();
	critterselection = Critterselection::Instance();
	registerCmd("quit", &Commands::quit);

	registerCmd("decreaseenergy", &Commands::decreaseenergy);
	registerCmd("increaseenergy", &Commands::increaseenergy);
	registerCmd("dec_foodmaxenergy", &Commands::decreasefoodmaxenergy);
	registerCmd("inc_foodmaxenergy", &Commands::increasefoodmaxenergy);

	registerCmd("dec_worldsizex", &Commands::dec_worldsizex);
	registerCmd("inc_worldsizex", &Commands::inc_worldsizex);
	registerCmd("dec_worldsizey", &Commands::dec_worldsizey);
	registerCmd("inc_worldsizey", &Commands::inc_worldsizey);

	registerCmd("loadallcritters", &WorldB::loadAllCritters);
	registerCmd("saveallcritters", &WorldB::saveAllCritters);
	registerCmd("insertcritter", &WorldB::insertCritter);
	registerCmd("killhalfofcritters", &WorldB::killHalfOfCritters);
	registerCmd("camera_resetposition", &WorldB::resetCamera);

	registerCmd("camera_moveup", &WorldB::camera_moveup);
	registerCmd("camera_movedown", &WorldB::camera_movedown);
	registerCmd("camera_moveforward", &WorldB::camera_moveforward);
	registerCmd("camera_movebackward", &WorldB::camera_movebackward);
	registerCmd("camera_moveleft", &WorldB::camera_moveleft);
	registerCmd("camera_moveright", &WorldB::camera_moveright);
	registerCmd("camera_lookup", &WorldB::camera_lookup);
	registerCmd("camera_lookdown", &WorldB::camera_lookdown);
	registerCmd("camera_lookleft", &WorldB::camera_lookleft);
	registerCmd("camera_lookright", &WorldB::camera_lookright);
	registerCmd("camera_rollleft", &WorldB::camera_rollleft);
	registerCmd("camera_rollright", &WorldB::camera_rollright);

	registerCmd("gui_togglepanel", &Maincanvas::swapChild);
	registerCmd("settings_increase", &Settings::increaseCVar);
	registerCmd("settings_decrease", &Settings::decreaseCVar);

	registerCmd("cs_unregister", &Critterselection::unregisterCritterVID);
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

void Commands::registerCmd(string name, void (Critterselection::*pt2Func)(const unsigned int&))
{
	cmd* c = new cmd();
	c->commandtype		= T_CS;
	c->argtype		= A_UINT;
	c->critterselectionMember_uint= pt2Func;
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

void Commands::execCmd(const string& name, const unsigned int& ui)
{
	if ( cmdlist[name]->commandtype == T_CS )
	{
		(critterselection->*cmdlist[name]->critterselectionMember_uint)(ui);
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
			else if ( cmds.argtype == A_UINT )
				execCmd(cmds.name, cmds.argui);
		}
		else
			cerr << "command '" << cmds.name << "'s args do not match: got " << cmds.argtype << " but expected " << cmdlist[cmds.name]->argtype << endl;
	}
// 	else
// 		cerr << "command '" << cmds.name << "' does not exist" << endl;
}

void Commands::quit()
{
	SDL_Quit();
	exit(0);
}

void Commands::decreaseenergy()
{
	if ( ( (int)settings->getCVar("energy") - 1 ) >= 0 )
	{
		settings->setCVar("energy", settings->getCVar("energy")-1 );
		world->freeEnergy -= settings->getCVar("food_maxenergy");
		
		stringstream buf;
		buf << "energy: " << settings->getCVar("energy");
		Logbuffer::Instance()->add(buf);
	}
}

void Commands::increaseenergy()
{
	settings->setCVar("energy", settings->getCVar("energy")+1 );
	world->freeEnergy += settings->getCVar("food_maxenergy");

	stringstream buf;
	buf << "energy: " << settings->getCVar("energy");
	Logbuffer::Instance()->add(buf);
}

void Commands::decreasefoodmaxenergy()
{
	if ( ( (int)settings->getCVar("food_maxenergy") - 1 ) >= 0 )
	{
		world->freeEnergy -= settings->getCVar("energy");
		settings->setCVar("food_maxenergy", settings->getCVar("food_maxenergy")-1 );
	}
}

void Commands::increasefoodmaxenergy()
{
	world->freeEnergy += settings->getCVar("energy");
	settings->setCVar("food_maxenergy", settings->getCVar("food_maxenergy")+1 );
}

void Commands::dec_worldsizex() { settings->decreaseCVar("worldsizeX"); world->makeFloor(); }
void Commands::inc_worldsizex() { settings->increaseCVar("worldsizeX"); world->makeFloor(); }
void Commands::dec_worldsizey() { settings->decreaseCVar("worldsizeY"); world->makeFloor(); }
void Commands::inc_worldsizey() { settings->increaseCVar("worldsizeY"); world->makeFloor(); }

Commands::~Commands()
{
	for( cmdit = cmdlist.begin(); cmdit != cmdlist.end(); cmdit++ )
		delete cmdit->second;
}
