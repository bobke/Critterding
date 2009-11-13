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
		void click(const int& button);
		void release(const int& button);
		void genEvent( const int& button, const string& name, const cmdsettings& cmds, unsigned int responsetime, unsigned int minfresponsetime, unsigned int fresponseinterval );
// 		cmdsettings command;
	private:
// 		Commands* cmd;
// 		vector<string> eventnames;

		map<unsigned int, string> buttonlist;
// 		typedef map <string, cmd*>::const_iterator cmdlist_iterator;
// 		cmdlist_iterator cmdit;

		Events *events;
		string eventname;
};

#endif
