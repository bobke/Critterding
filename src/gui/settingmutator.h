#ifndef SETTINGMUTATOR_H
#define SETTINGMUTATOR_H

#include "container.h"

using namespace std;

class Settingmutator : public Container
{
	public:
		Settingmutator();
		~Settingmutator();
		void	draw();
		void	load(const string& svalue);
	protected:
	private:

};

#endif
