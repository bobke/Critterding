#ifndef ROUNDWORLD_H
#define ROUNDWORLD_H

#include "../entities/worldb.h"

class Roundworld : public WorldB {

	public:
		Roundworld();
		~Roundworld();

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
