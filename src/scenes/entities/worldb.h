#ifndef WORLDB_H
#define WORLDB_H

#include <sstream>
#include <iomanip>
#include <pthread.h>
#include <math.h>
#include <vector>
#include <string>
#include <cstring> 
#include "../../utils/timer.h"
#include "../../utils/dir.h"
#include "../../utils/file.h"
#include "../../utils/parser.h"
#include "../../utils/randgen.h"
#include "../../utils/settings.h"
#include "grid.h"
#include "floor.h"
#include "food.h"
#include "corpse.h"
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

		int			size;
		float			freeEnergy;
		float			freeEnergyInfo;

		unsigned int		selectedCritter;
		bool			isSelected;

		bool			doTimedInserts;
		void			toggleTimedInserts();

		void			process();
		void			drawWithGrid();
		void			drawWithinCritterSight(unsigned int cid);

		void			resize(unsigned int newsize);
		void			startfoodamount(unsigned int amount);

		void			insertRandomFood(int amount, float energy);

		void			insertCritter();
		void			positionCritterB(unsigned int cid);
		void			saveAllCritters();
		void			loadAllCritters();

		float			autosaveCounter;

		void			createWall();
		void			destroyWall();
		void			toggleGate(unsigned int wid);

		void			printSettings();

		bool			spotIsFree(Vector3f &position, float osize, unsigned int exclude);

	private:

		Settings		*settings;
		//RandGen			randgen;
		RandGen			*randgen;
		Parser			*parseH;

		vector<Food*>		food;
		vector<Corpse*>		corpses;
		vector<Wall*>		walls;
		vector<Bullet*>		bullets;

		Dir			dirH;
		File			fileH;

		unsigned int		timedInsertsCounter;

		unsigned char		*retina;
		unsigned int		items;

		Grid			grid;
		Floor			floor;
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

		GLuint			displayLists;
		void			generateList();

};

#endif
