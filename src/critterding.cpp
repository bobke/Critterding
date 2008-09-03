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
\n  --critter_flipnewborns   [0]  If set to 1, newborns will be flipped 180 degrees\
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
\n   --brain_mutate_minsynapsesatbuildtime          [0]  If set to 1, the value above will mutate\
\n\
\n  --brain_maxsynapsesatbuildtime                 [60]  Max synapses when creating new neuron\
\n   --brain_mutate_maxsynapsesatbuildtime          [0]  If set to 1, the value above will mutate\
\n\
\n  --brain_percentchanceinhibitoryneuron          [50]  % chance neuron is inhibitory (vs exhibitory)\
\n   --brain_mutate_percentchanceinhibitoryneuron   [0]  If set to 1, the value above will mutate\
\n\
\n  --brain_percentchancemotorneuron               [50]  % chance a neuron is a motor neuron, this value seems\
\n                                                       high, but when it tries to create a motor neuron that is\
\n                                                       is already taken, it will stay a normal neuron\
\n   --brain_mutate_percentchancemotorneuron        [0]  If set to 1, the value above will mutate\
\n\
\n  --brain_percentchanceplasticneuron             [20]  % chance a neuron applies synaptic plasticity\
\n   --brain_mutate_percentchanceplasticneuron      [0]  If set to 1, the value above will mutate\
\n\
\n  --brain_minplasticitystrengthen               [100]  Min weight by which plastic synapses strengthen (1/100)\
\n  --brain_maxplasticitystrengthen              [1000]  Max weight by which plastic synapses strengthen (1/1000)\
\n  --brain_minplasticityweaken                  [1000]  Min weight by which plastic synapses weaken (1/1000)\
\n  --brain_maxplasticityweaken                 [10000]  Max weight by which plastic synapses weaken (1/10000)\
\n   --brain_mutate_plasticityfactors               [0]  If set to 1, all values above will mutate\
\n\
\n  --brain_minfiringthreshold                      [2]  Min firing threshold of a neuron\
\n   --brain_mutate_minfiringthreshold              [0]  If set to 1, the value above will mutate\
\n\
\n  --brain_maxfiringthreshold                     [10]  Max firing threshold of a neuron\
\n   --brain_mutate_maxfiringthreshold              [0]  If set to 1, the value above will mutate\
\n\
\n  --brain_maxdendridicbranches                    [3]  Max dendridic branches per neuron\
\n   --brain_mutate_maxdendridicbranches            [0]  If set to 1, the value above will mutate\
\n\
\n  --brain_percentchanceconsistentsynapses        [50]  % chance neuron has consistent synapses\
\n                                                       meaning all (new) synapses are inhibitory or exhibitory\
\n   --brain_mutate_percentchanceconsistentsynapses [0]  If set to 1, the value above will mutate\
\n\
\n  --brain_percentchanceinhibitorysynapses        [50]  % chance a synapse is inhibitory (vs exhibitory)\
\n   --brain_mutate_percentchanceinhibitorysynapses [0]  If set to 1, the value above will mutate\
\n\
\n  --brain_percentchancesensorysynapse            [20]  % chance a synapse connects with a sensor (inputneuron)\
\n   --brain_mutate_percentchancesensorysynapse     [0]  If set to 1, the value above will mutate\
\n\
\n  --brain_percentmutateeffectaddneuron           [10]  % chance of adding a neuron for a mutationrun\
\n  --brain_percentmutateeffectremoveneuron        [10]  % chance of removing a neuron for a mutationrun\
\n  --brain_percentmutateeffectalterneuron         [20]  % chance of altering a neuron for a mutationrun\
\n  --brain_percentmutateeffectaddsynapse          [30]  % chance of adding a synapse for a mutationrun\
\n  --brain_percentmutateeffectremovesynapse       [30]  % chance of removing a synapse for a mutationrun\
\n   --brain_mutate_mutateeffects                   [0]  If set to 1, all values above will mutate";

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
	unsigned int critter_flipnewborns					= 0;

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
		unsigned int brain_mutate_minsynapsesatbuildtime		= 0;

	unsigned int brain_maxsynapsesatbuildtime				= 60;
		unsigned int brain_mutate_maxsynapsesatbuildtime		= 0;

	unsigned int brain_percentchanceinhibitoryneuron			= 50;
		unsigned int brain_mutate_percentchanceinhibitoryneuron		= 0;

	unsigned int brain_percentchancemotorneuron				= 50;
		unsigned int brain_mutate_percentchancemotorneuron		= 0;

	unsigned int brain_percentchanceplasticneuron				= 20;
		unsigned int brain_mutate_percentchanceplasticneuron		= 0;

	unsigned int brain_minplasticitystrengthen				= 100;
	unsigned int brain_maxplasticitystrengthen				= 1000;
	unsigned int brain_minplasticityweaken					= 1000;
	unsigned int brain_maxplasticityweaken					= 10000;
		unsigned int brain_mutate_plasticityfactors			= 0;

	unsigned int brain_minfiringthreshold					= 2;
		unsigned int brain_mutate_minfiringthreshold			= 0;

	unsigned int brain_maxfiringthreshold					= 10;
		unsigned int brain_mutate_maxfiringthreshold			= 0;

	unsigned int brain_maxdendridicbranches					= 3;
		unsigned int brain_mutate_maxdendridicbranches			= 0;

	unsigned int brain_percentchanceconsistentsynapses			= 50;
		unsigned int brain_mutate_percentchanceconsistentsynapses	= 0;

	unsigned int brain_percentchanceinhibitorysynapses			= 50;
		unsigned int brain_mutate_percentchanceinhibitorysynapses	= 0;

	unsigned int brain_percentchancesensorysynapse				= 20;
		unsigned int brain_mutate_percentchancesensorysynapse		= 0;

	unsigned int brain_percentmutateeffectaddneuron				= 10;
	unsigned int brain_percentmutateeffectremoveneuron			= 10;
	unsigned int brain_percentmutateeffectalterneuron			= 20;
	unsigned int brain_percentmutateeffectaddsynapse			= 30;
	unsigned int brain_percentmutateeffectremovesynapse			= 30;
		unsigned int brain_mutate_mutateeffects				= 0;

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
			worldsize = atoi(argv[optind]);
	        }
		else if (sw=="--energy")
		{
			optind++;
			energy = atoi(argv[optind]);
	        }
		else if (sw=="--mincritters")
		{
			optind++;
			mincritters = atoi(argv[optind]);
	        }
		else if (sw=="--retinasperrow")
		{
			optind++;
			retinasperrow = atoi(argv[optind]);
	        }
	// Critter Settings
		else if (sw=="--critter_maxlifetime")
		{
			optind++;
			critter_maxlifetime = atoi(argv[optind]);
	        }
		else if (sw=="--critter_maxenergy")
		{
			optind++;
			critter_maxenergy = atoi(argv[optind]);
	        }
		else if (sw=="--critter_size")
		{
			optind++;
			critter_size = (float)atoi(argv[optind]) / 100.0f;
	        }
		else if (sw=="--critter_speed")
		{
			optind++;
			critter_speed = (float)atoi(argv[optind]) / 1000.0f;
	        }
		else if (sw=="--critter_sightrange")
		{
			optind++;
			critter_sightrange = (float)atoi(argv[optind]) / 10.0f;
	        }
		else if (sw=="--critter_retinasize")
		{
			optind++;
			critter_retinasize = atoi(argv[optind]);
	        }
		else if (sw=="--critter_colorneurons")
		{
			optind++;
			critter_colorneurons = atoi(argv[optind]);
	        }
		else if (sw=="--critter_mutationrate")
		{
			optind++;
			critter_mutationrate = atoi(argv[optind]);
	        }
		else if (sw=="--critter_maxmutateruns")
		{
			optind++;
			critter_maxmutateruns = atoi(argv[optind]);
	        }
		else if (sw=="--critter_flipnewborns")
		{
			optind++;
			if ( atoi(argv[optind]) == 1 )
				critter_flipnewborns = 1;
	        }

	// Food Settings
		else if (sw=="--food_maxlifetime")
		{
			optind++;
			food_maxlifetime = atoi(argv[optind]);
	        }
		else if (sw=="--food_maxenergy")
		{
			optind++;
			food_maxenergy = atoi(argv[optind]);
	        }
		else if (sw=="--food_size")
		{
			optind++;
			food_size = (float)atoi(argv[optind]) / 100.0f;
	        }

	// Brain Settings
		else if (sw=="--brain_maxneurons")
		{
			optind++;
			brain_maxneurons = atoi(argv[optind]);
	        }
		else if (sw=="--brain_minsynapses")
		{
			optind++;
			brain_minsynapses = atoi(argv[optind]);
	        }
		else if (sw=="--brain_maxsynapses")
		{
			optind++;
			brain_maxsynapses = atoi(argv[optind]);
	        }
		else if (sw=="--brain_minneuronsatbuildtime")
		{
			optind++;
			brain_minneuronsatbuildtime = atoi(argv[optind]);
	        }
		else if (sw=="--brain_maxneuronsatbuildtime")
		{
			optind++;
			brain_maxneuronsatbuildtime = atoi(argv[optind]);
	        }
		else if (sw=="--brain_minsynapsesatbuildtime")
		{
			optind++;
			brain_minsynapsesatbuildtime = atoi(argv[optind]);
	        }
		else if (sw=="--brain_mutate_minsynapsesatbuildtime")
		{
			optind++;
			if ( atoi(argv[optind]) == 1 )
				brain_mutate_minsynapsesatbuildtime = 1;
	        }

		else if (sw=="--brain_maxsynapsesatbuildtime")
		{
			optind++;
			brain_maxsynapsesatbuildtime = atoi(argv[optind]);
	        }
		else if (sw=="--brain_mutate_maxsynapsesatbuildtime")
		{
			optind++;
			if ( atoi(argv[optind]) == 1 )
				brain_mutate_maxsynapsesatbuildtime = 1;
	        }
		else if (sw=="--brain_percentchanceinhibitoryneuron")
		{
			optind++;
			brain_percentchanceinhibitoryneuron = atoi(argv[optind]);
	        }
		else if (sw=="--brain_mutate_percentchanceinhibitoryneuron")
		{
			optind++;
			if ( atoi(argv[optind]) == 1 )
				brain_mutate_percentchanceinhibitoryneuron = 1;
	        }
		else if (sw=="--brain_percentchancemotorneuron")
		{
			optind++;
			brain_percentchancemotorneuron = atoi(argv[optind]);
	        }
		else if (sw=="--brain_mutate_percentchancemotorneuron")
		{
			optind++;
			if ( atoi(argv[optind]) == 1 )
				brain_mutate_percentchancemotorneuron = 1;
	        }
		else if (sw=="--brain_percentchanceplasticneuron")
		{
			optind++;
			brain_percentchanceplasticneuron = atoi(argv[optind]);
	        }
		else if (sw=="--brain_mutate_percentchanceplasticneuron")
		{
			optind++;
			if ( atoi(argv[optind]) == 1 )
				brain_mutate_percentchanceplasticneuron = 1;
	        }

		else if (sw=="--brain_minplasticitystrengthen")
		{
			optind++;
			brain_minplasticitystrengthen = atoi(argv[optind]);
	        }
		else if (sw=="--brain_maxplasticitystrengthen")
		{
			optind++;
			brain_maxplasticitystrengthen = atoi(argv[optind]);
	        }
		else if (sw=="--brain_minplasticityweaken")
		{
			optind++;
			brain_minplasticityweaken = atoi(argv[optind]);
	        }
		else if (sw=="--brain_maxplasticityweaken")
		{
			optind++;
			brain_maxplasticityweaken = atoi(argv[optind]);
	        }
		else if (sw=="--brain_mutate_plasticityfactors")
		{
			optind++;
			if ( atoi(argv[optind]) == 1 )
				brain_mutate_plasticityfactors = 1;
	        }


		else if (sw=="--brain_minfiringthreshold")
		{
			optind++;
			brain_minfiringthreshold = atoi(argv[optind]);
	        }
		else if (sw=="--brain_mutate_minfiringthreshold")
		{
			optind++;
			if ( atoi(argv[optind]) == 1 )
				brain_mutate_minfiringthreshold = 1;
	        }
		else if (sw=="--brain_maxfiringthreshold")
		{
			optind++;
			brain_maxfiringthreshold = atoi(argv[optind]);
	        }
		else if (sw=="--brain_mutate_maxfiringthreshold")
		{
			optind++;
			if ( atoi(argv[optind]) == 1 )
				brain_mutate_maxfiringthreshold = 1;
	        }
		else if (sw=="--brain_maxdendridicbranches")
		{
			optind++;
			brain_maxdendridicbranches = atoi(argv[optind]);
	        }
		else if (sw=="--brain_mutate_maxdendridicbranches")
		{
			optind++;
			if ( atoi(argv[optind]) == 1 )
				brain_mutate_maxdendridicbranches = 1;
	        }
		else if (sw=="--brain_percentchanceconsistentsynapses")
		{
			optind++;
			brain_percentchanceconsistentsynapses = atoi(argv[optind]);
	        }
		else if (sw=="--brain_mutate_percentchanceconsistentsynapses")
		{
			optind++;
			if ( atoi(argv[optind]) == 1 )
				brain_mutate_percentchanceconsistentsynapses = 1;
	        }
		else if (sw=="--brain_percentchanceinhibitorysynapses")
		{
			optind++;
			brain_percentchanceinhibitorysynapses = atoi(argv[optind]);
	        }
		else if (sw=="--brain_mutate_percentchanceinhibitorysynapses")
		{
			optind++;
			if ( atoi(argv[optind]) == 1 )
				brain_mutate_percentchanceinhibitorysynapses = 1;
	        }
		else if (sw=="--brain_percentchancesensorysynapse")
		{
			optind++;
			brain_percentchancesensorysynapse = atoi(argv[optind]);
	        }
		else if (sw=="--brain_mutate_percentchancesensorysynapse")
		{
			optind++;
			if ( atoi(argv[optind]) == 1 )
				brain_mutate_percentchancesensorysynapse = 1;
	        }
		else if (sw=="--brain_percentmutateeffectaddneuron")
		{
			optind++;
			brain_percentmutateeffectaddneuron = atoi(argv[optind]);
	        }
		else if (sw=="--brain_percentmutateeffectremoveneuron")
		{
			optind++;
			brain_percentmutateeffectremoveneuron = atoi(argv[optind]);
	        }
		else if (sw=="--brain_percentmutateeffectalterneuron")
		{
			optind++;
			brain_percentmutateeffectalterneuron = atoi(argv[optind]);
	        }
		else if (sw=="--brain_percentmutateeffectaddsynapse")
		{
			optind++;
			brain_percentmutateeffectaddsynapse = atoi(argv[optind]);
	        }
		else if (sw=="--brain_percentmutateeffectremovesynapse")
		{
			optind++;
			brain_percentmutateeffectremovesynapse = atoi(argv[optind]);
	        }
		else if (sw=="--brain_mutate_mutateeffects")
		{
			optind++;
			if ( atoi(argv[optind]) == 1 )
				brain_mutate_mutateeffects = 1;
	        }

		else if (sw=="--help")
		{
			cout << helpinfo << endl;
			exit(1);
	        }

		else
		{
			cout << "Unknown switch: " << argv[optind] << endl;
			cout << helpinfo << endl;
			exit(1);
		}
		optind++;
	}

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

