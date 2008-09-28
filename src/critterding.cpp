#include "gl/glwindow.h"
#include "scenes/evolution.h"

using namespace std;

// Global Settings
	unsigned int worldsize							= 25;
	unsigned int energy							= 500;
	unsigned int mincritters						= 10;
	unsigned int retinasperrow						= 20;
	unsigned int camerasensitivity						= 10;

// Critter Settings
	unsigned int critter_maxlifetime					= 2000;
	unsigned int critter_maxenergy						= 5000;
	unsigned int critter_startenergy					= 2500;
	unsigned int critter_maxchildren					= 100;
	unsigned int critter_maxbullets						= 200;
	unsigned int critter_minenergyproc					= 3000;
	unsigned int critter_minenergyfire					= 1;
	unsigned int critter_size						= 10;
	unsigned int critter_speed						= 50;
	unsigned int critter_sightrange						= 40;
	unsigned int critter_retinasize						= 7;
	unsigned int critter_colorneurons					= 3;
	unsigned int critter_mutationrate					= 8;
	unsigned int critter_maxmutations					= 3;
	unsigned int critter_percentchangetype					= 1;
	bool critter_flipnewborns						= false;

// Food Settings
	unsigned int food_maxlifetime						= 500;
	unsigned int food_maxenergy						= 1000;
	unsigned int food_size							= 15;

// Corpse Settings
	unsigned int corpse_maxlifetime						= 1000;
	unsigned int corpse_maxenergy						= 2500;
	unsigned int corpse_size						= 15;

// Brain Settings
	unsigned int brain_maxneurons						= 1000;
	unsigned int brain_minsynapses						= 1;
	unsigned int brain_maxsynapses						= 100;
	unsigned int brain_minneuronsatbuildtime				= 20;
	unsigned int brain_maxneuronsatbuildtime				= 30;

	unsigned int brain_minsynapsesatbuildtime				= 1;
		bool brain_mutate_minsynapsesatbuildtime			= false;

	unsigned int brain_maxsynapsesatbuildtime				= 60;
		bool brain_mutate_maxsynapsesatbuildtime			= false;

	unsigned int brain_percentchanceinhibitoryneuron			= 50;
		bool brain_mutate_percentchanceinhibitoryneuron			= false;

	unsigned int brain_percentchancemotorneuron				= 50;
		bool brain_mutate_percentchancemotorneuron			= false;

	unsigned int brain_percentchanceplasticneuron				= 20;
		bool brain_mutate_percentchanceplasticneuron			= false;

	unsigned int brain_minplasticitystrengthen				= 100;
	unsigned int brain_maxplasticitystrengthen				= 1000;
	unsigned int brain_minplasticityweaken					= 1000;
	unsigned int brain_maxplasticityweaken					= 10000;
		bool brain_mutate_plasticityfactors				= false;

	unsigned int brain_minfiringthreshold					= 2;
		bool brain_mutate_minfiringthreshold				= false;

	unsigned int brain_maxfiringthreshold					= 10;
		bool brain_mutate_maxfiringthreshold				= false;

	unsigned int brain_maxdendridicbranches					= 3;
		bool brain_mutate_maxdendridicbranches				= false;

	unsigned int brain_percentchanceconsistentsynapses			= 50;
		bool brain_mutate_percentchanceconsistentsynapses		= false;

	unsigned int brain_percentchanceinhibitorysynapses			= 50;
		bool brain_mutate_percentchanceinhibitorysynapses		= false;

	unsigned int brain_percentchancesensorysynapse				= 20;
		bool brain_mutate_percentchancesensorysynapse			= false;

	unsigned int brain_percentmutateeffectaddneuron				= 10;
	unsigned int brain_percentmutateeffectremoveneuron			= 10;
	unsigned int brain_percentmutateeffectalterneuron			= 20;
	unsigned int brain_percentmutateeffectaddsynapse			= 30;
	unsigned int brain_percentmutateeffectremovesynapse			= 30;
		bool brain_mutate_mutateeffects					= false;


bool checkSwitch(string matchsw, unsigned int &var, unsigned int min, unsigned int max, int optind, char *argv[])
{
	if ( matchsw == argv[optind] )
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
	else return false;
}


