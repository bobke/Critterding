#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <iostream>
#include <sstream>
#include "file.h"
#include "parser.h"
#include <GL/gl.h>

using namespace std;

class Settings
{
	public:
		static Settings* Instance();

		GLuint fontbase;
		string profileName;

		// info data
		unsigned int totalNeurons;
		unsigned int totalSynapses;

		unsigned int *winWidth;
		unsigned int *winHeight;

		unsigned int worldsize;
			unsigned int worldsizeMin;
			unsigned int worldsizeMax;
		unsigned int startenergy;
			unsigned int startenergyMin;
			unsigned int startenergyMax;
		unsigned int mincritters;
			unsigned int mincrittersMin;
			unsigned int mincrittersMax;
		unsigned int retinasperrow;
			unsigned int retinasperrowMin;
			unsigned int retinasperrowMax;
		unsigned int camerasensitivity;
			unsigned int camerasensitivityMin;
			unsigned int camerasensitivityMax;
		unsigned int walltype;
			unsigned int walltypeMin;
			unsigned int walltypeMax;
		bool exit_if_empty;
		bool autoload;
		bool noverbose;

		unsigned int critter_maxlifetime;
			unsigned int critter_maxlifetimeMin;
			unsigned int critter_maxlifetimeMax;
		unsigned int critter_maxenergy;
			unsigned int critter_maxenergyMin;
			unsigned int critter_maxenergyMax;
		unsigned int critter_startenergy;
			unsigned int critter_startenergyMin;
			unsigned int critter_startenergyMax;
		unsigned int critter_procinterval;
			unsigned int critter_procintervalMin;
			unsigned int critter_procintervalMax;
		unsigned int critter_fireinterval;
			unsigned int critter_fireintervalMin;
			unsigned int critter_fireintervalMax;
		unsigned int critter_minenergyproc;
			unsigned int critter_minenergyprocMin;
			unsigned int critter_minenergyprocMax;
		unsigned int critter_minenergyfire;
			unsigned int critter_minenergyfireMin;
			unsigned int critter_minenergyfireMax;
		unsigned int critter_firecost;
			unsigned int critter_firecostMin;
			unsigned int critter_firecostMax;
		unsigned int critter_sizeI;
			unsigned int critter_sizeIMin;
			unsigned int critter_sizeIMax;
		unsigned int critter_speedI;
			unsigned int critter_speedIMin;
			unsigned int critter_speedIMax;
		unsigned int critter_sightrangeI;
			unsigned int critter_sightrangeIMin;
			unsigned int critter_sightrangeIMax;
		unsigned int critter_retinasize;
			unsigned int critter_retinasizeMin;
			unsigned int critter_retinasizeMax;
		unsigned int critter_mutationrate;
			unsigned int critter_mutationrateMin;
			unsigned int critter_mutationrateMax;
		unsigned int critter_maxmutations;
			unsigned int critter_maxmutationsMin;
			unsigned int critter_maxmutationsMax;
		unsigned int critter_percentchangetype;
			unsigned int critter_percentchangetypeMin;
			unsigned int critter_percentchangetypeMax;
		bool critter_flipnewborns;
		bool critter_randomrotatenewborns;
		bool critter_enablecarrying;
		unsigned int critter_autosaveinterval;
			unsigned int critter_autosaveintervalMin;
			unsigned int critter_autosaveintervalMax;

		unsigned int food_maxlifetime;
			unsigned int food_maxlifetimeMin;
			unsigned int food_maxlifetimeMax;
		unsigned int food_maxenergy;
			unsigned int food_maxenergyMin;
			unsigned int food_maxenergyMax;
		unsigned int food_sizeI;
			unsigned int food_sizeIMin;
			unsigned int food_sizeIMax;

		unsigned int corpse_maxlifetime;
			unsigned int corpse_maxlifetimeMin;
			unsigned int corpse_maxlifetimeMax;
		unsigned int corpse_maxenergy;
			unsigned int corpse_maxenergyMin;
			unsigned int corpse_maxenergyMax;
		unsigned int corpse_sizeI;
			unsigned int corpse_sizeIMin;
			unsigned int corpse_sizeIMax;
		bool corpse_disable;

		unsigned int brain_maxneurons;
			unsigned int brain_maxneuronsMin;
			unsigned int brain_maxneuronsMax;
		unsigned int brain_minsynapses;
			unsigned int brain_minsynapsesMin;
			unsigned int brain_minsynapsesMax;
		unsigned int brain_maxsynapses;
			unsigned int brain_maxsynapsesMin;
			unsigned int brain_maxsynapsesMax;
		unsigned int brain_minneuronsatbuildtime;
			unsigned int brain_minneuronsatbuildtimeMin;
			unsigned int brain_minneuronsatbuildtimeMax;
		unsigned int brain_maxneuronsatbuildtime;
			unsigned int brain_maxneuronsatbuildtimeMin;
			unsigned int brain_maxneuronsatbuildtimeMax;

		unsigned int brain_minsynapsesatbuildtime;
			unsigned int brain_minsynapsesatbuildtimeMin;
			unsigned int brain_minsynapsesatbuildtimeMax;
			bool brain_mutate_minsynapsesatbuildtime;

		unsigned int brain_maxsynapsesatbuildtime;
			unsigned int brain_maxsynapsesatbuildtimeMin;
			unsigned int brain_maxsynapsesatbuildtimeMax;
			bool brain_mutate_maxsynapsesatbuildtime;

