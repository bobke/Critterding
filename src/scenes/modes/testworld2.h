#ifndef TESTWORLD2_H
#define TESTWORLD2_H

#include "../entities/worldb.h"

class TestWorld2 : public WorldB {

	public:
		TestWorld2();
		~TestWorld2();

		void		process();
		void		init();
		void		drawWithGrid();
	private:
		void		drawSphere(btScalar radius, int lats, int longs);
		btVector3	findPosition();
		void		makeFloor();
		void		drawfloor();
		void		childPositionOffset(btVector3* v);
		
		btCollisionObject* fixedGround;
		btCollisionShape* groundShape;
		btTransform groundTransform;
};

#endif