// 	cout << "Remaining arguments = ";
// 	for (;optind<argc;optind++)
// 	{
// 		cout << argv[optind];
// 	}
// 	cout << endl << endl;

	//cerr << "Starting application" << endl;

	GLWindow glwindow;
	glwindow.create("Critterding beta4", 600, 600, 24, False);

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
		if (critter_flipnewborns == 1) mainscene.world.critter_flipnewborns = true;

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
		if (brain_mutate_minsynapsesatbuildtime == 1) mainscene.world.brain_mutate_minsynapsesatbuildtime = true;
		mainscene.world.brain_maxsynapsesatbuildtime = brain_maxsynapsesatbuildtime;
		if (brain_mutate_maxsynapsesatbuildtime == 1) mainscene.world.brain_mutate_maxsynapsesatbuildtime = true;
		mainscene.world.brain_percentchanceinhibitoryneuron = brain_percentchanceinhibitoryneuron;
		if (brain_mutate_percentchanceinhibitoryneuron == 1) mainscene.world.brain_mutate_percentchanceinhibitoryneuron = true;
		mainscene.world.brain_percentchanceconsistentsynapses = brain_percentchanceconsistentsynapses;
		if (brain_mutate_percentchanceconsistentsynapses == 1) mainscene.world.brain_mutate_percentchanceconsistentsynapses = true;

		mainscene.world.brain_percentchanceinhibitorysynapses = brain_percentchanceinhibitorysynapses;
		if (brain_mutate_percentchanceinhibitorysynapses == 1) mainscene.world.brain_mutate_percentchanceinhibitorysynapses = true;
		mainscene.world.brain_percentchancemotorneuron = brain_percentchancemotorneuron;
		if (brain_mutate_percentchancemotorneuron == 1) mainscene.world.brain_mutate_percentchancemotorneuron = true;
		mainscene.world.brain_percentchanceplasticneuron = brain_percentchanceplasticneuron;
		if (brain_mutate_percentchanceplasticneuron == 1) mainscene.world.brain_mutate_percentchanceplasticneuron = true;

		mainscene.world.brain_minplasticitystrengthen = brain_minplasticitystrengthen;
		mainscene.world.brain_maxplasticitystrengthen = brain_maxplasticitystrengthen;
		mainscene.world.brain_minplasticityweaken = brain_minplasticityweaken;
		mainscene.world.brain_maxplasticityweaken = brain_maxplasticityweaken;
		if (brain_mutate_plasticityfactors == 1) mainscene.world.brain_mutate_plasticityfactors = true;

		mainscene.world.brain_percentchancesensorysynapse = brain_percentchancesensorysynapse;
		if (brain_mutate_percentchancesensorysynapse == 1) mainscene.world.brain_mutate_percentchancesensorysynapse = true;
		mainscene.world.brain_minfiringthreshold = brain_minfiringthreshold;
		if (brain_mutate_minfiringthreshold == 1) mainscene.world.brain_mutate_minfiringthreshold = true;
		mainscene.world.brain_maxfiringthreshold = brain_maxfiringthreshold;
		if (brain_mutate_maxfiringthreshold == 1) mainscene.world.brain_mutate_maxfiringthreshold = true;
		mainscene.world.brain_maxdendridicbranches = brain_maxdendridicbranches;
		if (brain_mutate_maxdendridicbranches == 1) mainscene.world.brain_mutate_maxdendridicbranches = true;

		mainscene.world.brain_percentmutateeffectaddneuron = brain_percentmutateeffectaddneuron;
		mainscene.world.brain_percentmutateeffectremoveneuron = brain_percentmutateeffectremoveneuron;
		mainscene.world.brain_percentmutateeffectalterneuron = brain_percentmutateeffectalterneuron;
		mainscene.world.brain_percentmutateeffectaddsynapse = brain_percentmutateeffectaddsynapse;
		mainscene.world.brain_percentmutateeffectremovesynapse = brain_percentmutateeffectremovesynapse;
		if (brain_mutate_mutateeffects == 1) mainscene.world.brain_mutate_mutateeffects = true;

		// global
		mainscene.world.retinasperrow = retinasperrow;
		mainscene.world.resize(worldsize);
		mainscene.world.startfoodamount(energy);
		mainscene.world.setMincritters(mincritters);

		glwindow.runGLScene(mainscene);

	glwindow.destroy();
}
