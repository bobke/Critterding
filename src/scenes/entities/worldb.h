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

		int			size;
		float			freeEnergy;
		float			freeEnergyInfo;
		unsigned int		retinasperrow;

		unsigned int		critter_maxlifetime;
		float			critter_maxenergy;
		float			critter_size;
		float			critter_speed;
		float			critter_sightrange;
		unsigned int		critter_colorneurons;
		unsigned int		critter_mutationrate;
		unsigned int		critter_maxmutateruns;

		unsigned int		food_maxlifetime;
		float			food_maxenergy;
		float			food_size;

		unsigned int		selectedCritter;
		bool			isSelected;

		bool			doTimedInserts;
		void			toggleTimedInserts();

		void			process();
		void			drawWithGrid();

		void			resize(unsigned int newsize);
		void			startfoodamount(unsigned int amount);

		void			insertRandomFood(int amount, float energy);

		void			insertCritter();
		void			positionCritterB(unsigned int cid);
		void			saveAllCritters();
		void			loadAllCritters();

		void			increaseMincritters();
		void			decreaseMincritters();
		void			setMincritters(unsigned int c);

		void			createWall();
		void			destroyWall();
		void			toggleGate(unsigned int wid);

		bool			spotIsFree(Vector3f &position, float osize, unsigned int exclude);

	private:

		RandGen			randgen;

		vector<Food*>		food;
		vector<Wall*>		walls;
		vector<Bullet*>		bullets;

		Dir			dirH;
		File			fileH;
		Parser			parseH;

		unsigned int		timedInsertsCounter;

		unsigned char		*retina;
		unsigned int		items;

		bool			flipnewbornes;

		Grid			grid;
		Floor			floor;
		Infobar			*infobar;
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
