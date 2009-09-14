#ifndef WORLDB_H
#define WORLDB_H

#include "btBulletDynamicsCommon.h"
#include "LinearMath/btIDebugDraw.h"
// #include "../../gl/gldebugdrawer.h"
// #include <sstream>
#include <iomanip>
// #include <vector>
// #include <string>
// #include <cstring> 
#include "../../utils/timer.h"
#include "../../utils/dir.h"
#include "../../utils/file.h"
#include "../../utils/parser.h"
#include "../../utils/randgen.h"
#include "../../utils/settings.h"
#include "../../utils/textmessage.h"
#include "../../utils/textverbosemessage.h"
#include "../../utils/raycast.h"
#include "../../utils/mousepicker.h"
#include "food.h"
#include "wall.h"
#include "critterb.h"
#include "camera.h"

using namespace std;

class WorldB
{
	public:
		WorldB();
		virtual			~WorldB();
		virtual void		init();
		virtual void		process();

		Settings*		settings;
		RandGen*		randgen;
		Mousepicker*		mousepicker;
		Camera camera;
		void resetCamera();

		//SpuGatheringCollisionDispatcher*	m_dispatcher;
		btCollisionDispatcher*	m_dispatcher;
		btBroadphaseInterface*	m_broadphase;
		btDefaultCollisionConfiguration* m_collisionConfiguration;
		btDynamicsWorld*	m_dynamicsWorld;
		btConstraintSolver*	m_solver;
		btAlignedObjectArray<btCollisionShape*>	m_collisionShapes;

		vector<CritterB*>	critters;
		vector<Food*>		food;
		vector<Wall*>		walls;

		unsigned long		currentCritterID;

		float			freeEnergy;
		//float			freeEnergyInfo;

		void			drawWithGrid();
		void			drawWithoutFaces();
		
		void			drawWithinCritterSight(unsigned int cid);

		void			startfoodamount(unsigned int amount);

		void			insertRandomFood(int amount, float energy);

		virtual void		insertCritter();
// 		void			positionCritterB(unsigned int cid);
		void			saveAllCritters();
		virtual void		loadAllCritters();

		void			killHalfOfCritters();
		void			pickBody(const int& x, const int& y);
		void			movePickedBody(const int& x, const int& y);
		void			movePickedBody();
		float			autosaveCounter;

		// vision
		unsigned char		*retina;
		unsigned int		items;

		const unsigned int*	retinasperrow;
		const unsigned int*	critter_retinasize;
		const unsigned int*	critter_maxenergy;

		void		checkCollisions( CritterB* c );

		inline void grabVision()
		{
			// Read pixels into retina
			if ( critters.size() > 0 )
			{
				// determine height
				unsigned int picheight = *critter_retinasize;
				unsigned int rows = critters.size();
				while ( rows > *retinasperrow )
				{
					picheight += *critter_retinasize;
					rows -= *retinasperrow;
				}
				glReadBuffer(GL_BACK);
				glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
				glReadPixels(0, 0, picwidth, picheight, GL_RGBA, GL_UNSIGNED_BYTE, retina);
			}
		}

		inline void renderVision()
		{
			// render critter vision
			for( unsigned int i=0; i < critters.size(); i++)
			{
				if ( critters[i]->body.mouths.size() > 0 )
				{
					critters[i]->place();
					drawWithinCritterSight(i);
				}
			}
		}

		Dir			dirH;
		Parser*			parseH;
		File			fileH;

		string			loaddir;
	private:
		Raycast*		raycast;

		unsigned int		insertCritterCounter;

// 		GLDebugDrawer debugDrawer;

		// FIXME give these a better place.  We also want to know where to save profiles to
		string			homedir;
		string			progdir;
		string			savedir;

		// methods
		inline void		removeCritter(unsigned int cid);
		inline void		createDirs();
		inline btVector3	findPosition();

		// Settings pointers.. performance
		const unsigned int*	critter_maxlifetime;
		const unsigned int*	critter_autosaveinterval;
		const unsigned int*	critter_killhalfat;
		const unsigned int*	critter_sightrange;

		const unsigned int*	food_maxlifetime;
		const unsigned int*	food_maxenergy;

		// vision opts
		unsigned int picwidth;
};

#endif
