#include "button.h"

Button::Button()
{
	cmd = Commands::Instance();
	v_width = 60;
	v_height = 40;
}

void Button::draw()
{
	if (active)
	{
		updateAbsPosition();
// 		drawBackground();
		drawBorders();
		drawChildren();
	}
}

void Button::click()
{
	cmd->execCmd(command);
}

Button::~Button()
{
}
