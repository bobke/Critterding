#include "critterselection.h"

Critterselection* Critterselection::Instance () 
{
	static Critterselection t;
	return &t;
}

Critterselection::Critterselection()
{
}

void Critterselection::unregisterCritter(unsigned long critterID)
{
	cit = clist.find(critterID);
	if ( cit != clist.end() )
	{
		clist.erase(cit->first);
		cerr << critterID << " was removed :)" << endl;
	}
}

void Critterselection::registerCritter(CritterB* critter)
{
	if ( !clist[critter->critterID] )
	{
		clist[critter->critterID] = critter;
		cerr << critter->critterID << " was added :)" << endl;
	}
	else
	{
		cerr << critter->critterID << " skipped" << endl;
	}
}

Critterselection::~Critterselection()
{
}
