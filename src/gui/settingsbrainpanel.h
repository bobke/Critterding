#ifndef SETTINGSBRAINPANEL_H
#define SETTINGSBRAINPANEL_H

#include "panel.h"

using namespace std;

class Settingsbrainpanel : public Panel
{
	public:
		Settingsbrainpanel();
		~Settingsbrainpanel();

	private:
		unsigned int vspace;
		unsigned int hspace;
		void addSettingmutator( const string& name, unsigned int posx, unsigned int posy );
};

#endif
