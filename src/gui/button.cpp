#include "button.h"

Button::Button()
{
// 	cmd = Commands::Instance();
	events = Events::Instance();
	v_width = 60;
	v_height = 40;
}

void Button::draw()
{
	if (active)
	{
		drawBorders();
		drawChildren();
	}
}

void Button::genEvent(const int& button, const string& name, const cmdsettings& cmds, unsigned int responsetime, unsigned int minfresponsetime, unsigned int fresponseinterval )
{
	eventname = name;
	buttonlist[button] = eventname;
	events->registerEvent(eventname, cmds, responsetime, minfresponsetime, fresponseinterval );
}

void Button::click(const int& button)
{
// 	cerr << "activating event with button" << button << endl;
	events->activateEvent( buttonlist[button] );
}

void Button::release(const int& button)
{
	events->deactivateEvent( buttonlist[button] );
}

Button::~Button()
{
}
