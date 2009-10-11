#ifndef SETTINGSPANEL_H
#define SETTINGSPANEL_H

#include "panel.h"

using namespace std;

class Settingspanel : public Panel
{
	public:
		Settingspanel();
		~Settingspanel();

		void draw();
	private:
		unsigned int vspace;
		void loadWidgets(const string& svalue, const Vector2i& posoffset);
};

#endif
