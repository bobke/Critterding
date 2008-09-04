#include "gl/glwindow.h"
#include "scenes/evolution.h"
using namespace std;

string helpinfo = " \
\nSTARTUP OPTIONS\
\n\
\n  option       [default value]\
\n\
\n  Global Settings\
\n  --worldsize             [25]  Creates a 25x25 world\
\n  --energy               [500]  Energy in the system: 500*foodenergy(2500) = 1250000\
\n  --mincritters           [10]  If less than 10 critters are present, insert an adam\
\n  --retinasperrow         [20]  Amount of retinas on a row (bottom left of window)\
\n\
\n  Critter Settings\
\n  --critter_maxlifetime [2000]  Maximum amount of frames a critter can live\
\n  --critter_maxenergy   [5000]  Maximum amount of energy in a critter\
\n  --critter_size          [10]  Size of a critter\
\n  --critter_speed         [50]  Critter speed (50/1000 = 0.05 floor square)\
\n  --critter_sightrange    [40]  Distance a critter can see (40/10 = 4 floor squares)\
\n  --critter_retinasize     [7]  Resolution of critter's retina: 7x7\
\n  --critter_colorneurons   [3]  Earch color of every pixel (RGBA) will get [3] neurons (only for new adams)\
\n  --critter_mutationrate  [10]  When a critter procreates it mutates 10% of the time\
\n  --critter_maxmutateruns  [1]  When a critter mutates, it can do 1 mutation at maximum\
\n  --critter_flipnewborns        If set, newborns will be flipped 180 degrees\
\n\
\n  Food Settings\
\n  --food_maxlifetime    [1000]  Maximum amount of frames food can live\
\n  --food_maxenergy      [2500]  Maximum amount of energy in a food unit\
\n  --food_size             [15]  Size of a food unit\
\n\
\n  Brain Settings\
\n  --brain_maxneurons                           [1000]  Max neurons per critter\
\n  --brain_minsynapses                             [1]  Min synapses per neuron\
\n  --brain_maxsynapses                           [100]  Max synapses per neuron\
\n  --brain_minneuronsatbuildtime                  [20]  Min neurons for a new critter\
\n  --brain_maxneuronsatbuildtime                  [30]  Max neurons for a new critter\
\n\
\n  --brain_minsynapsesatbuildtime                  [1]  Min synapses when creating new neuron\
\n   --brain_mutate_minsynapsesatbuildtime               If set, the value above will mutate\
\n\
\n  --brain_maxsynapsesatbuildtime                 [60]  Max synapses when creating new neuron\
\n   --brain_mutate_maxsynapsesatbuildtime               If set, the value above will mutate\
\n\
\n  --brain_percentchanceinhibitoryneuron          [50]  % chance neuron is inhibitory (vs exhibitory)\
\n   --brain_mutate_percentchanceinhibitoryneuron        If set, the value above will mutate\
\n\
\n  --brain_percentchancemotorneuron               [50]  % chance a neuron is a motor neuron, this value seems\
\n                                                       high, but when it tries to create a motor neuron that is\
\n                                                       is already taken, it will stay a normal neuron\
\n   --brain_mutate_percentchancemotorneuron             If set, the value above will mutate\
\n\
\n  --brain_percentchanceplasticneuron             [20]  % chance a neuron applies synaptic plasticity\
\n   --brain_mutate_percentchanceplasticneuron           If set, the value above will mutate\
\n\
\n  --brain_minplasticitystrengthen               [100]  Min weight by which plastic synapses strengthen (1/100)\
\n  --brain_maxplasticitystrengthen              [1000]  Max weight by which plastic synapses strengthen (1/1000)\
\n  --brain_minplasticityweaken                  [1000]  Min weight by which plastic synapses weaken (1/1000)\
\n  --brain_maxplasticityweaken                 [10000]  Max weight by which plastic synapses weaken (1/10000)\
\n   --brain_mutate_plasticityfactors                    If set, all values above will mutate\
\n\
\n  --brain_minfiringthreshold                      [2]  Min firing threshold of a neuron\
\n   --brain_mutate_minfiringthreshold                   If set, the value above will mutate\
\n\
\n  --brain_maxfiringthreshold                     [10]  Max firing threshold of a neuron\
\n   --brain_mutate_maxfiringthreshold                   If set, the value above will mutate\
\n\
\n  --brain_maxdendridicbranches                    [3]  Max dendridic branches per neuron\
\n   --brain_mutate_maxdendridicbranches                 If set, the value above will mutate\
\n\
\n  --brain_percentchanceconsistentsynapses        [50]  % chance neuron has consistent synapses\
\n                                                       meaning all (new) synapses are inhibitory or exhibitory\
\n   --brain_mutate_percentchanceconsistentsynapses      If set, the value above will mutate\
\n\
\n  --brain_percentchanceinhibitorysynapses        [50]  % chance a synapse is inhibitory (vs exhibitory)\
\n   --brain_mutate_percentchanceinhibitorysynapses      If set, the value above will mutate\
\n\
\n  --brain_percentchancesensorysynapse            [20]  % chance a synapse connects with a sensor (inputneuron)\
\n   --brain_mutate_percentchancesensorysynapse          If set, the value above will mutate\
\n\
\n  --brain_percentmutateeffectaddneuron           [10]  % chance of adding a neuron for a mutationrun\
\n  --brain_percentmutateeffectremoveneuron        [10]  % chance of removing a neuron for a mutationrun\
\n  --brain_percentmutateeffectalterneuron         [20]  % chance of altering a neuron for a mutationrun\
\n  --brain_percentmutateeffectaddsynapse          [30]  % chance of adding a synapse for a mutationrun\
\n  --brain_percentmutateeffectremovesynapse       [30]  % chance of removing a synapse for a mutationrun\
\n   --brain_mutate_mutateeffects                        If set, all values above will mutate";

