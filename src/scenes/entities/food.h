#ifndef FOOD_H
#define FOOD_H
#ifdef _WIN32
	#include <time.h>
	#include <windows.h>
#endif

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
		void			createBody(btDynamicsWorld* m_dynamicsWorld, const btVector3& startOffset);
		unsigned int		type;

		void			draw();
		
		btScalar		position[16];

		float			color[3];

		unsigned int		lifetime;
		float			energyLevel;
		unsigned int		totalFrames;

		bool			isPicked;
	private:
		Settings		*settings;
};

#endif
