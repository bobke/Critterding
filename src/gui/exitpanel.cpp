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
	addWidgetButton( "yes", Vector2i(100, 40), Vector2i(50, 30), "Yes", Vector2i(15, 19), cmd.gen("quit"), 0, 0, 0 );
	addWidgetButton( "no", Vector2i(200, 40), Vector2i(50, 30), "No", Vector2i(18, 19), cmd.gen("gui_togglepanel", "exitpanel"), 0, 0, 0 );
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
