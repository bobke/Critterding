#ifndef ENTITY_H
#define ENTITY_H

#include "btBulletDynamicsCommon.h"
using namespace std;

class Entity
{
	public:
		Entity();
		~Entity();
		
		unsigned int type;
		float			color[4];
	private:
};

#endif
