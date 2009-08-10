#ifndef FOOD_H
#define FOOD_H

#include "btBulletDynamicsCommon.h"
#include "GL/gl.h"

#include "../../utils/settings.h"
#include "../../utils/displaylists.h"
#include "vector3f.h"
#include "body.h"

using namespace std;

class Food
{
	public:
		Food();
		~Food();

		Body			body;
		void			createBody(btDynamicsWorld* m_dynamicsWorld, btVector3 startOffset);
		unsigned int		type;

		void			draw();
		
		btScalar		position[16];

		float			color[3];

		unsigned int		lifetime;
		float			energyLevel;
		unsigned int		totalFrames;

	private:
		Settings		*settings;
};

#endif
