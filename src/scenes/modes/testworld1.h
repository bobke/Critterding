#ifndef TESTWORLD1_H
#define TESTWORLD1_H

#include "../entities/worldb.h"

class TestWorld1 : public WorldB {

	public:
		TestWorld1();
		~TestWorld1();

		void		process();
		void		init();
	private:
		btVector3 findPosition();
		float decSizeFactor;
		unsigned int elevations;
};

#endif
