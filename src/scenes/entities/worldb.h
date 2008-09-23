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
		unsigned int		retinasperrow;
		unsigned int		mincritters;

		unsigned int		critter_maxlifetime;
		float			critter_maxenergy;
		unsigned int		critter_startenergy;
		unsigned int		critter_maxchildren;
		unsigned int		critter_maxbullets;
		unsigned int		critter_minenergyproc;
		unsigned int		critter_minenergyfire;
		float			critter_size;
		float			critter_speed;
		float			critter_sightrange;
		unsigned int		critter_retinasize;
		unsigned int		critter_colorneurons;
		unsigned int		critter_mutationrate;
		unsigned int		critter_maxmutations;
		unsigned int		critter_percentchangetype;
		bool			critter_flipnewborns;

		unsigned int		food_maxlifetime;
		float			food_maxenergy;
		float			food_size;

		unsigned int		corpse_maxlifetime;
		float			corpse_maxenergy;
		float			corpse_size;

		unsigned int		brain_maxneurons;
		unsigned int		brain_minsynapses;
		unsigned int		brain_maxsynapses;
		unsigned int		brain_minneuronsatbuildtime;
		unsigned int		brain_maxneuronsatbuildtime;
		unsigned int		brain_minsynapsesatbuildtime;
		bool			brain_mutate_minsynapsesatbuildtime;
		unsigned int		brain_maxsynapsesatbuildtime;
		bool			brain_mutate_maxsynapsesatbuildtime;
		unsigned int		brain_percentchanceinhibitoryneuron;
		bool			brain_mutate_percentchanceinhibitoryneuron;
		unsigned int		brain_percentchanceconsistentsynapses;
		bool			brain_mutate_percentchanceconsistentsynapses;

		unsigned int		brain_percentchanceinhibitorysynapses;
		bool			brain_mutate_percentchanceinhibitorysynapses;
		unsigned int		brain_percentchancemotorneuron;
		bool			brain_mutate_percentchancemotorneuron;
		unsigned int		brain_percentchanceplasticneuron;
		bool			brain_mutate_percentchanceplasticneuron;

		unsigned int		brain_minplasticitystrengthen;
		unsigned int		brain_maxplasticitystrengthen;
		unsigned int		brain_minplasticityweaken;
		unsigned int		brain_maxplasticityweaken;
		bool			brain_mutate_plasticityfactors;

		unsigned int		brain_percentchancesensorysynapse;
		bool			brain_mutate_percentchancesensorysynapse;
		unsigned int		brain_minfiringthreshold;
		bool			brain_mutate_minfiringthreshold;
		unsigned int		brain_maxfiringthreshold;
		bool			brain_mutate_maxfiringthreshold;
		unsigned int		brain_maxdendridicbranches;
		bool			brain_mutate_maxdendridicbranches;

		unsigned int		brain_percentmutateeffectaddneuron;
		unsigned int		brain_percentmutateeffectremoveneuron;
		unsigned int		brain_percentmutateeffectalterneuron;
		unsigned int		brain_percentmutateeffectaddsynapse;
		unsigned int		brain_percentmutateeffectremovesynapse;
		bool			brain_mutate_mutateeffects;



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

		void			printSettings();

		bool			spotIsFree(Vector3f &position, float osize, unsigned int exclude);

	private:

		RandGen			randgen;

		vector<Food*>		food;
		vector<Corpse*>		corpses;
		vector<Wall*>		walls;
		vector<Bullet*>		bullets;

		Dir			dirH;
		File			fileH;
		Parser			parseH;

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
