#ifndef BUTTON_H
#define BUTTON_H

#include "panel.h"
#include "../utils/commands.h"

using namespace std;

class Button : public Panel
{
	public:
		Button();
		~Button();

		void draw();
		void click();
		string command;
	private:
		Commands* cmd;
};

#endif
