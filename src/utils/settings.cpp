#include "settings.h"

Settings* Settings::Instance () 
{
	static Settings t;
	return &t;
}

Settings::Settings()
{
	worldsize			= 25;
	startenergy			= 500;
	mincritters			= 10;
	retinasperrow			= 20;
	camerasensitivity		= 10;
	exit_if_empty			= false;

	critter_maxlifetime		= 2000;
	critter_maxenergy		= 5000;
	critter_startenergy		= 2500;
	critter_procinterval		= 20;
	critter_fireinterval		= 10;
	critter_minenergyproc		= 3000;
	critter_minenergyfire		= 1;
	critter_sizeI			= 10;
	critter_speedI			= 50;
	critter_sightrangeI		= 40;
	critter_retinasize		= 7;
	critter_colorneurons		= 3;
	critter_mutationrate		= 8;
	critter_maxmutations		= 3;
	critter_percentchangetype	= 0;
	critter_flipnewborns		= false;
	critter_randomrotatenewborns	= false;
	critter_autosaveinterval	= 0;

	food_maxlifetime		= 500;
	food_maxenergy			= 1000;
	food_sizeI			= 15;

	corpse_enable			= false;
	corpse_maxlifetime		= 1000;
	corpse_maxenergy		= 2500;
	corpse_sizeI			= 15;

	brain_maxneurons		= 1000;
	brain_minsynapses		= 1;
	brain_maxsynapses		= 100;
	brain_minneuronsatbuildtime	= 20;
	brain_maxneuronsatbuildtime	= 30;

	brain_minsynapsesatbuildtime			= 1;
		brain_mutate_minsynapsesatbuildtime		= false;

	brain_maxsynapsesatbuildtime			= 60;
		brain_mutate_maxsynapsesatbuildtime		= false;

	brain_percentchanceinhibitoryneuron		= 50;
		brain_mutate_percentchanceinhibitoryneuron	= false;

	brain_percentchancemotorneuron			= 50;
		brain_mutate_percentchancemotorneuron		= false;

	brain_percentchanceplasticneuron		= 20;
		brain_mutate_percentchanceplasticneuron		= false;

	brain_minplasticitystrengthen			= 100;
	brain_maxplasticitystrengthen			= 1000;
	brain_minplasticityweaken			= 1000;
	brain_maxplasticityweaken			= 10000;
/*	brain_percentchanceplasticneuron		= 50;
		brain_mutate_percentchanceplasticneuron		= false;

	brain_minplasticitystrengthen			= 100;
	brain_maxplasticitystrengthen			= 100000;
	brain_minplasticityweaken			= 100;
	brain_maxplasticityweaken			= 100000;*/
		brain_mutate_plasticityfactors			= false;

	brain_minfiringthreshold			= 2;
		brain_mutate_minfiringthreshold			= false;

	brain_maxfiringthreshold			= 10;
		brain_mutate_maxfiringthreshold			= false;

	brain_maxdendridicbranches			= 3;
		brain_mutate_maxdendridicbranches		= false;

	brain_percentchanceconsistentsynapses		= 50;
		brain_mutate_percentchanceconsistentsynapses	= false;

	brain_percentchanceinhibitorysynapses		= 50;
		brain_mutate_percentchanceinhibitorysynapses	= false;

	brain_percentchancesensorysynapse		= 20;
		brain_mutate_percentchancesensorysynapse	= false;

	brain_percentmutateeffectaddneuron		= 10;
	brain_percentmutateeffectremoveneuron		= 10;
	brain_percentmutateeffectalterneuron		= 20;
	brain_percentmutateeffectaddsynapse		= 30;
	brain_percentmutateeffectremovesynapse		= 30;
		brain_mutate_mutateeffects			= false;


}