int main(int argc, char *argv[])
{
	std::stringstream helpinfo;

	helpinfo << "STARTUP OPTIONS" << endl << endl;
	helpinfo << "  option           [default value]" << endl << endl;
	helpinfo << "  Global Settings" << endl;
	helpinfo << "  --small                           Creates a 10x10 world with 200 energy" << endl;
	helpinfo << "  --medium                          Creates a 25x25 world with 500 energy (default)" << endl;
	helpinfo << "  --big                             Creates a 50x50 world with 2000 energy" << endl;
	helpinfo << "  --huge                            Creates a 100x100 world with 8000 energy" << endl;

	helpinfo << "  --worldsize                 [" << worldsize << "]  Creates a " << worldsize << "x" << worldsize << " world" << endl;
	helpinfo << "  --energy                   [" << energy << "]  Energy in the system: " << energy << "*food_energy(" << food_maxenergy << ") = " << energy*food_maxenergy << "" << endl;
	helpinfo << "  --mincritters               [" << mincritters << "]  If less than " << mincritters << " critters are present, insert an adam" << endl;
	helpinfo << "  --retinasperrow             [" << retinasperrow << "]  Place " << retinasperrow << " retinas on a row (bottom left of window)" << endl;
	helpinfo << "  --camerasensitivity         [" << camerasensitivity << "]  Camera sensitivity" << endl;
	helpinfo << endl;
	helpinfo << "  Critter Settings" << endl;
	helpinfo << "  --critter_maxlifetime     [" << critter_maxlifetime << "]  Max amount of frames a critter can live" << endl;
	helpinfo << "  --critter_maxenergy       [" << critter_maxenergy << "]  Max amount of energy in a critter" << endl;
	helpinfo << "  --critter_startenergy     [" << critter_startenergy << "]  Starting amount of energy for a new critter" << endl;
	helpinfo << "  --critter_maxchildren      [" << critter_maxchildren << "]  Max amount of children a critter can spawn" << endl;
	helpinfo << "  --critter_maxbullets       [" << critter_maxbullets << "]  Max amount of bullets a critter can fire" << endl;
	helpinfo << "  --critter_minenergyproc   [" << critter_minenergyproc << "]  Min amount of energy required for procreation" << endl;
	helpinfo << "  --critter_minenergyfire      [" << critter_minenergyfire << "]  Min amount of energy required for firing a bullet" << endl;
	helpinfo << "  --critter_size              [" << critter_size*100.0f << "]  Size of a critter" << endl;
	helpinfo << "  --critter_speed             [" << critter_speed*1000.0f << "]  Critter speed" << endl;
	helpinfo << "  --critter_sightrange        [" << critter_sightrange*10.0f << "]  Distance a critter can see (" << critter_sightrange*10.0f << " = " << critter_sightrange << " floor squares)" << endl;
	helpinfo << "  --critter_retinasize         [" << critter_retinasize << "]  Resolution of critter's retina: " << critter_retinasize << "x" << critter_retinasize << "" << endl;
	helpinfo << "  --critter_colorneurons       [" << critter_colorneurons << "]  Earch color of every pixel (RGBA) will get [" << critter_colorneurons << "] neurons (only for new adams)" << endl;
	helpinfo << "  --critter_mutationrate       [" << critter_mutationrate << "]  When a critter procreates there is a " << critter_mutationrate << "% chance it will mutate" << endl;
	helpinfo << "  --critter_maxmutations       [" << critter_maxmutations << "]  When a critter mutates, it can do " << critter_maxmutations << " mutations at maximum" << endl;
	helpinfo << "  --critter_percentchangetype  [" << critter_percentchangetype << "]  When a critter mutates, percent chance it changes type" << endl;
	helpinfo << "  --critter_flipnewborns            If set, newborns will be flipped 180 degrees" << endl;
	helpinfo << endl;
	helpinfo << "  Food Settings" << endl;
	helpinfo << "  --food_maxlifetime         [" << food_maxlifetime << "]  Maximum amount of frames food exists" << endl;
	helpinfo << "  --food_maxenergy          [" << food_maxenergy << "]  Maximum amount of energy in a food unit" << endl;
	helpinfo << "  --food_size                 [" << food_size*100.0f << "]  Size of a food unit" << endl;
	helpinfo << endl;
	helpinfo << "  Corpse Settings" << endl;
	helpinfo << "  --corpse_maxlifetime      [" << corpse_maxlifetime << "]  Maximum amount of frames a corpse exists" << endl;
	helpinfo << "  --corpse_maxenergy        [" << corpse_maxenergy << "]  Maximum amount of energy in a corpse unit" << endl;
	helpinfo << "  --corpse_size               [" << corpse_size*100.0f << "]  Size of a corpse unit" << endl;
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

	int optind=1;
	// decode arguments
	while ((optind < argc) && (argv[optind][0]=='-'))
	{
		string sw = argv[optind];

	// X Settings
		if (sw=="--small")
		{
			worldsize = 10;
			energy = 200;
	        }

		else if (sw=="--medium")
		{
			worldsize = 25;
			energy = 500;
	        }

		else if (sw=="--big")
		{
			worldsize = 50;
			energy = 2000;
	        }

		else if (sw=="--huge")
		{
			worldsize = 100;
			energy = 8000;
	        }

	// Global Settings

		else if ( checkSwitch("--worldsize", worldsize, 1, 5000, optind, argv) )
			optind++;

		else if ( checkSwitch("--energy", energy, 0, 1000000, optind, argv) )
			optind++;

		else if ( checkSwitch("--mincritters", mincritters, 0, 1000, optind, argv) )
			optind++;

		else if ( checkSwitch("--retinasperrow", retinasperrow, 1, 1000, optind, argv) )
			optind++;

		else if ( checkSwitch("--camerasensitivity", camerasensitivity, 1, 1000, optind, argv) )
			optind++;

	// Critter Settings

		else if ( checkSwitch("--critter_maxlifetime", critter_maxlifetime, 1, 1000000, optind, argv) )
			optind++;

		else if ( checkSwitch("--critter_maxenergy", critter_maxenergy, 1, 1000000, optind, argv) )
			optind++;

		else if ( checkSwitch("--critter_startenergy", critter_startenergy, 1, 1000000, optind, argv) )
			optind++;

		else if ( checkSwitch("--critter_maxchildren", critter_maxchildren, 1, 1000000, optind, argv) )
			optind++;

		else if ( checkSwitch("--critter_maxbullets", critter_maxbullets, 0, 1000000, optind, argv) )
			optind++;

		else if ( checkSwitch("--critter_minenergyproc", critter_minenergyproc, 0, 1000000, optind, argv) )
			optind++;

		else if ( checkSwitch("--critter_minenergyfire", critter_minenergyfire, 0, 1000000, optind, argv) )
			optind++;

		else if ( checkSwitch("--critter_size", critter_size, 1, 100, optind, argv) )
			optind++;

		else if ( checkSwitch("--critter_speed", critter_speed, 1, 1000, optind, argv) )
			optind++;

		else if ( checkSwitch("--critter_sightrange", critter_sightrange, 1, 1000, optind, argv) )
			optind++;

		else if ( checkSwitch("--critter_retinasize", critter_retinasize, 1, 1000, optind, argv) )
			optind++;

		else if ( checkSwitch("--critter_colorneurons", critter_colorneurons, 2, 100, optind, argv) )
			optind++;

		else if ( checkSwitch("--critter_mutationrate", critter_mutationrate, 0, 100, optind, argv) )
			optind++;

		else if ( checkSwitch("--critter_maxmutations", critter_maxmutations, 1, 100, optind, argv) )
			optind++;

		else if ( checkSwitch("--critter_percentchangetype", critter_percentchangetype, 0, 100, optind, argv) )
			optind++;

		else if (sw=="--critter_flipnewborns")
			critter_flipnewborns = true;

	// Food Settings

		else if ( checkSwitch("--food_maxlifetime", food_maxlifetime, 1, 1000000, optind, argv) )
			optind++;

		else if ( checkSwitch("--food_maxenergy", food_maxenergy, 1, 1000000, optind, argv) )
			optind++;

		else if ( checkSwitch("--food_size", food_size, 1, 100, optind, argv) )
			optind++;

	// Corpse Settings

		else if ( checkSwitch("--corpse_maxlifetime", corpse_maxlifetime, 0, 1000000, optind, argv) )
			optind++;

		else if ( checkSwitch("--corpse_maxenergy", corpse_maxenergy, 1, 1000000, optind, argv) )
			optind++;

		else if ( checkSwitch("--corpse_size", corpse_size, 1, 100, optind, argv) )
			optind++;

	// Brain Settings

		else if ( checkSwitch("--brain_maxneurons", brain_maxneurons, 1, 1000000, optind, argv) )
			optind++;

		else if ( checkSwitch("--brain_minsynapses", brain_minsynapses, 1, 1000000, optind, argv) )
			optind++;

		else if ( checkSwitch("--brain_maxsynapses", brain_maxsynapses, 1, 1000000, optind, argv) )
			optind++;

		else if ( checkSwitch("--brain_minneuronsatbuildtime", brain_minneuronsatbuildtime, 1, 1000000, optind, argv) )
			optind++;

		else if ( checkSwitch("--brain_maxneuronsatbuildtime", brain_maxneuronsatbuildtime, 1, 1000000, optind, argv) )
			optind++;

		else if ( checkSwitch("--brain_minsynapsesatbuildtime", brain_minsynapsesatbuildtime, 1, 1000000, optind, argv) )
			optind++;

		else if (sw=="--brain_mutate_minsynapsesatbuildtime")
			brain_mutate_minsynapsesatbuildtime = true;

		else if ( checkSwitch("--brain_maxsynapsesatbuildtime", brain_maxsynapsesatbuildtime, 1, 1000000, optind, argv) )
			optind++;

		else if (sw=="--brain_mutate_maxsynapsesatbuildtime")
			brain_mutate_maxsynapsesatbuildtime = true;

		else if ( checkSwitch("--brain_percentchanceinhibitoryneuron", brain_percentchanceinhibitoryneuron, 0, 100, optind, argv) )
			optind++;

		else if (sw=="--brain_mutate_percentchanceinhibitoryneuron")
			brain_mutate_percentchanceinhibitoryneuron = true;

		else if ( checkSwitch("--brain_percentchancemotorneuron", brain_percentchancemotorneuron, 0, 100, optind, argv) )
			optind++;

		else if (sw=="--brain_mutate_percentchancemotorneuron")
			brain_mutate_percentchancemotorneuron = true;

		else if ( checkSwitch("--brain_percentchanceplasticneuron", brain_percentchanceplasticneuron, 0, 100, optind, argv) )
			optind++;

		else if (sw=="--brain_mutate_percentchanceplasticneuron")
			brain_mutate_percentchanceplasticneuron = true;

		else if ( checkSwitch("--brain_minplasticitystrengthen", brain_minplasticitystrengthen, 1, 1000000, optind, argv) )
			optind++;

		else if ( checkSwitch("--brain_maxplasticitystrengthen", brain_maxplasticitystrengthen, 1, 1000000, optind, argv) )
			optind++;

		else if ( checkSwitch("--brain_minplasticityweaken", brain_minplasticityweaken, 1, 1000000, optind, argv) )
			optind++;

		else if ( checkSwitch("--brain_maxplasticityweaken", brain_maxplasticityweaken, 1, 1000000, optind, argv) )
			optind++;

		else if (sw=="--brain_mutate_plasticityfactors")
			brain_mutate_plasticityfactors = true;

		else if ( checkSwitch("--brain_minfiringthreshold", brain_minfiringthreshold, 1, 1000000, optind, argv) )
			optind++;

		else if (sw=="--brain_mutate_minfiringthreshold")
			brain_mutate_minfiringthreshold = true;

		else if ( checkSwitch("--brain_maxfiringthreshold", brain_maxfiringthreshold, 1, 1000000, optind, argv) )
			optind++;

		else if (sw=="--brain_mutate_maxfiringthreshold")
			brain_mutate_maxfiringthreshold = true;

		else if ( checkSwitch("--brain_maxdendridicbranches", brain_maxdendridicbranches, 1, 1000, optind, argv) )
			optind++;

		else if (sw=="--brain_mutate_maxdendridicbranches")
			brain_mutate_maxdendridicbranches = true;

		else if ( checkSwitch("--brain_percentchanceconsistentsynapses", brain_percentchanceconsistentsynapses, 0, 100, optind, argv) )
			optind++;

		else if (sw=="--brain_mutate_percentchanceconsistentsynapses")
			brain_mutate_percentchanceconsistentsynapses = true;

		else if ( checkSwitch("--brain_percentchanceinhibitorysynapses", brain_percentchanceinhibitorysynapses, 0, 100, optind, argv) )
			optind++;

		else if (sw=="--brain_mutate_percentchanceinhibitorysynapses")
			brain_mutate_percentchanceinhibitorysynapses = true;

		else if ( checkSwitch("--brain_percentchancesensorysynapse", brain_percentchancesensorysynapse, 0, 100, optind, argv) )
			optind++;

		else if (sw=="--brain_mutate_percentchancesensorysynapse")
			brain_mutate_percentchancesensorysynapse = true;

		else if ( checkSwitch("--brain_percentmutateeffectaddneuron", brain_percentmutateeffectaddneuron, 0, 100, optind, argv) )
			optind++;

		else if ( checkSwitch("--brain_percentmutateeffectremoveneuron", brain_percentmutateeffectremoveneuron, 0, 100, optind, argv) )
			optind++;

		else if ( checkSwitch("--brain_percentmutateeffectalterneuron", brain_percentmutateeffectalterneuron, 0, 100, optind, argv) )
			optind++;

		else if ( checkSwitch("--brain_percentmutateeffectaddsynapse", brain_percentmutateeffectaddsynapse, 0, 100, optind, argv) )
			optind++;

		else if ( checkSwitch("--brain_percentmutateeffectremovesynapse", brain_percentmutateeffectremovesynapse, 0, 100, optind, argv) )
			optind++;

		else if (sw=="--brain_mutate_mutateeffects")
			brain_mutate_mutateeffects = true;

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

	GLWindow glwindow;
	glwindow.create("Critterding beta7", 600, 600, 24, False);

		Evolution mainscene;

		mainscene.camera.position = Vector3f(-0.5f*worldsize, -1.1f*worldsize, -0.9f*worldsize);
		mainscene.camera.sensitivity = camerasensitivity;

		//mainscene.camera.position = cameraposition;

		// critter
		mainscene.world.critter_maxlifetime = critter_maxlifetime;
		mainscene.world.critter_maxenergy = critter_maxenergy;
		mainscene.world.critter_startenergy = critter_startenergy;
		mainscene.world.critter_minenergyproc = critter_minenergyproc;
		mainscene.world.critter_minenergyfire = critter_minenergyfire;
		mainscene.world.critter_maxchildren = critter_maxchildren;
		mainscene.world.critter_maxbullets = critter_maxbullets;
		mainscene.world.critter_size = (float)critter_size / 100.0f;
		mainscene.world.critter_speed = (float)critter_speed / 1000.0f;
		mainscene.world.critter_sightrange = (float)critter_sightrange / 10.0f;
		mainscene.world.critter_retinasize = critter_retinasize;
		mainscene.world.critter_colorneurons = critter_colorneurons;
		mainscene.world.critter_maxmutations = critter_maxmutations;
		mainscene.world.critter_mutationrate = critter_mutationrate;
		mainscene.world.critter_percentchangetype = critter_percentchangetype;
		mainscene.world.critter_flipnewborns = critter_flipnewborns;

		// food
		mainscene.world.food_maxlifetime = food_maxlifetime;
		mainscene.world.food_maxenergy = food_maxenergy;
		mainscene.world.food_size = (float)food_size / 100.0f;

		// corpse
		mainscene.world.corpse_maxlifetime = corpse_maxlifetime;
		mainscene.world.corpse_maxenergy = corpse_maxenergy;
		mainscene.world.corpse_size = (float)corpse_size / 100.0f;

		// brain
		mainscene.world.brain_maxneurons = brain_maxneurons;
		mainscene.world.brain_minsynapses = brain_minsynapses;
		mainscene.world.brain_maxsynapses = brain_maxsynapses;
		mainscene.world.brain_minneuronsatbuildtime = brain_minneuronsatbuildtime;
		mainscene.world.brain_maxneuronsatbuildtime = brain_maxneuronsatbuildtime;
		mainscene.world.brain_minsynapsesatbuildtime = brain_minsynapsesatbuildtime;
		mainscene.world.brain_mutate_minsynapsesatbuildtime = brain_mutate_minsynapsesatbuildtime;
		mainscene.world.brain_maxsynapsesatbuildtime = brain_maxsynapsesatbuildtime;
		mainscene.world.brain_mutate_maxsynapsesatbuildtime = brain_mutate_maxsynapsesatbuildtime;
		mainscene.world.brain_percentchanceinhibitoryneuron = brain_percentchanceinhibitoryneuron;
		mainscene.world.brain_mutate_percentchanceinhibitoryneuron = brain_mutate_percentchanceinhibitoryneuron;
		mainscene.world.brain_percentchanceconsistentsynapses = brain_percentchanceconsistentsynapses;
		mainscene.world.brain_mutate_percentchanceconsistentsynapses = brain_mutate_percentchanceconsistentsynapses;

		mainscene.world.brain_percentchanceinhibitorysynapses = brain_percentchanceinhibitorysynapses;
		mainscene.world.brain_mutate_percentchanceinhibitorysynapses = brain_mutate_percentchanceinhibitorysynapses;
		mainscene.world.brain_percentchancemotorneuron = brain_percentchancemotorneuron;
		mainscene.world.brain_mutate_percentchancemotorneuron = brain_mutate_percentchancemotorneuron;
		mainscene.world.brain_percentchanceplasticneuron = brain_percentchanceplasticneuron;
		mainscene.world.brain_mutate_percentchanceplasticneuron = brain_mutate_percentchanceplasticneuron;

		mainscene.world.brain_minplasticitystrengthen = brain_minplasticitystrengthen;
		mainscene.world.brain_maxplasticitystrengthen = brain_maxplasticitystrengthen;
		mainscene.world.brain_minplasticityweaken = brain_minplasticityweaken;
		mainscene.world.brain_maxplasticityweaken = brain_maxplasticityweaken;
		mainscene.world.brain_mutate_plasticityfactors = brain_mutate_plasticityfactors;

		mainscene.world.brain_percentchancesensorysynapse = brain_percentchancesensorysynapse;
		mainscene.world.brain_mutate_percentchancesensorysynapse = brain_mutate_percentchancesensorysynapse;
		mainscene.world.brain_minfiringthreshold = brain_minfiringthreshold;
		mainscene.world.brain_mutate_minfiringthreshold = brain_mutate_minfiringthreshold;
		mainscene.world.brain_maxfiringthreshold = brain_maxfiringthreshold;
		mainscene.world.brain_mutate_maxfiringthreshold = brain_mutate_maxfiringthreshold;
		mainscene.world.brain_maxdendridicbranches = brain_maxdendridicbranches;
		mainscene.world.brain_mutate_maxdendridicbranches = brain_mutate_maxdendridicbranches;

		mainscene.world.brain_percentmutateeffectaddneuron = brain_percentmutateeffectaddneuron;
		mainscene.world.brain_percentmutateeffectremoveneuron = brain_percentmutateeffectremoveneuron;
		mainscene.world.brain_percentmutateeffectalterneuron = brain_percentmutateeffectalterneuron;
		mainscene.world.brain_percentmutateeffectaddsynapse = brain_percentmutateeffectaddsynapse;
		mainscene.world.brain_percentmutateeffectremovesynapse = brain_percentmutateeffectremovesynapse;
		mainscene.world.brain_mutate_mutateeffects = brain_mutate_mutateeffects;

		// global
		mainscene.world.retinasperrow = retinasperrow;
		mainscene.world.resize(worldsize);
		mainscene.world.startfoodamount(energy);
		mainscene.world.setMincritters(mincritters);

		mainscene.world.printSettings();

		glwindow.runGLScene(mainscene);

	glwindow.destroy();
}
