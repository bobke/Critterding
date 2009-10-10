#include "exitpanel.h"

Exitpanel::Exitpanel()
{
	v_width = 400;
	v_height = 86;

	isMovable = true;
	position.x = 100;
	position.y = 100;
// 	updateAbsPosition();

	addWidgetText( "askexit", 10, 20, "Are you sure you want to exit?" );
	addWidgetButton( "yes", 100, 40, "Yes", cmd.gen("quit") );
	addWidgetButton( "no", 200, 40, "No", cmd.gen("gui_togglepanel", "exitpanel") );
}

void Exitpanel::draw()
{
	if (active)
	{
// 		absPosition.x = (*parent->v_widthP/2) - (v_width/2);
// 		absPosition.y = (*parent->v_heightP/2) - (v_height/2);

// 		updateAbsPosition();
		drawBackground();
		drawBorders();
		drawChildren();
	}
}

Exitpanel::~Exitpanel()
{
}
