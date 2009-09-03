#ifndef WORLDRACE_H
#define WORLDRACE_H

#include "worldb.h"

class WorldRace : public WorldB {

	public:
		WorldRace();
		~WorldRace();

		void		process();
		void		init();
	private:
		void		insCritter(int nr);
		void		insMutatedCritter(CritterB& other, int nr, bool mutateBrain, bool mutateBody);
		void		insFood(int nr);
		
		unsigned int	numcritters;
		float		critterspacing;

		unsigned int	framecounter;
		unsigned int	testduration;
		
		unsigned int	testcounter;
};

#endif
