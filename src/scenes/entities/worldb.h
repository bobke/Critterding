#ifndef WORLDB_H
#define WORLDB_H

#include "btBulletDynamicsCommon.h"
// #include "LinearMath/btIDebugDraw.h"
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
#include "../../utils/raycast.h"
#include "../../utils/mousepicker.h"
#include "../../utils/statsbuffer.h"
#include "../../utils/critterselection.h"
#include "../../utils/logbuffer.h"

#include "../gui/textverbosemessage.h"

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
		virtual btVector3	findPosition();
		virtual		void makeFloor();
		float			insertHight;
		void			getGeneralStats();
		void			killHalf();
		void			expireFood();
		void			expireCritters();
		void			autoinsertFood();
		void			autosaveCritters();
		void			autoexchangeCritters();
		void			autoinsertCritters();
		void			eat( CritterB* c );
		void			procreate( CritterB* c );
		void			makeDefaultFloor();
		
		Settings*		settings;
		Critterselection	*critterselection;
		Statsbuffer*		statsBuffer;
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

		virtual void		drawWithGrid();
		virtual void		drawWithoutFaces();
		
		void			drawWithinCritterSight(CritterB *c);
		void			drawWithinCritterSight(unsigned int cid);

		virtual void		drawfloor();
		virtual void		childPositionOffset(btVector3* v);

		void			startfoodamount(unsigned int amount);

		void			insertRandomFood(int amount, float energy);

		virtual void		insertCritter();
// 		void			positionCritterB(unsigned int cid);
		void			saveAllCritters();
		virtual void		loadAllCritters();

		void			removeSelectedCritter();
		void			removeAllSelectedCritters();
		void			duplicateCritter(unsigned int cid, bool brainmutant, bool bodymutant);

		void			duplicateSelectedCritter();
		void			spawnBrainMutantSelectedCritter();
		void			spawnBodyMutantSelectedCritter();
		void			spawnBrainBodyMutantSelectedCritter();
		void			feedSelectedCritter();
		void			resetageSelectedCritter();

		void			duplicateAllSelectedCritters();
		void			spawnBrainMutantAllSelectedCritters();
		void			spawnBodyMutantAllSelectedCritters();
		void			spawnBrainBodyMutantAllSelectedCritters();

		void			killHalfOfCritters();

		void			pickBody(const int& x, const int& y);
		void			selectBody(const int& x, const int& y);
		void			castMouseRay();
		void			movePickedBodyTo();
		void			movePickedBodyFrom();
		float			autosaveCounter;
		float			autoexchangeCounter;

		// vision
		unsigned char		*retina;
		unsigned int		items;

		const unsigned int*	retinasperrow;
		const unsigned int*	critter_retinasize;
		const unsigned int*	critter_maxenergy;

		void			checkCollisions( CritterB* c );

		void grabVision();

		void renderVision();

		void			calcMouseDirection();
		void			moveInMouseDirection(bool towards);

		Dir			dirH;
		Parser*			parseH;
		File			fileH;

		string			loaddir;

		bool			mouseRayHit;
		Entity*			mouseRayHitEntity;

		// camera operations (needed for commands)
		void 			camera_moveup();
		void 			camera_movedown();
		void 			camera_moveforward();
		void 			camera_movebackward();
		void 			camera_moveleft();
		void 			camera_moveright();
		void 			camera_lookup();
		void 			camera_lookdown();
		void 			camera_lookleft();
		void 			camera_lookright();
		void 			camera_rollleft();
		void 			camera_rollright();

		// pointers to parents (evolution) mousepos
		int* mousex;
		int* mousey;

	private:
		Raycast*		raycast;

		castResult		mouseRay;
		btVector3		mouseRayTo;

		unsigned int		insertCritterCounter;
// 		GLDebugDrawer debugDrawer;

		// FIXME give these a better place.  We also want to know where to save profiles to
		string			homedir;
		string			progdir;
		string			savedir;

		// methods
		inline void		removeCritter(unsigned int cid);
		inline void		createDirs();

		// Settings pointers.. performance
		const unsigned int*	critter_maxlifetime;
		const unsigned int*	critter_autosaveinterval;
		const unsigned int*	critter_autoexchangeinterval;
		const unsigned int*	critter_killhalfat;
		const unsigned int*	critter_sightrange;
		const unsigned int*	critter_raycastvision;

		const unsigned int*	food_maxlifetime;
		const unsigned int*	food_maxenergy;
		const unsigned int*	energy;

		// vision opts
		unsigned int picwidth;
		btScalar drawposition[16];
		
		btManifoldArray   manifoldArray;

		int			findSelectedCritterID();
		int			findCritterID(unsigned int cid);
};

#endif
