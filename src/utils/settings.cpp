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
	critter_mutationrate		= 10;
	critter_maxmutations		= 10;
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

	food_lifeenergyratio		= 0;
	corpse_lifeenergyratio		= 0;

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

	createHelpInfo();
}

void Settings::createHelpInfo()
{
	helpinfo << "STARTUP OPTIONS" << endl << endl;
	helpinfo << "  option           [default value]" << endl << endl;
	helpinfo << "  Global Settings" << endl;
	helpinfo << "  --small                           Creates a 10x10 world with 200 energy" << endl;
	helpinfo << "  --medium                          Creates a 25x25 world with 500 energy (default)" << endl;
	helpinfo << "  --big                             Creates a 50x50 world with 2000 energy" << endl;
	helpinfo << "  --huge                            Creates a 100x100 world with 8000 energy" << endl;

	helpinfo << "  --worldsize                 [" << worldsize << "]  Creates a " << worldsize << "x" << worldsize << " world" << endl;
	helpinfo << "  --energy                   [" << startenergy << "]  Energy in the system: " << startenergy << "*food_energy(" << food_maxenergy << ") = " << startenergy*food_maxenergy << "" << endl;
	helpinfo << "  --mincritters               [" << mincritters << "]  If less than " << mincritters << " critters are present, insert an adam" << endl;
	helpinfo << "  --retinasperrow             [" << retinasperrow << "]  Place " << retinasperrow << " retinas on a row (bottom left of window)" << endl;
	helpinfo << "  --camerasensitivity         [" << camerasensitivity << "]  Camera sensitivity" << endl;
	helpinfo << "  --exit_if_empty                   If set, the program will exit when no critters exist" << endl;

	helpinfo << endl;
	helpinfo << "  Critter Settings" << endl;
	helpinfo << "  --critter_maxlifetime     [" << critter_maxlifetime << "]  Max amount of frames a critter can live" << endl;
	helpinfo << "  --critter_maxenergy       [" << critter_maxenergy << "]  Max amount of energy in a critter" << endl;
	helpinfo << "  --critter_startenergy     [" << critter_startenergy << "]  Starting amount of energy for a new critter" << endl;
	helpinfo << "  --critter_procinterval      [" << critter_procinterval << "]  Time (in frames) between procreations" << endl;
	helpinfo << "  --critter_fireinterval       [" << critter_fireinterval << "]  Time (in frames) between bullets being fired" << endl;
	helpinfo << "  --critter_minenergyproc   [" << critter_minenergyproc << "]  Min amount of energy required for procreation" << endl;
	helpinfo << "  --critter_minenergyfire      [" << critter_minenergyfire << "]  Min amount of energy required for firing a bullet" << endl;
	helpinfo << "  --critter_size              [" << critter_sizeI << "]  Size of a critter" << endl;
	helpinfo << "  --critter_speed             [" << critter_speedI << "]  Critter speed" << endl;
	helpinfo << "  --critter_sightrange        [" << critter_sightrangeI << "]  Distance a critter can see (" << critter_sightrangeI*10.0f << " = " << critter_sightrangeI << " floor squares)" << endl;
	helpinfo << "  --critter_retinasize         [" << critter_retinasize << "]  Resolution of critter's retina: " << critter_retinasize << "x" << critter_retinasize << "" << endl;
	helpinfo << "  --critter_colorneurons       [" << critter_colorneurons << "]  Earch color of every pixel (RGBA) will get [" << critter_colorneurons << "] neurons (only for new adams)" << endl;
	helpinfo << "  --critter_mutationrate       [" << critter_mutationrate << "]  When a critter procreates there is a " << critter_mutationrate << "% chance it will mutate" << endl;
	helpinfo << "  --critter_maxmutations       [" << critter_maxmutations << "]  When a critter mutates, it can do " << critter_maxmutations << " mutations at maximum" << endl;
	helpinfo << "  --critter_percentchangetype  [" << critter_percentchangetype << "]  When a critter mutates, percent chance it changes type" << endl;
	helpinfo << "  --critter_flipnewborns            If set, newborns will be flipped 180 degrees" << endl;
	helpinfo << "  --critter_randomrotatenewborns    If set, newborns will be rotated randomly" << endl;

	helpinfo << "  --critter_autosaveinterval   [" << critter_autosaveinterval << "]  Save all critters every N seconds (0=disabled)" << endl;
	helpinfo << endl;
	helpinfo << "  Food Settings" << endl;
	helpinfo << "  --food_maxlifetime         [" << food_maxlifetime << "]  Maximum amount of frames food exists" << endl;
	helpinfo << "  --food_maxenergy          [" << food_maxenergy << "]  Maximum amount of energy in a food unit" << endl;
	helpinfo << "  --food_size                 [" << food_sizeI << "]  Size of a food unit" << endl;
	helpinfo << endl;
	helpinfo << "  Corpse Settings" << endl;
	helpinfo << "  --corpse_enable                   Enable corpses (act as poison)" << endl;
	helpinfo << "  --corpse_maxlifetime      [" << corpse_maxlifetime << "]  Maximum amount of frames a corpse exists" << endl;
	helpinfo << "  --corpse_maxenergy        [" << corpse_maxenergy << "]  Maximum amount of energy in a corpse unit" << endl;
	helpinfo << "  --corpse_size               [" << corpse_sizeI << "]  Size of a corpse unit" << endl;
	helpinfo << endl;
	helpinfo << "  Brain Settings" << endl;
	helpinfo << "  --brain_maxneurons                           [" << brain_maxneurons << "]  Max neurons per critter" << endl;
	helpinfo << "  --brain_minsynapses                             [" << brain_minsynapses << "]  Min synapses per neuron" << endl;
	helpinfo << "  --brain_maxsynapses                           [" << brain_maxsynapses << "]  Max synapses per neuron" << endl;
	helpinfo << "  --brain_minneuronsatbuildtime                  [" << brain_minneuronsatbuildtime << "]  Min neurons for a new critter" << endl;
	helpinfo << "  --brain_maxneuronsatbuildtime                  [" << brain_maxneuronsatbuildtime << "]  Max neurons for a new critter" << endl;
	helpinfo << "  --brain_minsynapsesatbuildtime                  [" << brain_minsynapsesatbuildtime << "]  Min synapses when creating new neuron" << endl;
	helpinfo << "    --brain_mutate_minsynapsesatbuildtime              If set, the value above will mutate" << endl;
	helpinfo << "  --brain_maxsynapsesatbuildtime                 [" << brain_maxsynapsesatbuildtime << "]  Max synapses when creating new neuron" << endl;
	helpinfo << "    --brain_mutate_maxsynapsesatbuildtime              If set, the value above will mutate" << endl;
	helpinfo << "  --brain_percentchanceinhibitoryneuron          [" << brain_percentchanceinhibitoryneuron << "]  % chance neuron is inhibitory (vs exhibitory)" << endl;
	helpinfo << "    --brain_mutate_percentchanceinhibitoryneuron       If set, the value above will mutate" << endl;
	helpinfo << "  --brain_percentchancemotorneuron               [" << brain_percentchancemotorneuron << "]  % chance a neuron is a motor neuron, this value seems" << endl;
	helpinfo << "                                                       high, but when it tries to create a motor neuron that is" << endl;
	helpinfo << "                                                       is already taken, it will stay a normal neuron" << endl;
	helpinfo << "    --brain_mutate_percentchancemotorneuron            If set, the value above will mutate" << endl;
	helpinfo << "  --brain_percentchanceplasticneuron             [" << brain_percentchanceplasticneuron << "]  % chance a neuron applies synaptic plasticity" << endl;
	helpinfo << "    --brain_mutate_percentchanceplasticneuron          If set, the value above will mutate" << endl;
	helpinfo << "  --brain_minplasticitystrengthen               [" << brain_minplasticitystrengthen << "]  Min weight by which plastic synapses strengthen (1/" << brain_minplasticitystrengthen << ")" << endl;
	helpinfo << "  --brain_maxplasticitystrengthen              [" << brain_maxplasticitystrengthen << "]  Max weight by which plastic synapses strengthen (1/" << brain_maxplasticitystrengthen << ")" << endl;
	helpinfo << "  --brain_minplasticityweaken                  [" << brain_minplasticityweaken << "]  Min weight by which plastic synapses weaken (1/" << brain_minplasticityweaken << ")" << endl;
	helpinfo << "  --brain_maxplasticityweaken                 [" << brain_maxplasticityweaken << "]  Max weight by which plastic synapses weaken (1/" << brain_maxplasticityweaken << ")" << endl;
	helpinfo << "    --brain_mutate_plasticityfactors                   If set, all values above will mutate" << endl;
	helpinfo << "  --brain_minfiringthreshold                      [" << brain_minfiringthreshold << "]  Min firing threshold of a neuron" << endl;
	helpinfo << "    --brain_mutate_minfiringthreshold                  If set, the value above will mutate" << endl;
	helpinfo << "  --brain_maxfiringthreshold                     [" << brain_maxfiringthreshold << "]  Max firing threshold of a neuron" << endl;
	helpinfo << "    --brain_mutate_maxfiringthreshold                  If set, the value above will mutate" << endl;
	helpinfo << "  --brain_maxdendridicbranches                    [" << brain_maxdendridicbranches << "]  Max dendridic branches per neuron" << endl;
	helpinfo << "    --brain_mutate_maxdendridicbranches                If set, the value above will mutate" << endl;
	helpinfo << "  --brain_percentchanceconsistentsynapses        [" << brain_percentchanceconsistentsynapses << "]  % chance neuron has consistent synapses" << endl;
	helpinfo << "                                                       meaning all (new) synapses are inhibitory or exhibitory" << endl;
	helpinfo << "    --brain_mutate_percentchanceconsistentsynapses     If set, the value above will mutate" << endl;
	helpinfo << "  --brain_percentchanceinhibitorysynapses        [" << brain_percentchanceinhibitorysynapses << "]  % chance a synapse is inhibitory (vs exhibitory)" << endl;
	helpinfo << "    --brain_mutate_percentchanceinhibitorysynapses     If set, the value above will mutate" << endl;
	helpinfo << "  --brain_percentchancesensorysynapse            [" << brain_percentchancesensorysynapse << "]  % chance a synapse connects with a sensor (inputneuron)" << endl;
	helpinfo << "    --brain_mutate_percentchancesensorysynapse         If set, the value above will mutate" << endl;
	helpinfo << "  --brain_percentmutateeffectaddneuron           [" << brain_percentmutateeffectaddneuron << "]  % chance of adding a neuron for a mutationrun" << endl;
	helpinfo << "  --brain_percentmutateeffectremoveneuron        [" << brain_percentmutateeffectremoveneuron << "]  % chance of removing a neuron for a mutationrun" << endl;
	helpinfo << "  --brain_percentmutateeffectalterneuron         [" << brain_percentmutateeffectalterneuron << "]  % chance of altering a neuron for a mutationrun" << endl;
	helpinfo << "  --brain_percentmutateeffectaddsynapse          [" << brain_percentmutateeffectaddsynapse << "]  % chance of adding a synapse for a mutationrun" << endl;
	helpinfo << "  --brain_percentmutateeffectremovesynapse       [" << brain_percentmutateeffectremovesynapse << "]  % chance of removing a synapse for a mutationrun" << endl;
	helpinfo << "    --brain_mutate_mutateeffects                       If set, all values above will mutate" << endl;
}

