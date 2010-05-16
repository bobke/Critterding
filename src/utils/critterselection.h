#ifndef CRITTERSELECTION_H
#define CRITTERSELECTION_H

#include <vector>
#include "../scenes/entities/critterb.h"

using namespace std;

class Critterselection
{
	public:
		static Critterselection* Instance();
		~Critterselection();

		void registerCritter(CritterB* critter);
		void unregisterCritter(CritterB* critter);
		void unregisterCritterID(const unsigned long& critterID);
		void unregisterCritterVID(const unsigned int& vectorID);
		void selectCritter(CritterB* critter);
		void selectCritterVID(const unsigned int& vectorID);
		void deselectCritter(CritterB* critter);
		void deselectCritter(const unsigned long& critterID);
		void clear();

		vector<CritterB*>	clist;
		CritterB*		selectedCritter;
		
		bool			cv_activate;

	protected:
		Critterselection();

	private:
		static Critterselection* _instance;

/*		map<unsigned long, CritterB*> clist;
		typedef map <unsigned long, CritterB*>::const_iterator clist_iterator;
		clist_iterator cit;*/
};

#endif
