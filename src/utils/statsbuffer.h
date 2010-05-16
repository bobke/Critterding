#ifndef STATSBUFFER_H
#define STATSBUFFER_H

// #include <iomanip>
#include <vector>
// #include "settings.h"
#include "../scenes/entities/critterb.h"
#include "../scenes/entities/food.h"

using namespace std;

struct statsSnapshot
{
	unsigned int		critters;
	unsigned int		food;
	
	unsigned int		neurons;
	unsigned int		synapses;
	unsigned int		adamdistance;
	unsigned int		bodyparts;
	unsigned int		weight;
};

class Statsbuffer
{
	public:
		static Statsbuffer*	Instance();
// 		Statsbuffer();
// 		~Statsbuffer();

// 		void add( const vector<CritterB*>& critters, const vector<Food*>& food );
		void add( const vector<CritterB*>& critters, const vector<Entity*>& entities );

		vector<statsSnapshot> snapshots;
		statsSnapshot current;
		float info_totalWeight;
		
	protected:
		Statsbuffer();
	private:
		static Statsbuffer*	_instance;

// 		Settings*		settings;
		
		unsigned int		recordInterval;
		unsigned int		framecounter;
		unsigned int		maxSnapshots;
};

#endif
