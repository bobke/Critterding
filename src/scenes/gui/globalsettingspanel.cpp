#include "globalsettingspanel.h"

Globalsettingspanel::Globalsettingspanel()
{
	v_width = 490;
	v_height = 340;

	isMovable = true;

	position.x = 50;
	position.y = 35;

	// FIXME camera sensitivity is missing
	unsigned int vint = 12;
	hspace = 10;
	vspace = vint; addSettingmutator("mincritters", hspace, vspace);
	vspace += vint; addMutator("energy", cmd.gen("decreaseenergy"), cmd.gen("increaseenergy"), hspace, vspace);
	vspace += vint; addSettingmutator("insertcritterevery", hspace, vspace);
	vspace += vint; addMutator("worldsizeX", cmd.gen("dec_worldsizex"), cmd.gen("inc_worldsizex"), hspace, vspace);
	vspace += vint; addMutator("worldsizeY", cmd.gen("dec_worldsizey"), cmd.gen("inc_worldsizey"), hspace, vspace);

// 	vspace += vint; 
	vspace += vint; addSettingmutator("fsX", hspace, vspace);
	vspace += vint; addSettingmutator("fsY", hspace, vspace);
	vspace += vint; addSettingmutator("fullscreen", hspace, vspace);
	vspace += vint; addSettingmutator("colormode", hspace, vspace);
	vspace += vint; addSettingmutator("exit_if_empty", hspace, vspace);
	vspace += vint; addSettingmutator("killhalfdecreaseenergybypct", hspace, vspace);
	vspace += vint; addSettingmutator("fpslimit", hspace, vspace);

// 	vspace += vint; 
	vspace += vint; addSettingmutator("critter_maxlifetime", hspace, vspace);
	vspace += vint; addSettingmutator("critter_maxenergy", hspace, vspace);
	vspace += vint; addSettingmutator("critter_startenergy", hspace, vspace);
	vspace += vint; addSettingmutator("critter_procinterval", hspace, vspace);
	vspace += vint; addSettingmutator("critter_minenergyproc", hspace, vspace);
	vspace += vint; addSettingmutator("critter_sightrange", hspace, vspace);
	vspace += vint; addSettingmutator("critter_autosaveinterval", hspace, vspace);
	vspace += vint; addSettingmutator("critter_autoexchangeinterval", hspace, vspace);
	vspace += vint; addSettingmutator("critter_killhalfat", hspace, vspace);
	vspace += vint; addSettingmutator("critter_enableomnivores", hspace, vspace);
	vspace += vint; addSettingmutator("critter_raycastvision", hspace, vspace);

// 	vspace += vint;
	vspace += vint; addSettingmutator("food_maxlifetime", hspace, vspace);
	vspace += vint; addMutator("food_maxenergy", cmd.gen("dec_foodmaxenergy"), cmd.gen("inc_foodmaxenergy"), hspace, vspace);
	vspace += vint; addSettingmutator("food_size", hspace, vspace);
}

Globalsettingspanel::~Globalsettingspanel()
{
}