void Settings::doCommandLineOptions(int argc, char *argv[])
{
	int optind=1;
	// decode arguments
	while ((optind < argc) && (argv[optind][0]=='-'))
	{
		string sw = argv[optind];

	// Global Settings

		if (sw=="--small")
		{
			worldsize = 10;
			startenergy = 200;
	        }

		else if (sw=="--medium")
		{
			worldsize = 25;
			startenergy = 500;
	        }

		else if (sw=="--big")
		{
			worldsize = 50;
			startenergy = 2000;
	        }

		else if (sw=="--huge")
		{
			worldsize = 100;
			startenergy = 8000;
	        }

		else if ( checkSwitch("--worldsize", worldsize, 1, 5000, optind, argv) ) optind++;
		else if ( checkSwitch("--energy", startenergy, 0, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--mincritters", mincritters, 0, 1000, optind, argv) ) optind++;
		else if ( checkSwitch("--retinasperrow", retinasperrow, 1, 1000, optind, argv) ) optind++;
		else if ( checkSwitch("--camerasensitivity", camerasensitivity, 1, 1000, optind, argv) ) optind++;
		else if ( sw=="--exit-if-empty") exit_if_empty = true;

	// Critter Settings

		else if ( checkSwitch("--critter_maxlifetime", critter_maxlifetime, 1, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_maxenergy", critter_maxenergy, 1, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_startenergy", critter_startenergy, 1, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_procinterval", critter_procinterval, 1, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_fireinterval", critter_fireinterval, 0, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_minenergyproc", critter_minenergyproc, 0, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_minenergyfire", critter_minenergyfire, 0, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_size", critter_sizeI, 1, 100, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_speed", critter_speedI, 1, 1000, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_sightrange", critter_sightrangeI, 1, 1000, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_retinasize", critter_retinasize, 1, 1000, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_colorneurons", critter_colorneurons, 2, 100, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_mutationrate", critter_mutationrate, 0, 100, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_maxmutations", critter_maxmutations, 1, 100, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_percentchangetype", critter_percentchangetype, 0, 100, optind, argv) ) optind++;
		else if (sw=="--critter_flipnewborns") critter_flipnewborns = true;
		else if (sw=="--critter_randomrotatenewborns") critter_randomrotatenewborns = true;
		else if ( checkSwitch("--critter_autosaveinterval", critter_autosaveinterval, 1, 1000000, optind, argv) ) optind++;

	// Food Settings

		else if ( checkSwitch("--food_maxlifetime", food_maxlifetime, 1, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--food_maxenergy", food_maxenergy, 1, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--food_size", food_sizeI, 1, 100, optind, argv) ) optind++;

	// Corpse Settings

		else if (sw=="--corpse_enable") corpse_enable = true;
		else if ( checkSwitch("--corpse_maxlifetime", corpse_maxlifetime, 1, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--corpse_maxenergy", corpse_maxenergy, 1, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--corpse_size", corpse_sizeI, 1, 100, optind, argv) ) optind++;

	// Brain Settings

		else if ( checkSwitch("--brain_maxneurons", brain_maxneurons, 1, 1000000, optind, argv) ) optind++;

		else if ( checkSwitch("--brain_minsynapses", brain_minsynapses, 1, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--brain_maxsynapses", brain_maxsynapses, 1, 1000000, optind, argv) ) optind++;

		else if ( checkSwitch("--brain_minneuronsatbuildtime", brain_minneuronsatbuildtime, 1, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--brain_maxneuronsatbuildtime", brain_maxneuronsatbuildtime, 1, 1000000, optind, argv) ) optind++;

		else if ( checkSwitch("--brain_minsynapsesatbuildtime", brain_minsynapsesatbuildtime, 1, 1000000, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_minsynapsesatbuildtime") brain_mutate_minsynapsesatbuildtime = true;

		else if ( checkSwitch("--brain_maxsynapsesatbuildtime", brain_maxsynapsesatbuildtime, 1, 1000000, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_maxsynapsesatbuildtime") brain_mutate_maxsynapsesatbuildtime = true;

		else if ( checkSwitch("--brain_percentchanceinhibitoryneuron", brain_percentchanceinhibitoryneuron, 0, 100, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_percentchanceinhibitoryneuron") brain_mutate_percentchanceinhibitoryneuron = true;

		else if ( checkSwitch("--brain_percentchancemotorneuron", brain_percentchancemotorneuron, 0, 100, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_percentchancemotorneuron") brain_mutate_percentchancemotorneuron = true;

		else if ( checkSwitch("--brain_percentchanceplasticneuron", brain_percentchanceplasticneuron, 0, 100, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_percentchanceplasticneuron") brain_mutate_percentchanceplasticneuron = true;

		else if ( checkSwitch("--brain_minplasticitystrengthen", brain_minplasticitystrengthen, 1, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--brain_maxplasticitystrengthen", brain_maxplasticitystrengthen, 1, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--brain_minplasticityweaken", brain_minplasticityweaken, 1, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--brain_maxplasticityweaken", brain_maxplasticityweaken, 1, 1000000, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_plasticityfactors") brain_mutate_plasticityfactors = true;

		else if ( checkSwitch("--brain_minfiringthreshold", brain_minfiringthreshold, 1, 1000000, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_minfiringthreshold") brain_mutate_minfiringthreshold = true;

		else if ( checkSwitch("--brain_maxfiringthreshold", brain_maxfiringthreshold, 1, 1000000, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_maxfiringthreshold") brain_mutate_maxfiringthreshold = true;

		else if ( checkSwitch("--brain_maxdendridicbranches", brain_maxdendridicbranches, 1, 1000, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_maxdendridicbranches") brain_mutate_maxdendridicbranches = true;

		else if ( checkSwitch("--brain_percentchanceconsistentsynapses", brain_percentchanceconsistentsynapses, 0, 100, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_percentchanceconsistentsynapses") brain_mutate_percentchanceconsistentsynapses = true;

		else if ( checkSwitch("--brain_percentchanceinhibitorysynapses", brain_percentchanceinhibitorysynapses, 0, 100, optind, argv) ) optind++;

		else if (sw=="--brain_mutate_percentchanceinhibitorysynapses") brain_mutate_percentchanceinhibitorysynapses = true;

		else if ( checkSwitch("--brain_percentchancesensorysynapse", brain_percentchancesensorysynapse, 0, 100, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_percentchancesensorysynapse") brain_mutate_percentchancesensorysynapse = true;

		else if ( checkSwitch("--brain_percentmutateeffectaddneuron", brain_percentmutateeffectaddneuron, 0, 100, optind, argv) ) optind++;
		else if ( checkSwitch("--brain_percentmutateeffectremoveneuron", brain_percentmutateeffectremoveneuron, 0, 100, optind, argv) ) optind++;
		else if ( checkSwitch("--brain_percentmutateeffectalterneuron", brain_percentmutateeffectalterneuron, 0, 100, optind, argv) ) optind++;
		else if ( checkSwitch("--brain_percentmutateeffectaddsynapse", brain_percentmutateeffectaddsynapse, 0, 100, optind, argv) ) optind++;
		else if ( checkSwitch("--brain_percentmutateeffectremovesynapse", brain_percentmutateeffectremovesynapse, 0, 100, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_mutateeffects") brain_mutate_mutateeffects = true;

		else if (sw=="--help")
		{
			cout << helpinfo.str() << endl;
			exit(1);
	        }

		else
		{
			cout << "Unknown switch: " << argv[optind] << endl;
			cout << "use --help for more information" << endl;
			exit(1);
		}
		optind++;
	}

	if (optind<argc)
	{
		cout << "Unknown switch: " << argv[optind] << endl;
		cout << "use --help for more information" << endl;
		exit(1);
	}
	cout << endl << endl;

}


bool Settings::checkSwitch(string matchsw, unsigned int &var, unsigned int min, unsigned int max, int optind, char *argv[])
{
	if ( matchsw == argv[optind] )
	{
		if ( argv[optind+1] )
		{
			unsigned int value = atoi(argv[optind+1]);
			if ( value >= min && value <= max )
			{
				var = value;
				return true;
			}
			else
			{
				cerr << matchsw << " expects a value that is >=" << min << " and <=" << max << endl;
				exit(1);
			}
		}
		else
		{
			cerr << matchsw << " expects a value that is >=" << min << " and <=" << max << endl;
			exit(1);
		}
	}
	else return false;
}

