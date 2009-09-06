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
		void		makeFloor();
		void		insCritter(int nr);
		void		insMutatedCritter(CritterB& other, int nr, bool mutateBrain, bool mutateBody);
		void		insFood(int nr);
		
		float		critterspacing;
		bool		haveWinner;

		unsigned int	framecounter;
		
		unsigned int	testcounter;
};

#endif
