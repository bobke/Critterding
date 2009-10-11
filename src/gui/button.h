#ifndef BUTTON_H
#define BUTTON_H

#include "panel.h"
#include "../utils/events.h"

// #include "../utils/commands.h"

using namespace std;

class Button : public Panel
{
	public:
		Button();
		~Button();

		void draw();
		void click();
		void release();
		void genEvent(const string& name, const cmdsettings& cmds, unsigned int responsetime, unsigned int minfresponsetime, unsigned int fresponseinterval);
// 		cmdsettings command;
	private:
// 		Commands* cmd;
		Events *events;
		string eventname;
};

#endif
