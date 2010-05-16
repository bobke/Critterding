#ifndef ENTITY_H
#define ENTITY_H

#include "btBulletDynamicsCommon.h"
#include "../../utils/color.h"
using namespace std;

enum entityType {
	CRITTER = 0,
	FOOD,
	WALL
};

class Entity
{
	public:
		Entity();
		virtual ~Entity();
		virtual void		draw();
		virtual void		drawDimmed(float dim);

		entityType		type;
// 		float			color[4];
		Color			color;
		bool			isPicked;
	private:
};

#endif
