#ifndef SETTINGSPANEL_H
#define SETTINGSPANEL_H

#include "../../gui/panel.h"

using namespace std;

class Settingspanel : public Panel
{
	public:
		Settingspanel();
		~Settingspanel();

	private:
		unsigned int vspace;
		unsigned int hspace;
		void addMutator(  const string& name, const cmdsettings& cmd1, const cmdsettings& cmd2, unsigned int posx, unsigned int posy  );
		void addSettingmutator( const string& name, unsigned int posx, unsigned int posy );
};

#endif
