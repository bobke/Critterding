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
	registerCmd("dec_worldsizez", &Commands::dec_worldsizez);
	registerCmd("inc_worldsizez", &Commands::inc_worldsizez);

	registerCmd("loadallcritters", &WorldB::loadAllCritters);
	registerCmd("saveallcritters", &WorldB::saveAllCritters);
	registerCmd("insertcritter", &WorldB::insertCritter);
	registerCmd("killhalfofcritters", &WorldB::killHalfOfCritters);
	registerCmd("camera_resetposition", &WorldB::resetCamera);
	registerCmd("toggle_pause", &WorldB::togglePause);
	registerCmd("toggle_sleeper", &WorldB::toggleSleeper);
	registerCmd("toggle_mouselook", &WorldB::toggleMouselook);

	registerCmd("critter_select", &WorldB::selectBody);
	registerCmd("critter_deselect", &WorldB::deselectBody);
	registerCmd("critter_pick", &WorldB::pickBody);
	registerCmd("critter_unpick", &WorldB::unpickBody);
	
	registerCmd("camera_moveup", &Commands::camera_moveup);
	registerCmd("camera_movedown", &Commands::camera_movedown);
	registerCmd("camera_moveforward", &Commands::camera_moveforward);
	registerCmd("camera_movebackward", &Commands::camera_movebackward);
	registerCmd("camera_moveleft", &Commands::camera_moveleft);
	registerCmd("camera_moveright", &Commands::camera_moveright);
	registerCmd("camera_lookup", &Commands::camera_lookup);
	registerCmd("camera_lookdown", &Commands::camera_lookdown);
	registerCmd("camera_lookleft", &Commands::camera_lookleft);
	registerCmd("camera_lookright", &Commands::camera_lookright);
	registerCmd("camera_rollleft", &Commands::camera_rollleft);
	registerCmd("camera_rollright", &Commands::camera_rollright);
	registerCmd("camera_lookhorizontal", &Commands::camera_lookhorizontal);
	registerCmd("camera_lookvertical", &Commands::camera_lookvertical);
	registerCmd("camera_movehorizontal", &Commands::camera_movehorizontal);
	registerCmd("camera_movevertical", &Commands::camera_movevertical);

	registerCmd("gui_togglepanel", &Maincanvas::swapChild);
	registerCmd("gui_toggle", &Maincanvas::swap);
	registerCmd("settings_saveprofile", &Settings::saveProfile);
	registerCmd("settings_increase", &Settings::increaseCVar);
	registerCmd("settings_decrease", &Settings::decreaseCVar);

	registerCmd("cs_unregister", &Critterselection::unregisterCritterVID);
// 	registerCmd("cs_select", &Critterselection::selectCritterVID);
	registerCmd("cs_select", &Commands::selectCritter);
	registerCmd("cs_selectall", &Commands::selectCritterAll);
	registerCmd("cs_clear", &Critterselection::clear);
	registerCmd("cs_kill", &WorldB::removeSelectedCritter);
	registerCmd("cs_killall", &WorldB::removeAllSelectedCritters);

	registerCmd("cs_duplicate", &WorldB::duplicateSelectedCritter);
	registerCmd("cs_spawnbrainmutant", &WorldB::spawnBrainMutantSelectedCritter);
	registerCmd("cs_spawnbodymutant", &WorldB::spawnBodyMutantSelectedCritter);
	registerCmd("cs_spawnbrainbodymutant", &WorldB::spawnBrainBodyMutantSelectedCritter);

	registerCmd("cs_duplicateall", &WorldB::duplicateAllSelectedCritters);
	registerCmd("cs_spawnbrainmutantall", &WorldB::spawnBrainMutantAllSelectedCritters);
	registerCmd("cs_spawnbodymutantall", &WorldB::spawnBodyMutantAllSelectedCritters);
	registerCmd("cs_spawnbrainbodymutantall", &WorldB::spawnBrainBodyMutantAllSelectedCritters);

	registerCmd("cs_feed", &WorldB::feedSelectedCritter);
	registerCmd("cs_resetage", &WorldB::resetageSelectedCritter);
}

void Commands::registerCmd(string name, void (Commands::*pt2Func)())
{
	cmd* c = new cmd();
	c->commandtype		= T_COMMAND;
	c->argtype		= A_NOARG;
	c->commandsMember	= pt2Func;
	cmdlist[name]		= c;
}

