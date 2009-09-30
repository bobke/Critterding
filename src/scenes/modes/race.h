#ifndef WORLDRACE_H
#define WORLDRACE_H

#include "../entities/worldb.h"

class WorldRace : public WorldB {

	public:
		WorldRace();
		~WorldRace();

		void		process();
		void		init();
		void		insertCritter();
		void		loadAllCritters();
	private:
		void		makeRaceFloor();
		void		insRandomCritter(int nr);
		void		insMutatedCritter(CritterB& other, int nr, unsigned int id, bool mutateBrain, bool mutateBody);
		void		insFood(int nr);
		
		float		critterspacing;

		bool		haveWinner;

		unsigned int	framecounter;
		
		unsigned int	testcounter;
};

#endif
