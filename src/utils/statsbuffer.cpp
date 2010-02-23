#include "statsbuffer.h"

Statsbuffer* Statsbuffer::Instance () 
{
	static Statsbuffer t;
	return &t;
}

Statsbuffer::Statsbuffer()
{
// 	settings = Settings::Instance();

	recordInterval = 100;
	framecounter = 0;
	maxSnapshots = 3000;
}

void Statsbuffer::add( const vector<CritterB*>& critters, const vector<Food*>& food )
{
	// get stats of this frame
	current.neurons	= 0;
	current.synapses	= 0;
	current.adamdistance	= 0;
	current.bodyparts	= 0;
	current.weight		= 0;
	CritterB* c;
	for( unsigned int i=0; i < critters.size(); i++ )
	{
		c = critters[i];
		current.neurons	+= c->brain.totalNeurons;
		current.synapses	+= c->brain.totalSynapses;
		current.adamdistance	+= c->genotype->adamdist;
		current.bodyparts	+= c->body.bodyparts.size();
		current.weight		+= c->body.totalWeight;
	}
	current.critters		= critters.size();
	current.food			= food.size();

	if ( ++framecounter == recordInterval )
	{
		// remove expired snapshots
		if ( snapshots.size() == maxSnapshots )
			snapshots.erase(snapshots.begin());

		// insert the current snapshot
		snapshots.push_back(current);

		framecounter = 0;

		// debug output
/*		cerr << endl;
		for ( unsigned int i=0; i < snapshots.size(); i++ )
			cerr << "c: " << snapshots[i].critters << ", f: " << snapshots[i].food << endl;*/
	}
}
