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
// #include "grid.h"
// #include "floor.h"
#include "food.h"
// #include "corpse.h"
#include "wall.h"
// #include "bullet.h"
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

		void			insertCritter();
// 		void			positionCritterB(unsigned int cid);
		void			saveAllCritters();
		void			loadAllCritters();

		void			killHalfOfCritters();
		void			pickBody(const int& x, const int& y);
		void			movePickedBody(const int& x, const int& y);
		void			movePickedBody();
		float			autosaveCounter;

// 		// picking
// 		int gPickingConstraintId;
// 		btVector3 gOldPickingPos;
// 		btVector3 gHitPos;
// 		float gOldPickingDist;
// 		btRigidBody* pickedBody;//for deactivation state
// 
// 		btScalar mousePickClamping;
// 		btTypedConstraint* m_pickConstraint;
// 		bool* pickedBool;

		// vision
		unsigned char		*retina;
		unsigned int		items;

		const unsigned int*	retinasperrow;
		const unsigned int*	critter_retinasize;

		// FIXME: inline
		void		grabVision();

	private:
		Parser*			parseH;
		Raycast*		raycast;
		Dir			dirH;
		File			fileH;

		unsigned int		insertCritterCounter;

// 		GLDebugDrawer debugDrawer;

		// FIXME give these a better place.  We also want to know where to save profiles to
		string			homedir;
		string			progdir;
		string			savedir;
		string			loaddir;

		// methods
		inline void		removeCritter(unsigned int cid);
		inline void		createDirs();
		inline btVector3	findPosition();

		// Settings pointers.. performance
		const unsigned int*	critter_maxlifetime;
		const unsigned int*	critter_maxenergy;
		const unsigned int*	critter_autosaveinterval;
		const unsigned int*	critter_killhalfat;
		const unsigned int*	critter_sightrange;

		const unsigned int*	food_maxlifetime;
		const unsigned int*	food_maxenergy;

};

#endif
