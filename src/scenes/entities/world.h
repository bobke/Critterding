#ifndef WORLD_H
#define WORLD_H

// [19:55] <Ingar> btw een tof truukske
// [19:55] <Ingar> #include <iomanip>
// [19:55] <Ingar> std::cout << "FPS (altijd 3 posities): " << setw(3) << fps << std::endl;

// #include <sys/stat.h>
// #include <sys/types.h>
// #include <errno.h>
// #include <dirent.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <fstream>

#include <sstream>
#include <pthread.h>
#include <math.h>
#include <vector>
#include <string>

#include "../../utils/dir.h"
#include "../../utils/file.h"
#include "../../utils/parser.h"
#include "randgen.h"
#include "grid.h"
#include "floor.h"
#include "infobar.h"
#include "food.h"
#include "bullet.h"
#include "critter.h"

using namespace std;

class World{
	public:
		World();
		~World();

		vector<Critter*>	critters;
		vector<Food*>		food;
		vector<Bullet*>		bullets;
		pthread_mutex_t		bulletsV_mutex;

		RandGen			randgen;

		float			freeEnergy;
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

		void			process();
		void			drawWithGrid();
		void			drawWithFloor();

		float			foodenergy;


		void			insertCritter();
		unsigned int		copyCritter(unsigned int cid);
		void			positionCritter(unsigned int cid);
		void			saveAllCritters();
		void			loadAllCritters();
		void			processCritter(unsigned int i);

		void			increaseMincritters();
		void			decreaseMincritters();
		void			increaseMaxcritters();
		void			decreaseMaxcritters();

		void			toggleBGthread();

	private:

		Dir			dirH;
		File			fileH;
		Parser			parseH;

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
};

#endif
