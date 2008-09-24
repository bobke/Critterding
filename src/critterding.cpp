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
	float        critter_size						= 0.1f;
	float        critter_speed						= 0.05f;
	float        critter_sightrange						= 3.0f;
	unsigned int critter_retinasize						= 7;
	unsigned int critter_colorneurons					= 3;
	unsigned int critter_mutationrate					= 8;
	unsigned int critter_maxmutations					= 3;
	unsigned int critter_percentchangetype					= 1;
	bool critter_flipnewborns						= false;

// Food Settings
	unsigned int food_maxlifetime						= 500;
	unsigned int food_maxenergy						= 1000;
	float        food_size							= 0.15f;

// Corpse Settings
	unsigned int corpse_maxlifetime						= 1000;
	unsigned int corpse_maxenergy						= 2500;
	float        corpse_size						= 0.15f;

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
		else if (sw=="--worldsize")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 1 && value <= 5000 )
				worldsize = value;
			else { cerr << "worldsize must match >=1 and <=5000" << endl; exit(1); }
	        }
		else if (sw=="--energy")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 0 && value <= 1000000 )
				energy = value;
			else { cerr << "energy must match >=0 and <=1000000" << endl; exit(1); }
	        }
		else if (sw=="--mincritters")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 0 && value <= 1000 )
				mincritters = value;
			else { cerr << "mincritters must match >=0 and <=1000" << endl; exit(1); }
	        }
		else if (sw=="--retinasperrow")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 1 && value <= 1000 )
				retinasperrow = value;
			else { cerr << "retinasperrow must match >=1 and <=1000" << endl; exit(1); }
	        }
		else if (sw=="--camerasensitivity")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 1 && value <= 1000 )
				camerasensitivity = value;
			else { cerr << "camerasensitivity must match >=1 and <=1000" << endl; exit(1); }
	        }
	// Critter Settings
		else if (sw=="--critter_maxlifetime")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 1 && value <= 1000000 )
				critter_maxlifetime = value;
			else { cerr << "critter_maxlifetime must match >=1 and <=1000000" << endl; exit(1); }
	        }
		else if (sw=="--critter_maxenergy")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 1 && value <= 1000000 )
				critter_maxenergy = value;
			else { cerr << "critter_maxenergy must match >=1 and <=1000000" << endl; exit(1); }
	        }
		else if (sw=="--critter_startenergy")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 1 && value <= 1000000 )
				critter_startenergy = value;
			else { cerr << "critter_startenergy must match >=1 and <=1000000" << endl; exit(1); }
	        }
		else if (sw=="--critter_maxchildren")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 1 && value <= 1000000 )
				critter_maxchildren = value;
			else { cerr << "critter_maxchildren must match >=1 and <=1000000" << endl; exit(1); }
	        }
		else if (sw=="--critter_maxbullets")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 0 && value <= 1000000 )
				critter_maxbullets = value;
			else { cerr << "critter_maxbullets must match >=0 and <=1000000" << endl; exit(1); }
	        }
		else if (sw=="--critter_minenergyproc")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 0 && value <= 1000000 )
				critter_minenergyproc = value;
			else { cerr << "critter_minenergyproc must match >=0 and <=1000000" << endl; exit(1); }
	        }
		else if (sw=="--critter_minenergyfire")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 0 && value <= 1000000 )
				critter_minenergyfire = value;
			else { cerr << "critter_minenergyfire must match >=0 and <=1000000" << endl; exit(1); }
	        }
		else if (sw=="--critter_size")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 1 && value <= 100 )
				critter_size = (float)value / 100.0f;
			else { cerr << "critter_size must match >=1 and <=100" << endl; exit(1); }
	        }
		else if (sw=="--critter_speed")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 1 && value <= 1000 )
				critter_speed = (float)value / 1000.0f;
			else { cerr << "critter_speed must match >=1 and <=1000" << endl; exit(1); }
	        }
		else if (sw=="--critter_sightrange")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 1 && value <= 1000 )
				critter_sightrange = (float)value / 10.0f;
			else { cerr << "critter_sightrange must match >=1 and <=1000" << endl; exit(1); }
	        }
		else if (sw=="--critter_retinasize")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 1 && value <= 100 )
				critter_retinasize = value;
			else { cerr << "critter_retinasize must match >=1 and <=100" << endl; exit(1); }
	        }
		else if (sw=="--critter_colorneurons")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 2 && value <= 100 )
				critter_colorneurons = value;
			else { cerr << "critter_colorneurons must match >=2 and <=100" << endl; exit(1); }
	        }
		else if (sw=="--critter_mutationrate")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 0 && value <= 100 )
				critter_mutationrate = value;
			else { cerr << "critter_mutationrate must match >=0 and <=100" << endl; exit(1); }
	        }
		else if (sw=="--critter_maxmutations")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 1 && value <= 100 )
				critter_maxmutations = value;
			else { cerr << "critter_maxmutations must match >=1 and <=100" << endl; exit(1); }
	        }
		else if (sw=="--critter_percentchangetype")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 0 && value <= 100 )
				critter_percentchangetype = value;
			else { cerr << "critter_percentchangetype must match >=0 and <=100" << endl; exit(1); }
	        }
		else if (sw=="--critter_flipnewborns")
		{
			critter_flipnewborns = true;
	        }

	// Food Settings
		else if (sw=="--food_maxlifetime")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 1 && value <= 1000000 )
				food_maxlifetime = value;
			else { cerr << "food_maxlifetime must match >=1 and <=1000000" << endl; exit(1); }
	        }
		else if (sw=="--food_maxenergy")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 1 && value <= 1000000 )
				food_maxenergy = value;
			else { cerr << "food_maxenergy must match >=1 and <=1000000" << endl; exit(1); }
	        }
		else if (sw=="--food_size")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 1 && value <= 100 )
				food_size = (float)value / 100.0f;
			else { cerr << "food_size must match >=1 and <=100" << endl; exit(1); }
	        }

	// Corpse Settings
		else if (sw=="--corpse_maxlifetime")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 0 && value <= 1000000 )
				corpse_maxlifetime = value;
			else { cerr << "corpse_maxlifetime must match >=0 and <=1000000" << endl; exit(1); }
	        }
		else if (sw=="--corpse_maxenergy")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 1 && value <= 1000000 )
				corpse_maxenergy = value;
			else { cerr << "corpse_maxenergy must match >=1 and <=1000000" << endl; exit(1); }
	        }
		else if (sw=="--corpse_size")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 1 && value <= 100 )
				corpse_size = (float)value / 100.0f;
			else { cerr << "corpse_size must match >=1 and <=100" << endl; exit(1); }
	        }

	// Brain Settings
		else if (sw=="--brain_maxneurons")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 1 && value <= 1000000 )
				brain_maxneurons = value;
			else { cerr << "brain_maxneurons must match >=1 and <=1000000" << endl; exit(1); }
	        }
		else if (sw=="--brain_minsynapses")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >=1  && value <= 1000000 )
				brain_minsynapses = value;
			else { cerr << "brain_minsynapses must match >=1 and <=1000000" << endl; exit(1); }
	        }
		else if (sw=="--brain_maxsynapses")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >=1  && value <= 1000000 )
				brain_maxsynapses = value;
			else { cerr << "brain_maxsynapses must match >=1 and <=1000000" << endl; exit(1); }
	        }
		else if (sw=="--brain_minneuronsatbuildtime")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >=1  && value <= 1000000 )
				brain_minneuronsatbuildtime = value;
			else { cerr << "brain_minneuronsatbuildtime must match >=1 and <=1000000" << endl; exit(1); }
	        }
		else if (sw=="--brain_maxneuronsatbuildtime")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >=1  && value <= 1000000 )
				brain_maxneuronsatbuildtime = value;
			else { cerr << "brain_maxneuronsatbuildtime must match >=1 and <=1000000" << endl; exit(1); }
	        }
		else if (sw=="--brain_minsynapsesatbuildtime")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >=1  && value <= 1000000 )
				brain_minsynapsesatbuildtime = value;
			else { cerr << "brain_minsynapsesatbuildtime must match >=1 and <=1000000" << endl; exit(1); }
	        }
		else if (sw=="--brain_mutate_minsynapsesatbuildtime")
		{
			brain_mutate_minsynapsesatbuildtime = true;
	        }

		else if (sw=="--brain_maxsynapsesatbuildtime")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >=1  && value <= 1000000 )
				brain_maxsynapsesatbuildtime = value;
			else { cerr << "brain_maxsynapsesatbuildtime must match >=1 and <=1000000" << endl; exit(1); }
	        }
		else if (sw=="--brain_mutate_maxsynapsesatbuildtime")
		{
			brain_mutate_maxsynapsesatbuildtime = true;
	        }
		else if (sw=="--brain_percentchanceinhibitoryneuron")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >=0  && value <= 100 )
				brain_percentchanceinhibitoryneuron = value;
			else { cerr << "brain_percentchanceinhibitoryneuron must match >=0 and <=100" << endl; exit(1); }
	        }
		else if (sw=="--brain_mutate_percentchanceinhibitoryneuron")
		{
			brain_mutate_percentchanceinhibitoryneuron = true;
	        }
		else if (sw=="--brain_percentchancemotorneuron")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >=0  && value <= 100 )
				brain_percentchancemotorneuron = value;
			else { cerr << "brain_percentchancemotorneuron must match >=0 and <=100" << endl; exit(1); }
	        }
		else if (sw=="--brain_mutate_percentchancemotorneuron")
		{
			brain_mutate_percentchancemotorneuron = true;
	        }
		else if (sw=="--brain_percentchanceplasticneuron")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >=0  && value <= 100 )
				brain_percentchanceplasticneuron = value;
			else { cerr << "brain_percentchanceplasticneuron must match >=0 and <=100" << endl; exit(1); }
	        }
		else if (sw=="--brain_mutate_percentchanceplasticneuron")
		{
			brain_mutate_percentchanceplasticneuron = true;
	        }

		else if (sw=="--brain_minplasticitystrengthen")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >=1  && value <= 1000000 )
				brain_minplasticitystrengthen = value;
			else { cerr << "brain_minplasticitystrengthen must match >=1 and <=1000000" << endl; exit(1); }
	        }
		else if (sw=="--brain_maxplasticitystrengthen")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 1 && value <= 1000000 )
				brain_maxplasticitystrengthen = value;
			else { cerr << "brain_maxplasticitystrengthen must match >=1 and <=1000000" << endl; exit(1); }
	        }
		else if (sw=="--brain_minplasticityweaken")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 1 && value <= 1000000 )
				brain_minplasticityweaken = value;
			else { cerr << "brain_minplasticityweaken must match >=1 and <=1000000" << endl; exit(1); }
	        }
		else if (sw=="--brain_maxplasticityweaken")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 1 && value <= 1000000 )
				brain_maxplasticityweaken = value;
			else { cerr << "brain_maxplasticityweaken must match >=1 and <=1000000" << endl; exit(1); }
	        }
		else if (sw=="--brain_mutate_plasticityfactors")
		{
			brain_mutate_plasticityfactors = true;
	        }
		else if (sw=="--brain_minfiringthreshold")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 1 && value <= 1000000 )
				brain_minfiringthreshold = value;
			else { cerr << "brain_minfiringthreshold must match >=1 and <=1000000" << endl; exit(1); }
	        }
		else if (sw=="--brain_mutate_minfiringthreshold")
		{
			brain_mutate_minfiringthreshold = true;
	        }
		else if (sw=="--brain_maxfiringthreshold")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 1 && value <= 1000000 )
				brain_maxfiringthreshold = value;
			else { cerr << "brain_maxfiringthreshold must match >=1 and <=1000000" << endl; exit(1); }
	        }
		else if (sw=="--brain_mutate_maxfiringthreshold")
		{
			brain_mutate_maxfiringthreshold = true;
	        }
		else if (sw=="--brain_maxdendridicbranches")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 1 && value <= 1000 )
				brain_maxdendridicbranches = value;
			else { cerr << "brain_maxdendridicbranches must match >=1 and <=1000" << endl; exit(1); }
	        }
		else if (sw=="--brain_mutate_maxdendridicbranches")
		{
			brain_mutate_maxdendridicbranches = true;
	        }
		else if (sw=="--brain_percentchanceconsistentsynapses")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 0 && value <= 100 )
				brain_percentchanceconsistentsynapses = value;
			else { cerr << "brain_percentchanceconsistentsynapses must match >=0 and <=100" << endl; exit(1); }
	        }
		else if (sw=="--brain_mutate_percentchanceconsistentsynapses")
		{
			brain_mutate_percentchanceconsistentsynapses = true;
	        }
		else if (sw=="--brain_percentchanceinhibitorysynapses")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 0 && value <= 100 )
				brain_percentchanceinhibitorysynapses = value;
			else { cerr << "brain_percentchanceinhibitorysynapses must match >=0 and <=100" << endl; exit(1); }
	        }
		else if (sw=="--brain_mutate_percentchanceinhibitorysynapses")
		{
			brain_mutate_percentchanceinhibitorysynapses = true;
	        }
		else if (sw=="--brain_percentchancesensorysynapse")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 0 && value <= 100 )
				brain_percentchancesensorysynapse = value;
			else { cerr << "brain_percentchancesensorysynapse must match >=0 and <=100" << endl; exit(1); }
	        }
		else if (sw=="--brain_mutate_percentchancesensorysynapse")
		{
			brain_mutate_percentchancesensorysynapse = true;
	        }
		else if (sw=="--brain_percentmutateeffectaddneuron")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 0 && value <= 100 )
				brain_percentmutateeffectaddneuron = value;
			else { cerr << "brain_percentmutateeffectaddneuron must match >=0 and <=100" << endl; exit(1); }
	        }
		else if (sw=="--brain_percentmutateeffectremoveneuron")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 0 && value <= 100 )
				brain_percentmutateeffectremoveneuron = value;
			else { cerr << "brain_percentmutateeffectremoveneuron must match >=0 and <=100" << endl; exit(1); }
	        }
		else if (sw=="--brain_percentmutateeffectalterneuron")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 0 && value <= 100 )
				brain_percentmutateeffectalterneuron = value;
			else { cerr << "brain_percentmutateeffectalterneuron must match >=0 and <=100" << endl; exit(1); }
	        }
		else if (sw=="--brain_percentmutateeffectaddsynapse")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 0 && value <= 100 )
				brain_percentmutateeffectaddsynapse = value;
			else { cerr << "brain_percentmutateeffectaddsynapse must match >=0 and <=100" << endl; exit(1); }
	        }
		else if (sw=="--brain_percentmutateeffectremovesynapse")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 0 && value <= 100 )
				brain_percentmutateeffectremovesynapse = value;
			else { cerr << "brain_percentmutateeffectremovesynapse must match >=0 and <=100" << endl; exit(1); }
	        }
		else if (sw=="--brain_mutate_mutateeffects")
		{
			brain_mutate_mutateeffects = true;
	        }

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
		mainscene.world.critter_size = critter_size;
		mainscene.world.critter_speed = critter_speed;
		mainscene.world.critter_sightrange = critter_sightrange;
		mainscene.world.critter_retinasize = critter_retinasize;
		mainscene.world.critter_colorneurons = critter_colorneurons;
		mainscene.world.critter_maxmutations = critter_maxmutations;
		mainscene.world.critter_mutationrate = critter_mutationrate;
		mainscene.world.critter_percentchangetype = critter_percentchangetype;
		mainscene.world.critter_flipnewborns = critter_flipnewborns;

		// food
		mainscene.world.food_maxlifetime = food_maxlifetime;
		mainscene.world.food_maxenergy = food_maxenergy;
		mainscene.world.food_size = food_size;

		// corpse
		mainscene.world.corpse_maxlifetime = corpse_maxlifetime;
		mainscene.world.corpse_maxenergy = corpse_maxenergy;
		mainscene.world.corpse_size = corpse_size;

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
