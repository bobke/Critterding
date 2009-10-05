#ifndef STATSBUFFER_H
#define STATSBUFFER_H

// #include <iomanip>
#include <vector>
#include "settings.h"

using namespace std;

struct statsSnapshot
{
	unsigned int		critters;
	unsigned int		food;
};

class Statsbuffer
{
	public:
		static Statsbuffer*	Instance();
// 		Statsbuffer();
// 		~Statsbuffer();

		void add();
		vector<statsSnapshot>	snapshots;
	protected:
		Statsbuffer();
	private:
		static Statsbuffer*	_instance;

		Settings*		settings;
		
		unsigned int		recordInterval;
		unsigned int		framecounter;
		unsigned int		maxSnapshots;
};

#endif
