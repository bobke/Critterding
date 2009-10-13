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

void Button::genEvent(const string& name, const cmdsettings& cmds, unsigned int responsetime, unsigned int minfresponsetime, unsigned int fresponseinterval )
{
	eventname = name;
	events->registerEvent(eventname, cmds, responsetime, minfresponsetime, fresponseinterval );
}

void Button::click()
{
// 	cerr << "activating event " << endl;
	events->activateEvent(eventname);
}

void Button::release()
{
	events->deactivateEvent(eventname);
}

Button::~Button()
{
}