// Global Settings
	unsigned int worldsize				= 25;
	unsigned int energy				= 500;
	unsigned int mincritters			= 10;
	unsigned int retinasperrow			= 20;

// Critter Settings
	unsigned int critter_maxlifetime					= 2000;
	unsigned int critter_maxenergy						= 5000;
	float        critter_size						= 0.1f;
	float        critter_speed						= 0.05f;
	float        critter_sightrange						= 4.0f;
	unsigned int critter_retinasize						= 7;
	unsigned int critter_colorneurons					= 3;
	unsigned int critter_mutationrate					= 10;
	unsigned int critter_maxmutateruns					= 1;
	bool critter_flipnewborns						= false;

// Food Settings
	unsigned int food_maxlifetime						= 1000;
	unsigned int food_maxenergy						= 2500;
	float        food_size							= 0.15f;

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

	int optind=1;
	// decode arguments
	while ((optind < argc) && (argv[optind][0]=='-'))
	{
		string sw = argv[optind];

	// Global Settings
		if (sw=="--worldsize")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 1 && value <= 1000000 )
				worldsize = value;
			else { cerr << "worldsize must match >=1 and <=1000000" << endl; exit(1); }
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
	// Critter Settings
		else if (sw=="--critter_maxlifetime")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 0 && value <= 1000000 )
				critter_maxlifetime = value;
			else { cerr << "critter_maxlifetime must match >=1 and <=1000000" << endl; exit(1); }
	        }
		else if (sw=="--critter_maxenergy")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 0 && value <= 1000000 )
				critter_maxenergy = value;
			else { cerr << "critter_maxenergy must match >=1 and <=1000000" << endl; exit(1); }
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
		else if (sw=="--critter_maxmutateruns")
		{
			optind++;
			unsigned int value = atoi(argv[optind]);
			if ( value >= 1 && value <= 100 )
				critter_maxmutateruns = value;
			else { cerr << "critter_maxmutateruns must match >=1 and <=100" << endl; exit(1); }
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
			cout << helpinfo << endl;
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

	// report settings
	cout << endl << "Global Settings" << endl;
	cout << "  World size                  = " << worldsize << "x" << worldsize << endl;
	cout << "  Energy in system            = " << energy << "*" << food_maxenergy << " = " << energy*food_maxenergy << endl;
	cout << "  Minimal amount of critters  = " << mincritters << endl;
	cout << "  Retinas per row             = " << retinasperrow << endl;

	cout << endl << "Critter Settings" << endl;
	cout << "  max Lifetime               = " << critter_maxlifetime << endl;
	cout << "  max Energy                 = " << critter_maxenergy << endl;
	cout << "  Size                        = " << critter_size*100.0f << endl;
	cout << "  Speed                       = " << critter_speed*1000.0f << endl;
	cout << "  Sight range                 = " << critter_sightrange*10.0f << endl;
	cout << "  Retina size                 = " << critter_retinasize << endl;
	cout << "  Color neurons               = " << critter_colorneurons << endl;
	cout << "  Mutationrate                = " << critter_mutationrate << endl;
	cout << "  Mutationruns                = " << critter_maxmutateruns << endl;
	cout << "  Flip newborns               = " << critter_flipnewborns << endl;

	cout << endl << "Food Settings" << endl;
	cout << "  max Lifetime                = " << food_maxlifetime << endl;
	cout << "  max Energy                  = " << food_maxenergy << endl;
	cout << "  Size                        = " << food_size*100.0f << endl;

	cout << endl << "Brain Settings" << endl;
	cout << "  max Neurons per critter     = " << brain_maxneurons << endl;
	cout << "  min Synapses per neuron     = " << brain_minsynapses << endl;
	cout << "  max Synapses per neuron     = " << brain_maxsynapses << endl;
	cout << "  min Neurons at build time   = " << brain_minneuronsatbuildtime << endl;
	cout << "  max Neurons at build time   = " << brain_maxneuronsatbuildtime << endl;
	cout << "  min Synapses at build time  = " << brain_minsynapsesatbuildtime << endl;
	cout << "    mutate                    = " << brain_mutate_minsynapsesatbuildtime << endl;
	cout << "  max Synapses at build time  = " << brain_maxsynapsesatbuildtime << endl;
	cout << "    mutate                    = " << brain_mutate_maxsynapsesatbuildtime << endl;
	cout << "  % Inhibitory neuron         = " << brain_percentchanceinhibitoryneuron << endl;
	cout << "    mutate                    = " << brain_mutate_percentchanceinhibitoryneuron << endl;
	cout << "  % Motor neuron              = " << brain_percentchancemotorneuron << endl;
	cout << "    mutate                    = " << brain_mutate_percentchancemotorneuron << endl;
	cout << "  % Plastic neuron            = " << brain_percentchanceplasticneuron << endl;
	cout << "    mutate                    = " << brain_mutate_percentchanceplasticneuron << endl;
	cout << "  min Plasticity strengthen   = " << brain_minplasticitystrengthen << endl;
	cout << "  max Plasticity strengthen   = " << brain_maxplasticitystrengthen << endl;
	cout << "  min Plasticity weaken       = " << brain_minplasticityweaken << endl;
	cout << "  max Plasticity weaken       = " << brain_maxplasticityweaken << endl;
	cout << "    mutate plasticityfactors  = " << brain_mutate_plasticityfactors << endl;
	cout << "  min Firing threshold        = " << brain_minfiringthreshold << endl;
	cout << "    mutate                    = " << brain_mutate_minfiringthreshold << endl;
	cout << "  max Firing threshold        = " << brain_maxfiringthreshold << endl;
	cout << "    mutate                    = " << brain_mutate_maxfiringthreshold << endl;
	cout << "  max Dendridic branches      = " << brain_maxdendridicbranches << endl;
	cout << "    mutate                    = " << brain_mutate_maxdendridicbranches << endl;
	cout << "  % Consistent synapses       = " << brain_percentchanceconsistentsynapses << endl;
	cout << "    mutate                    = " << brain_mutate_percentchanceconsistentsynapses << endl;
	cout << "  % Inhibitory synapses       = " << brain_percentchanceinhibitorysynapses << endl;
	cout << "    mutate                    = " << brain_mutate_percentchanceinhibitorysynapses << endl;
	cout << "  % Sensory Synapse           = " << brain_percentchancesensorysynapse << endl;
	cout << "    mutate                    = " << brain_mutate_percentchancesensorysynapse << endl;
	cout << "  % Effect: add neuron        = " << brain_percentmutateeffectaddneuron << endl;
	cout << "  % Effect: remove neuron     = " << brain_percentmutateeffectremoveneuron << endl;
	cout << "  % Effect: alter neuron      = " << brain_percentmutateeffectalterneuron << endl;
	cout << "  % Effect: add synapse       = " << brain_percentmutateeffectaddsynapse << endl;
	cout << "  % Effect: remove synapse    = " << brain_percentmutateeffectremovesynapse << endl;
	cout << "    mutate effects            = " << brain_mutate_mutateeffects << endl;

	cout << endl;

	GLWindow glwindow;
	glwindow.create("Critterding beta5", 800, 600, 24, False);

		Evolution mainscene;

		// critter
		mainscene.world.critter_maxlifetime = critter_maxlifetime;
		mainscene.world.critter_maxenergy = critter_maxenergy;
		mainscene.world.critter_size = critter_size;
		mainscene.world.critter_speed = critter_speed;
		mainscene.world.critter_sightrange = critter_sightrange;
		mainscene.world.critter_retinasize = critter_retinasize;
		mainscene.world.critter_colorneurons = critter_colorneurons;
		mainscene.world.critter_maxmutateruns = critter_maxmutateruns;
		mainscene.world.critter_mutationrate = critter_mutationrate;
		mainscene.world.critter_flipnewborns = critter_flipnewborns;

		// food
		mainscene.world.food_maxlifetime = food_maxlifetime;
		mainscene.world.food_maxenergy = food_maxenergy;
		mainscene.world.food_size = food_size;

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

		glwindow.runGLScene(mainscene);

	glwindow.destroy();
}
