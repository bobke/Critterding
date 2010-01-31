#include "settingspanel.h"

Settingspanel::Settingspanel()
{
// 	isTouchable = true;
// 	isTransparant = true;
// 	zaxis = 0;

	mutatorcol1 = 10;
	mutatorcol2 = 200;
	mutatorcol3 = 280;
}

void Settingspanel::addMutator(  const string& name, const cmdsettings& cmd1, const cmdsettings& cmd2, unsigned int posx, unsigned int posy  )
{
	string str(name); string strval = str; string strdec = str; string strinc = str;
	strval.append("val"); strdec.append("dec"); strinc.append("inc");

	addWidgetText( str, posx+mutatorcol1, posy+9, name );
	addWidgetText( strval, posx+mutatorcol2, posy+9, settings->getCVarPtr(name) );
	addWidgetButton( strdec, Vector2i(posx+mutatorcol3, posy), Vector2i(11, 10), "-", Vector2i(3, 8), cmd1, 150, 0, 2 );
	addWidgetButton( strinc, Vector2i(posx+mutatorcol3+18, posy), Vector2i(11, 10), "+", Vector2i(1, 8), cmd2, 150, 0, 2 );
}

void Settingspanel::addSettingmutator( const string& name, unsigned int posx, unsigned int posy )
{
	string str(name); string strval = str; string strdec = str; string strinc = str;
	strval.append("val"); strdec.append("dec"); strinc.append("inc");

	addWidgetText( str, posx+mutatorcol1, posy+9, name );
	addWidgetText( strval, posx+mutatorcol2, posy+9, settings->getCVarPtr(name) );
	addWidgetButton( strdec, Vector2i(posx+mutatorcol3, posy), Vector2i(11, 10), "-", Vector2i(3, 8), cmd.gen("settings_decrease", name), 150, 0, 2 );
	addWidgetButton( strinc, Vector2i(posx+mutatorcol3+18, posy), Vector2i(11, 10), "+", Vector2i(1, 8), cmd.gen("settings_increase", name), 150, 0, 2 );
}

Settingspanel::~Settingspanel()
{
}
