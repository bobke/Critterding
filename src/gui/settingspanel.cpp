#include "settingspanel.h"

Settingspanel::Settingspanel()
{
	v_width = 700;
	v_height = 500;

	isMovable = true;

	position.x = 50;
	position.y = 50;

	vspace = 13;
	addWidgetText( "critter_maxlifetime", 10, 20, "mincritters" );
// 	addWidgetText( "critter_maxlifetime_val", 100, 20, "what it should be tho" );

	addWidgetButton( "up", 100, 40, "Up", cmd.gen("settings_increase", "mincritters") );
	addWidgetButton( "down", 200, 40, "Down", cmd.gen("settings_decrease", "mincritters") );
}

void Settingspanel::draw()
{
	if (active)
	{
		updateAbsPosition();
		drawBackground();
		drawBorders();
		drawChildren();
	}
}

Settingspanel::~Settingspanel()
{
}