		unsigned int brain_percentchanceinhibitoryneuron;
			unsigned int brain_percentchanceinhibitoryneuronMin;
			unsigned int brain_percentchanceinhibitoryneuronMax;
			bool brain_mutate_percentchanceinhibitoryneuron;

		unsigned int brain_percentchancemotorneuron;
			unsigned int brain_percentchancemotorneuronMin;
			unsigned int brain_percentchancemotorneuronMax;
			bool brain_mutate_percentchancemotorneuron;

		unsigned int brain_percentchanceplasticneuron;
			unsigned int brain_percentchanceplasticneuronMin;
			unsigned int brain_percentchanceplasticneuronMax;
			bool brain_mutate_percentchanceplasticneuron;

		unsigned int brain_minplasticitystrengthen;
			unsigned int brain_minplasticitystrengthenMin;
			unsigned int brain_minplasticitystrengthenMax;
		unsigned int brain_maxplasticitystrengthen;
			unsigned int brain_maxplasticitystrengthenMin;
			unsigned int brain_maxplasticitystrengthenMax;
		unsigned int brain_minplasticityweaken;
			unsigned int brain_minplasticityweakenMin;
			unsigned int brain_minplasticityweakenMax;
		unsigned int brain_maxplasticityweaken;
			unsigned int brain_maxplasticityweakenMin;
			unsigned int brain_maxplasticityweakenMax;
			bool brain_mutate_plasticityfactors;

		unsigned int brain_minfiringthreshold;
			unsigned int brain_minfiringthresholdMin;
			unsigned int brain_minfiringthresholdMax;
			bool brain_mutate_minfiringthreshold;

		unsigned int brain_maxfiringthreshold;
			unsigned int brain_maxfiringthresholdMin;
			unsigned int brain_maxfiringthresholdMax;
			bool brain_mutate_maxfiringthreshold;

		unsigned int brain_maxdendridicbranches;
			unsigned int brain_maxdendridicbranchesMin;
			unsigned int brain_maxdendridicbranchesMax;
			bool brain_mutate_maxdendridicbranches;

		unsigned int brain_percentchanceconsistentsynapses;
			unsigned int brain_percentchanceconsistentsynapsesMin;
			unsigned int brain_percentchanceconsistentsynapsesMax;
			bool brain_mutate_percentchanceconsistentsynapses;

		unsigned int brain_percentchanceinhibitorysynapses;
			unsigned int brain_percentchanceinhibitorysynapsesMin;
			unsigned int brain_percentchanceinhibitorysynapsesMax;
			bool brain_mutate_percentchanceinhibitorysynapses;

		unsigned int brain_percentchancesensorysynapse;
			unsigned int brain_percentchancesensorysynapseMin;
			unsigned int brain_percentchancesensorysynapseMax;
			bool brain_mutate_percentchancesensorysynapse;

		unsigned int brain_percentmutateeffectaddneuron;
			unsigned int brain_percentmutateeffectaddneuronMin;
			unsigned int brain_percentmutateeffectaddneuronMax;
		unsigned int brain_percentmutateeffectremoveneuron;
			unsigned int brain_percentmutateeffectremoveneuronMin;
			unsigned int brain_percentmutateeffectremoveneuronMax;
		unsigned int brain_percentmutateeffectalterneuron;
			unsigned int brain_percentmutateeffectalterneuronMin;
			unsigned int brain_percentmutateeffectalterneuronMax;
		unsigned int brain_percentmutateeffectaddsynapse;
			unsigned int brain_percentmutateeffectaddsynapseMin;
			unsigned int brain_percentmutateeffectaddsynapseMax;
		unsigned int brain_percentmutateeffectremovesynapse;
			unsigned int brain_percentmutateeffectremovesynapseMin;
			unsigned int brain_percentmutateeffectremovesynapseMax;
		unsigned int brain_percentMutateEffectAlterMutable;
			unsigned int brain_percentMutateEffectAlterMutableMin;
			unsigned int brain_percentMutateEffectAlterMutableMax;

			bool brain_mutate_mutateeffects;

		unsigned int brain_costhavingneuron;
			unsigned int brain_costhavingneuronMin;
			unsigned int brain_costhavingneuronMax;
		unsigned int brain_costfiringneuron;
			unsigned int brain_costfiringneuronMin;
			unsigned int brain_costfiringneuronMax;
		unsigned int brain_costfiringmotorneuron;
			unsigned int brain_costfiringmotorneuronMin;
			unsigned int brain_costfiringmotorneuronMax;
		unsigned int brain_costhavingsynapse;
			unsigned int brain_costhavingsynapseMin;
			unsigned int brain_costhavingsynapseMax;

		// other vars
		float critter_size;
		float critter_speed;
		float critter_sightrange;
		float food_size;
		float corpse_size;

		float food_lifeenergyratio;
		float corpse_lifeenergyratio;

		float freeEnergyInfo;

		void doCommandLineOptions(int argc, char *argv[]);
		void loadProfile(char* filename);

		void printSettings();

	protected:
		Settings();
	private:
		File fileH;
		Parser			*parseH;

		stringstream helpinfo;
		void createHelpInfo();

		static Settings* _instance;
		bool checkSwitch(string matchsw, unsigned int &var, unsigned int min, unsigned int max, int optind, char *argv[]);
		bool checkConfigFileValue(string matchsw, unsigned int &var, unsigned int min, unsigned int max, string &line);
		bool checkConfigFileValue(string matchsw, bool &var, string &line);
};

#endif
