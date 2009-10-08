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
	private:
		Commands* cmd;
};

#endif
