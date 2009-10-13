#include "exitpanel.h"

Exitpanel::Exitpanel()
{
	isMovable = true;
	position.x = 200;
	position.y = 557;
	v_width = 400;
	v_height = 86;

	addWidgetText( "askexit", 10, 20, "Are you sure you want to exit?" );
	addWidgetButton( "yes", Vector2i(100, 40), Vector2i(50, 30), "Yes", Vector2i(15, 19), cmd.gen("quit"), 0, 0, 0 );
	addWidgetButton( "no", Vector2i(200, 40), Vector2i(50, 30), "No", Vector2i(18, 19), cmd.gen("gui_togglepanel", "exitpanel"), 0, 0, 0 );
}

Exitpanel::~Exitpanel()
{
}
