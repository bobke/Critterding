#ifndef ENTITY_H
#define ENTITY_H

#include "btBulletDynamicsCommon.h"
#include "../../utils/color.h"
using namespace std;

class Entity
{
	public:
		Entity();
		~Entity();
		
		unsigned int type;
// 		float			color[4];
		Color			color;
		bool			isPicked;
	private:
};

#endif
