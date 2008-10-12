#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class Settings
{
	public:
		static Settings* Instance();

		unsigned int *winWidth;
		unsigned int *winHeight;

		unsigned int worldsize;
		unsigned int startenergy;
		unsigned int mincritters;
		unsigned int retinasperrow;
		unsigned int camerasensitivity;
		bool exit_if_empty;

		unsigned int critter_maxlifetime;
		unsigned int critter_maxenergy;
		unsigned int critter_startenergy;
		unsigned int critter_procinterval;
		unsigned int critter_fireinterval;
		unsigned int critter_minenergyproc;
		unsigned int critter_minenergyfire;
		unsigned int critter_sizeI;
		float critter_size;
		unsigned int critter_speedI;
		float critter_speed;
		unsigned int critter_sightrangeI;
		float critter_sightrange;
		unsigned int critter_retinasize;
		unsigned int critter_colorneurons;
		unsigned int critter_mutationrate;
		unsigned int critter_maxmutations;
		unsigned int critter_percentchangetype;
		bool critter_flipnewborns;
		bool critter_randomrotatenewborns;
		unsigned int critter_autosaveinterval;

		unsigned int food_maxlifetime;
		unsigned int food_maxenergy;
		unsigned int food_sizeI;
		float food_size;

		bool corpse_enable;
		unsigned int corpse_maxlifetime;
		unsigned int corpse_maxenergy;
		unsigned int corpse_sizeI;
		float corpse_size;

		float food_lifeenergyratio;
		float corpse_lifeenergyratio;

		unsigned int brain_maxneurons;
		unsigned int brain_minsynapses;
		unsigned int brain_maxsynapses;
		unsigned int brain_minneuronsatbuildtime;
		unsigned int brain_maxneuronsatbuildtime;

		unsigned int brain_minsynapsesatbuildtime;
			bool brain_mutate_minsynapsesatbuildtime;

		unsigned int brain_maxsynapsesatbuildtime;
			bool brain_mutate_maxsynapsesatbuildtime;

		unsigned int brain_percentchanceinhibitoryneuron;
			bool brain_mutate_percentchanceinhibitoryneuron;

		unsigned int brain_percentchancemotorneuron;
			bool brain_mutate_percentchancemotorneuron;

		unsigned int brain_percentchanceplasticneuron;
			bool brain_mutate_percentchanceplasticneuron;

		unsigned int brain_minplasticitystrengthen;
		unsigned int brain_maxplasticitystrengthen;
		unsigned int brain_minplasticityweaken;
		unsigned int brain_maxplasticityweaken;
			bool brain_mutate_plasticityfactors;

		unsigned int brain_minfiringthreshold;
			bool brain_mutate_minfiringthreshold;

		unsigned int brain_maxfiringthreshold;
			bool brain_mutate_maxfiringthreshold;

		unsigned int brain_maxdendridicbranches;
			bool brain_mutate_maxdendridicbranches;

		unsigned int brain_percentchanceconsistentsynapses;
			bool brain_mutate_percentchanceconsistentsynapses;

		unsigned int brain_percentchanceinhibitorysynapses;
			bool brain_mutate_percentchanceinhibitorysynapses;

		unsigned int brain_percentchancesensorysynapse;
			bool brain_mutate_percentchancesensorysynapse;

		unsigned int brain_percentmutateeffectaddneuron;
		unsigned int brain_percentmutateeffectremoveneuron;
		unsigned int brain_percentmutateeffectalterneuron;
		unsigned int brain_percentmutateeffectaddsynapse;
		unsigned int brain_percentmutateeffectremovesynapse;
			bool brain_mutate_mutateeffects;


		void doCommandLineOptions(int argc, char *argv[]);
		stringstream helpinfo;
		void createHelpInfo();

	protected:
		Settings();
	private:
		static Settings* _instance;

		bool checkSwitch(string matchsw, unsigned int &var, unsigned int min, unsigned int max, int optind, char *argv[]);
};

#endif
