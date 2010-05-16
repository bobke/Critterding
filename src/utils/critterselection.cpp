#include "critterselection.h"

Critterselection* Critterselection::Instance () 
{
	static Critterselection t;
	return &t;
}

Critterselection::Critterselection()
{
	cv_activate = false;
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

void Critterselection::clear()
{
	while ( clist.size() > 0 )
		clist.erase(clist.begin());
}

void Critterselection::unregisterCritterVID(const unsigned int& vectorID)
{
	if ( vectorID < clist.size() )
		clist.erase(clist.begin()+vectorID);
}

void Critterselection::registerCritter(CritterB* critter)
{
// 	selectCritter(critter);

	// skip if already registered;
	for ( unsigned int i = 0; i < clist.size(); i++ )
		if ( clist[i]->critterID == critter->critterID )
			return;

	clist.push_back(critter);
}

void Critterselection::unregisterCritter(CritterB* critter)
{
	for ( unsigned int i = 0; i < clist.size(); i++ )
		if ( clist[i]->critterID == critter->critterID )
		{
			clist.erase(clist.begin()+i);
			return;
		}
}

void Critterselection::deselectCritter(CritterB* critter)
{
	if ( selectedCritter && selectedCritter == critter )
		selectedCritter = 0;
}

void Critterselection::deselectCritter(const unsigned long& critterID)
{
	if ( selectedCritter && selectedCritter->critterID == critterID )
		selectedCritter = 0;
}

void Critterselection::selectCritter(CritterB* critter)
{
	cv_activate = true;
	selectedCritter = critter;
}

void Critterselection::selectCritterVID(const unsigned int& vectorID)
{
	cv_activate = true;
	selectedCritter = clist[vectorID];
}

Critterselection::~Critterselection()
{
}
