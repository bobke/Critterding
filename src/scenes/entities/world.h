#ifndef WORLD_H
#define WORLD_H

#include <sstream>
#include <iomanip>
#include <pthread.h>
#include <math.h>
#include <vector>
#include <string>

#include "../../utils/dir.h"
#include "../../utils/file.h"
#include "../../utils/parser.h"
#include "../../utils/randgen.h"
#include "grid.h"
#include "floor.h"
#include "infobar.h"
#include "food.h"
#include "wall.h"
#include "bullet.h"
#include "critter.h"

using namespace std;

class World{
	public:
		World();
		~World();

		vector<Critter*>	critters;
		vector<Food*>		food;
		vector<Wall*>		walls;
		vector<Bullet*>		bullets;
		pthread_mutex_t		bulletsV_mutex;

		RandGen			randgen;

		float			freeEnergy;
		float			freeEnergyInfo;
		pthread_mutex_t		freeEnergy_mutex;
		int			size;
		unsigned int		mutationRate;

		// THREADING
		pthread_t		bgthread;
		bool			bgthreadActive;
		bool			bgthreadIsSpawned;

		pthread_cond_t		condition_startthreads;
		pthread_mutex_t		condition_startthreads_mutex;

		vector<unsigned int>	cqueue;
		pthread_mutex_t		cqueue_mutex;

		unsigned int		selectedCritter;
		bool			isSelected;

		void			process();
		void			drawWithGrid();
		void			drawWithFloor();

		float			foodenergy;


		void			insertCritter();
		void			positionCritter(unsigned int cid);
		void			saveAllCritters();
		void			loadAllCritters();
		void			processCritter(unsigned int i);

		void			increaseMincritters();
		void			decreaseMincritters();
		void			increaseMaxcritters();
		void			decreaseMaxcritters();

		void			toggleBGthread();
		void			createWall();
		void			destroyWall();
		void			toggleGate(unsigned int wid);

	private:

		Dir			dirH;
		File			fileH;
		Parser			parseH;

		bool			flipnewbornes;

		Grid			grid;
		Floor			floor;
		Infobar			*infobar;
		float			foodsize;
		unsigned int		maxcritters;
		unsigned int		mincritters;
		string			homedir;
		string			progdir;
		string			savedir;
		string			loaddir;

		// methods

		void			insertRandomFood(int amount, float energy);
		void			removeCritter(unsigned int cid);
		bool			isTouchingAnything(float size, float x, float z);
		Vector3f		findEmptySpace(float objectsize);
		void			createDirs();
		bool			spotIsFree(Vector3f &position, float osize, unsigned int exclude);
		bool			spotIsFree(Vector3f &position, float osize);
};

#endif
