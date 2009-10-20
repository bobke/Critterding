#include "settingspanel.h"

Settingspanel::Settingspanel()
{
	v_width = 490;
	v_height = 550;

	isMovable = true;

	position.x = 50;
	position.y = 35;

	// FIXME camera sensitivity is missing
	unsigned int vint = 12;
	hspace = 10;
	vspace = 12;
	addSettingmutator("mincritters", hspace, vspace);

	// Special energy widgets
	vspace += vint; addMutator("energy", cmd.gen("decreaseenergy"), cmd.gen("increaseenergy"), hspace, vspace);
	vspace += vint; addSettingmutator("insertcritterevery", hspace, vspace);
	vspace += vint; addMutator("worldsizeX", cmd.gen("dec_worldsizex"), cmd.gen("inc_worldsizex"), hspace, vspace);
	vspace += vint; addMutator("worldsizeY", cmd.gen("dec_worldsizey"), cmd.gen("inc_worldsizey"), hspace, vspace);

// 	vspace += vint; 
	vspace += vint; addSettingmutator("fsX", hspace, vspace);
	vspace += vint; addSettingmutator("fsY", hspace, vspace);
	vspace += vint; addSettingmutator("fullscreen", hspace, vspace);
	vspace += vint; addSettingmutator("exit_if_empty", hspace, vspace);
	vspace += vint; addSettingmutator("killhalfdecreaseenergybypct", hspace, vspace);

// 	vspace += vint; 
	vspace += vint; addSettingmutator("critter_maxlifetime", hspace, vspace);
	vspace += vint; addSettingmutator("critter_maxenergy", hspace, vspace);
	vspace += vint; addSettingmutator("critter_startenergy", hspace, vspace);
	vspace += vint; addSettingmutator("critter_procinterval", hspace, vspace);
	vspace += vint; addSettingmutator("critter_minenergyproc", hspace, vspace);
	vspace += vint; addSettingmutator("critter_sightrange", hspace, vspace);
	vspace += vint; addSettingmutator("critter_autosaveinterval", hspace, vspace);
	vspace += vint; addSettingmutator("critter_killhalfat", hspace, vspace);
	vspace += vint; addSettingmutator("critter_enableomnivores", hspace, vspace);

// 	vspace += vint;
	vspace += vint; addSettingmutator("food_maxlifetime", hspace, vspace);
	vspace += vint; addSettingmutator("food_maxenergy", hspace, vspace);
	vspace += vint; addSettingmutator("food_size", hspace, vspace);

	vspace += vint;
	vspace += vint; addSettingmutator("body_maxmutations", hspace, vspace);
	vspace += vint; addSettingmutator("body_mutationrate", hspace, vspace);
	vspace += vint; addSettingmutator("body_maxbodyparts", hspace, vspace);
	vspace += vint; addSettingmutator("body_maxbodypartsatbuildtime", hspace, vspace);
	vspace += vint; addSettingmutator("body_minbodypartsize", hspace, vspace);
	vspace += vint; addSettingmutator("body_maxbodypartsize", hspace, vspace);
	vspace += vint; addSettingmutator("body_minheadsize", hspace, vspace);
	vspace += vint; addSettingmutator("body_maxheadsize", hspace, vspace);
	vspace += vint; addSettingmutator("body_percentmutateeffectaddbodypart", hspace, vspace);
	vspace += vint; addSettingmutator("body_percentmutateeffectremovebodypart", hspace, vspace);
	vspace += vint; addSettingmutator("body_percentmutateeffectresizebodypart", hspace, vspace);
	vspace += vint; addSettingmutator("body_percentmutateeffectresizebodypart_slightly", hspace, vspace);
	vspace += vint; addSettingmutator("body_percentmutateeffectchangeconstraintlimits", hspace, vspace);
	vspace += vint; addSettingmutator("body_percentmutateeffectchangeconstraintlimits_slightly", hspace, vspace);
	vspace += vint; addSettingmutator("body_percentmutateeffectchangeconstraintangles", hspace, vspace);
	vspace += vint; addSettingmutator("body_percentmutateeffectchangeconstraintangles_slightly", hspace, vspace);
	vspace += vint; addSettingmutator("body_percentmutateeffectchangeconstraintposition", hspace, vspace);
	vspace += vint; addSettingmutator("body_percentmutateeffectchangeconstraintposition_slightly", hspace, vspace);
	vspace += vint; addSettingmutator("body_percentmutateeffectresizehead", hspace, vspace);
	vspace += vint; addSettingmutator("body_percentmutateeffectresizehead_slightly", hspace, vspace);
	vspace += vint; addSettingmutator("body_percentmutateeffectrepositionhead", hspace, vspace);
}

void Settingspanel::addMutator(  const string& name, const cmdsettings& cmd1, const cmdsettings& cmd2, unsigned int posx, unsigned int posy  )
{
	unsigned int col1 = 10; unsigned int col2 = 350; unsigned int col3 = 430;
	string str(name); string strval = str; string strdec = str; string strinc = str;
	strval.append("val"); strdec.append("dec"); strinc.append("inc");

	addWidgetText( str, posx+col1, posy+9, name );
	addWidgetText( strval, posx+col2, posy+9, settings->getCVarPtr(name) );
	addWidgetButton( strdec, Vector2i(posx+col3, posy), Vector2i(11, 10), "-", Vector2i(3, 8), cmd1, 150, 0, 2 );
	addWidgetButton( strinc, Vector2i(posx+col3+18, posy), Vector2i(11, 10), "+", Vector2i(1, 8), cmd2, 150, 0, 2 );
}

void Settingspanel::addSettingmutator( const string& name, unsigned int posx, unsigned int posy )
{
	unsigned int col1 = 10; unsigned int col2 = 350; unsigned int col3 = 430;
	string str(name); string strval = str; string strdec = str; string strinc = str;
	strval.append("val"); strdec.append("dec"); strinc.append("inc");

	addWidgetText( str, posx+col1, posy+9, name );
	addWidgetText( strval, posx+col2, posy+9, settings->getCVarPtr(name) );
	addWidgetButton( strdec, Vector2i(posx+col3, posy), Vector2i(11, 10), "-", Vector2i(3, 8), cmd.gen("settings_decrease", name), 150, 0, 2 );
	addWidgetButton( strinc, Vector2i(posx+col3+18, posy), Vector2i(11, 10), "+", Vector2i(1, 8), cmd.gen("settings_increase", name), 150, 0, 2 );
}

Settingspanel::~Settingspanel()
{
}
