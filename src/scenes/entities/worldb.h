#ifndef WORLDB_H
#define WORLDB_H

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
#include "critterb.h"

using namespace std;

class WorldB
{
	public:
		WorldB();
		~WorldB();

		vector<CritterB*>	critters;
		vector<Food*>		food;
		vector<Wall*>		walls;
		vector<Bullet*>		bullets;

		RandGen			randgen;

		float			freeEnergy;
		float			freeEnergyInfo;
		int			size;
		unsigned int		mutationRate;

		unsigned int		selectedCritter;
		bool			isSelected;

		void			process();
		void			drawWithGrid();

		float			foodenergy;
		void			insertRandomFood(int amount, float energy);

		void			insertCritter();
		void			positionCritterB(unsigned int cid);
		void			saveAllCritters();
		void			loadAllCritters();

		void			increaseMincritters();
		void			decreaseMincritters();

		void			createWall();
		void			destroyWall();
		void			toggleGate(unsigned int wid);

		bool			spotIsFree(Vector3f &position, float osize, unsigned int exclude);


		pthread_cond_t			condition_startthreads;
		pthread_mutex_t			condition_startthreads_mutex;

		pthread_cond_t			condition_threadsdone;
		pthread_mutex_t			condition_threadsdone_mutex;

		unsigned int			nthreads;
		unsigned int			registeredThreads;
		unsigned int			busyThreads;
		pthread_mutex_t			busyThreads_mutex;

		pthread_mutex_t			freeEnergy_mutex;
		pthread_mutex_t			position_mutex;

		vector<pthread_t>		threads;

	private:

		Dir			dirH;
		File			fileH;
		Parser			parseH;

		bool			flipnewbornes;

		Grid			grid;
		Floor			floor;
		Infobar			*infobar;
		float			foodsize;
		unsigned int		mincritters;
		string			homedir;
		string			progdir;
		string			savedir;
		string			loaddir;

		// methods

		void			removeCritter(unsigned int cid);
		bool			isTouchingAnything(float size, float x, float z);
		Vector3f		findEmptySpace(float objectsize);
		void			createDirs();
		bool			spotIsFree(Vector3f &position, float osize);


};

#endif