void Commands::registerCmd(string name, void (Commands::*pt2Func)(const unsigned int&))
{
	cmd* c = new cmd();
	c->commandtype		= T_COMMAND;
	c->argtype		= A_UINT;
	c->commandsMember_uint	= pt2Func;
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

void Commands::registerCmd(string name, void (Maincanvas::*pt2Func)())
{
	cmd* c = new cmd();
	c->commandtype		= T_CANVAS;
	c->argtype		= A_NOARG;
	c->canvasMember		= pt2Func;
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

void Commands::registerCmd(string name, void (Settings::*pt2Func)())
{
	cmd* c = new cmd();
	c->commandtype		= T_SETTINGS;
	c->argtype		= A_NOARG;
	c->settingsMember	= pt2Func;
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

void Commands::registerCmd(string name, void (Critterselection::*pt2Func)())
{
	cmd* c = new cmd();
	c->commandtype		= T_CS;
	c->argtype		= A_NOARG;
	c->critterselectionMember = pt2Func;
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
		(this->*cmdlist[name]->commandsMember)();
	else if ( cmdlist[name]->commandtype == T_WORLD )
		(world->*cmdlist[name]->worldMember)();
	else if ( cmdlist[name]->commandtype == T_CS )
		(critterselection->*cmdlist[name]->critterselectionMember)();
	else if ( cmdlist[name]->commandtype == T_CANVAS )
		(canvas->*cmdlist[name]->canvasMember)();
	else if ( cmdlist[name]->commandtype == T_SETTINGS )
		(settings->*cmdlist[name]->settingsMember)();
}

void Commands::execCmd(const string& name, const string& str)
{
	if ( cmdlist[name]->commandtype == T_CANVAS )
		(canvas->*cmdlist[name]->canvasMember_string)(str);
	else if ( cmdlist[name]->commandtype == T_SETTINGS )
		(settings->*cmdlist[name]->settingsMember_string)(str);
}

void Commands::execCmd(const string& name, const unsigned int& ui)
{
	if ( cmdlist[name]->commandtype == T_CS )
		(critterselection->*cmdlist[name]->critterselectionMember_uint)(ui);
	else if ( cmdlist[name]->commandtype == T_COMMAND )
		(this->*cmdlist[name]->commandsMember_uint)(ui);
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

void Commands::selectCritterAll()
{
	critterselection->clear();
	for ( unsigned int i=0; i < world->critters.size(); i++ )
		critterselection->registerCritter(world->critters[i]);
}

void Commands::selectCritter(const unsigned int& c)
{
	canvas->swapChild("critterview");
	critterselection->selectCritterVID(c);
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
void Commands::dec_worldsizez() { settings->decreaseCVar("worldsizeZ"); world->makeFloor(); }
void Commands::inc_worldsizez() { settings->increaseCVar("worldsizeZ"); world->makeFloor(); }

// camera ops
void Commands::camera_moveup() { world->camera.moveUp(0.01f); world->movePickedBodyFrom(); }
void Commands::camera_movedown() { world->camera.moveDown(0.01f); world->movePickedBodyFrom(); }
void Commands::camera_moveforward() { world->camera.moveForward(0.01f); world->movePickedBodyFrom(); }
void Commands::camera_movebackward() { world->camera.moveBackward(0.01f); world->movePickedBodyFrom(); }
void Commands::camera_moveleft() { world->camera.moveLeft(0.01f); world->movePickedBodyFrom(); }
void Commands::camera_moveright() { world->camera.moveRight(0.01f); world->movePickedBodyFrom(); }

void Commands::camera_lookup() { world->camera.lookUp(0.001f); world->calcMouseDirection(); world->movePickedBodyTo(); }
void Commands::camera_lookdown() { world->camera.lookDown(0.001f); world->calcMouseDirection(); world->movePickedBodyTo(); }
void Commands::camera_lookleft() { world->camera.lookLeft(0.001f); world->calcMouseDirection(); world->movePickedBodyTo(); }
void Commands::camera_lookright() { world->camera.lookRight(0.001f); world->calcMouseDirection(); world->movePickedBodyTo(); }
void Commands::camera_rollleft() { world->camera.rollLeft(0.001f); world->calcMouseDirection(); world->movePickedBodyTo(); }
void Commands::camera_rollright() { world->camera.rollRight(0.001f); world->calcMouseDirection(); world->movePickedBodyTo(); }

void Commands::camera_lookhorizontal() { world->camera.lookRight((float)world->relx/3000); world->calcMouseDirection(); world->movePickedBodyTo(); }
void Commands::camera_lookvertical() { world->camera.lookDown((float)world->rely/3000); world->calcMouseDirection(); world->movePickedBodyTo(); }

void Commands::camera_movehorizontal() { world->camera.moveRight((float)world->relx/300); world->movePickedBodyFrom(); }
void Commands::camera_movevertical() { world->camera.moveDown((float)world->rely/300); world->movePickedBodyFrom(); }

Commands::~Commands()
{
	for( cmdit = cmdlist.begin(); cmdit != cmdlist.end(); cmdit++ )
		delete cmdit->second;
}
