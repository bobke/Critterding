#ifndef SETTINGSBODYPANEL_H
#define SETTINGSBODYPANEL_H

#include "../../gui/settingspanel.h"

using namespace std;

class Settingsbodypanel : public Settingspanel
{
	public:
		Settingsbodypanel();
		~Settingsbodypanel();

	private:
		unsigned int vspace;
		unsigned int hspace;
};

#endif
