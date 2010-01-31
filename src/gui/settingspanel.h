#ifndef SETTINGSPANEL_H
#define SETTINGSPANEL_H

#include "panel.h"

using namespace std;

class Settingspanel : public Panel
{
	public:
		Settingspanel();
		~Settingspanel();
	protected:
		unsigned int mutatorcol1;
		unsigned int mutatorcol2;
		unsigned int mutatorcol3;

		virtual void addMutator(  const string& name, const cmdsettings& cmd1, const cmdsettings& cmd2, unsigned int posx, unsigned int posy  );
		virtual void addSettingmutator( const string& name, unsigned int posx, unsigned int posy );
	private:

};

#endif
