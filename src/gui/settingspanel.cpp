#include "settingspanel.h"

Settingspanel::Settingspanel()
{
	v_width = 300;
	v_height = 300;

	isMovable = true;

	position.x = 50;
	position.y = 50;
// 	updateAbsPosition();

	vspace = 15;
	Vector2i offset(10, vspace);
	loadWidgets("mincritters" , offset);

	offset.y += vspace;
	offset.y += vspace; loadWidgets("critter_maxlifetime" , offset);
	offset.y += vspace; loadWidgets("critter_maxenergy" , offset);
	offset.y += vspace; loadWidgets("critter_startenergy" , offset);
	offset.y += vspace; loadWidgets("critter_procinterval" , offset);
	offset.y += vspace; loadWidgets("critter_minenergyproc" , offset);
	offset.y += vspace; loadWidgets("critter_sightrange" , offset);
	offset.y += vspace; loadWidgets("critter_autosaveinterval" , offset);
	offset.y += vspace; loadWidgets("critter_killhalfat" , offset);
	offset.y += vspace; loadWidgets("critter_enableomnivores" , offset);

	offset.y += vspace;
	offset.y += vspace; loadWidgets("food_maxlifetime" , offset);
	offset.y += vspace; loadWidgets("food_maxenergy" , offset);
	offset.y += vspace; loadWidgets("food_size" , offset);
}

void Settingspanel::draw()
{
	if (active)
	{
		drawBackground();
		drawBorders();
		drawChildren();
	}
}

void Settingspanel::loadWidgets(const string& svalue, const Vector2i& posoffset)
{
	unsigned int col1 = 10;
	unsigned int col2 = 180;
	unsigned int col3 = 230;
	
	string str(svalue);
	string strval = str; string strdec = str; string strinc = str;
	strval.append("val"); strdec.append("dec"); strinc.append("inc");

	addWidgetText( svalue, posoffset.x+col1, posoffset.y+20, svalue );
	addWidgetText( strval, posoffset.x+col2, posoffset.y+20, settings->getCVarPtr(svalue) );
	addWidgetButton( strdec, Vector2i(posoffset.x+col3, posoffset.y+10), Vector2i(10, 10), "-", Vector2i(3, 8), cmd.gen("settings_decrease", svalue), 150, 0, 2 );
	addWidgetButton( strinc, Vector2i(posoffset.x+col3+18, posoffset.y+10), Vector2i(10, 10), "+", Vector2i(1, 8), cmd.gen("settings_increase", svalue), 150, 0, 2 );
}


Settingspanel::~Settingspanel()
{
}
