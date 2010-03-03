#ifndef FOOD_H
#define FOOD_H

#include "btBulletDynamicsCommon.h"
#include "GL/gl.h"

#include "../../utils/settings.h"
#include "../../utils/displaylists.h"
#include "entity.h"
#include "body.h"

using namespace std;

class Food : public Entity
{
	public:
		Food();
		~Food();

		Body			body;
		void			createBody(btDynamicsWorld* m_dynamicsWorld, const btVector3& startOffset);

		void			draw();
		
		btScalar		position[16];

// 		float			color[3];

		unsigned int		lifetime;
		float			energyLevel;
		unsigned int		totalFrames;
		btDefaultMotionState* myMotionState;
	private:
		Settings		*settings;

		btBoxShape* boxShape;
		btVector3 halfExtent;

		const unsigned int*	food_size;
};

#endif
