#ifndef CRITTERSELECTION_H
#define CRITTERSELECTION_H

#include <map>
#include "../scenes/entities/critterb.h"

using namespace std;

class Critterselection
{
	public:
		static Critterselection* Instance();
		~Critterselection();

		void registerCritter(CritterB* critter);
		void unregisterCritter(unsigned long critterID);

	protected:
		Critterselection();

	private:
		static Critterselection* _instance;

		map<unsigned long, CritterB*> clist;
		typedef map <unsigned long, CritterB*>::const_iterator clist_iterator;
		clist_iterator cit;
};

#endif
