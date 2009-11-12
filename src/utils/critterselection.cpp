#include "critterselection.h"

Critterselection* Critterselection::Instance () 
{
	static Critterselection t;
	return &t;
}

Critterselection::Critterselection()
{
}

void Critterselection::unregisterCritterID(const unsigned long& critterID)
{
	for ( unsigned int i = 0; i < clist.size(); i++ )
		if ( clist[i]->critterID == critterID )
		{
			clist.erase(clist.begin()+i);
			return;
		}
}

void Critterselection::unregisterCritterVID(const unsigned int& vectorID)
{
	if ( vectorID < clist.size() )
		clist.erase(clist.begin()+vectorID);
}

void Critterselection::registerCritter(CritterB* critter)
{
	// skip if already registered;
	for ( unsigned int i = 0; i < clist.size(); i++ )
		if ( clist[i]->critterID == critter->critterID )
			return;
	
	clist.push_back(critter);
/*
	if ( !clist[critter->critterID] )
	{
		clist[critter->critterID] = critter;
		cerr << critter->critterID << " was added :)" << endl;
	}
	else
	{
		cerr << critter->critterID << " skipped" << endl;
	}*/
}

Critterselection::~Critterselection()
{
}
