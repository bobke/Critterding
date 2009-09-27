#include "statsbuffer.h"

Statsbuffer* Statsbuffer::Instance () 
{
	static Statsbuffer t;
	return &t;
}

Statsbuffer::Statsbuffer()
{
	settings = Settings::Instance();

	recordInterval = 100;
	framecounter = 0;
	maxSnapshots = 3000;
}

void Statsbuffer::add()
{
	if ( ++framecounter == recordInterval )
	{
		// remove expired snapshots
		if ( snapshots.size() == maxSnapshots )
			snapshots.erase(snapshots.begin());

		// insert a new snapshot
		snapshots.push_back(statsSnapshot());
		statsSnapshot* s = &snapshots[snapshots.size() - 1];

		s->critters		= settings->info_critters;
		s->food			= settings->info_food;

		framecounter = 0;

		// debug output
/*		cerr << endl;
		for ( unsigned int i=0; i < snapshots.size(); i++ )
			cerr << "c: " << snapshots[i].critters << ", f: " << snapshots[i].food << endl;*/
	}
}
