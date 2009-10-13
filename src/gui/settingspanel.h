#ifndef SETTINGSPANEL_H
#define SETTINGSPANEL_H

#include "panel.h"

using namespace std;

class Settingspanel : public Panel
{
	public:
		Settingspanel();
		~Settingspanel();

	private:
		unsigned int vspace;
		unsigned int hspace;
};

#endif
