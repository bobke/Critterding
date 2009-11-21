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
	selectCritter(critter);

	// skip if already registered;
	for ( unsigned int i = 0; i < clist.size(); i++ )
		if ( clist[i]->critterID == critter->critterID )
			return;

	clist.push_back(critter);
}

void Critterselection::deselectCritter(CritterB* critter)
{
	if ( selectedCritter == critter )
		selectedCritter = 0;
}

void Critterselection::selectCritter(CritterB* critter)
{
	selectedCritter = critter;
}

void Critterselection::selectCritterVID(const unsigned int& vectorID)
{
	selectedCritter = clist[vectorID];
}

Critterselection::~Critterselection()
{
}
