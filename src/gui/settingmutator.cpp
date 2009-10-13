#include "settingmutator.h"

Settingmutator::Settingmutator()
{
}

void Settingmutator::draw()
{
	drawChildren();
}

void Settingmutator::load(const string& svalue)
{
	unsigned int col1 = 10;
	unsigned int col2 = 350;
	unsigned int col3 = 430;
	
	string str(svalue);
	string strval = str;
	string strdec = str;
	string strinc = str;
	strval.append("val");
	strdec.append("dec");
	strinc.append("inc");

	addWidgetText( svalue, absPosition.x+col1, absPosition.y+9, svalue );
	addWidgetText( strval, absPosition.x+col2, absPosition.y+9, settings->getCVarPtr(svalue) );
	addWidgetButton( strdec, Vector2i(absPosition.x+col3, absPosition.y), Vector2i(11, 10), "-", Vector2i(3, 8), cmd.gen("settings_decrease", svalue), 150, 0, 2 );
	addWidgetButton( strinc, Vector2i(absPosition.x+col3+18, absPosition.y), Vector2i(11, 10), "+", Vector2i(1, 8), cmd.gen("settings_increase", svalue), 150, 0, 2 );
}


Settingmutator::~Settingmutator()
{
}
