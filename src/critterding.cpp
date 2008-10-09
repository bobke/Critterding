#include "gl/glwindow.h"
#include "scenes/evolution.h"
#include "utils/settings.h"

using namespace std;

Settings *settings = Settings::Instance();


bool checkSwitch(string matchsw, unsigned int &var, unsigned int min, unsigned int max, int optind, char *argv[])
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

	helpinfo << "  --worldsize                 [" << settings->worldsize << "]  Creates a " << settings->worldsize << "x" << settings->worldsize << " world" << endl;
	helpinfo << "  --energy                   [" << settings->startenergy << "]  Energy in the system: " << settings->startenergy << "*food_energy(" << settings->food_maxenergy << ") = " << settings->startenergy*settings->food_maxenergy << "" << endl;
	helpinfo << "  --mincritters               [" << settings->mincritters << "]  If less than " << settings->mincritters << " critters are present, insert an adam" << endl;
	helpinfo << "  --retinasperrow             [" << settings->retinasperrow << "]  Place " << settings->retinasperrow << " retinas on a row (bottom left of window)" << endl;
	helpinfo << "  --camerasensitivity         [" << settings->camerasensitivity << "]  Camera sensitivity" << endl;
	helpinfo << "  --exit_if_empty                   If set, the program will exit when no critters exist" << endl;

	helpinfo << endl;
	helpinfo << "  Critter Settings" << endl;
	helpinfo << "  --critter_maxlifetime     [" << settings->critter_maxlifetime << "]  Max amount of frames a critter can live" << endl;
	helpinfo << "  --critter_maxenergy       [" << settings->critter_maxenergy << "]  Max amount of energy in a critter" << endl;
	helpinfo << "  --critter_startenergy     [" << settings->critter_startenergy << "]  Starting amount of energy for a new critter" << endl;
	helpinfo << "  --critter_procinterval      [" << settings->critter_procinterval << "]  Time (in frames) between procreations" << endl;
	helpinfo << "  --critter_fireinterval       [" << settings->critter_fireinterval << "]  Time (in frames) between bullets being fired" << endl;
	helpinfo << "  --critter_minenergyproc   [" << settings->critter_minenergyproc << "]  Min amount of energy required for procreation" << endl;
	helpinfo << "  --critter_minenergyfire      [" << settings->critter_minenergyfire << "]  Min amount of energy required for firing a bullet" << endl;
	helpinfo << "  --critter_size              [" << settings->critter_sizeI << "]  Size of a critter" << endl;
	helpinfo << "  --critter_speed             [" << settings->critter_speedI << "]  Critter speed" << endl;
	helpinfo << "  --critter_sightrange        [" << settings->critter_sightrangeI << "]  Distance a critter can see (" << settings->critter_sightrangeI*10.0f << " = " << settings->critter_sightrangeI << " floor squares)" << endl;
	helpinfo << "  --critter_retinasize         [" << settings->critter_retinasize << "]  Resolution of critter's retina: " << settings->critter_retinasize << "x" << settings->critter_retinasize << "" << endl;
	helpinfo << "  --critter_colorneurons       [" << settings->critter_colorneurons << "]  Earch color of every pixel (RGBA) will get [" << settings->critter_colorneurons << "] neurons (only for new adams)" << endl;
	helpinfo << "  --critter_mutationrate       [" << settings->critter_mutationrate << "]  When a critter procreates there is a " << settings->critter_mutationrate << "% chance it will mutate" << endl;
	helpinfo << "  --critter_maxmutations       [" << settings->critter_maxmutations << "]  When a critter mutates, it can do " << settings->critter_maxmutations << " mutations at maximum" << endl;
	helpinfo << "  --critter_percentchangetype  [" << settings->critter_percentchangetype << "]  When a critter mutates, percent chance it changes type" << endl;
	helpinfo << "  --critter_flipnewborns            If set, newborns will be flipped 180 degrees" << endl;
	helpinfo << "  --critter_randomrotatenewborns    If set, newborns will be rotated randomly" << endl;

	helpinfo << "  --critter_autosaveinterval   [" << settings->critter_autosaveinterval << "]  Save all critters every N seconds (0=disabled)" << endl;
	helpinfo << endl;
	helpinfo << "  Food Settings" << endl;
	helpinfo << "  --food_maxlifetime         [" << settings->food_maxlifetime << "]  Maximum amount of frames food exists" << endl;
	helpinfo << "  --food_maxenergy          [" << settings->food_maxenergy << "]  Maximum amount of energy in a food unit" << endl;
	helpinfo << "  --food_size                 [" << settings->food_sizeI << "]  Size of a food unit" << endl;
	helpinfo << endl;
	helpinfo << "  Corpse Settings" << endl;
	helpinfo << "  --corpse_disable                  Sets corpse_maxlifetime=0, critter_percentchangetype=0" << endl;
	helpinfo << "  --corpse_maxlifetime      [" << settings->corpse_maxlifetime << "]  Maximum amount of frames a corpse exists" << endl;
	helpinfo << "  --corpse_maxenergy        [" << settings->corpse_maxenergy << "]  Maximum amount of energy in a corpse unit" << endl;
	helpinfo << "  --corpse_size               [" << settings->corpse_sizeI << "]  Size of a corpse unit" << endl;
	helpinfo << endl;
	helpinfo << "  Brain Settings" << endl;
	helpinfo << "  --brain_maxneurons                           [" << settings->brain_maxneurons << "]  Max neurons per critter" << endl;
	helpinfo << "  --brain_minsynapses                             [" << settings->brain_minsynapses << "]  Min synapses per neuron" << endl;
	helpinfo << "  --brain_maxsynapses                           [" << settings->brain_maxsynapses << "]  Max synapses per neuron" << endl;
	helpinfo << "  --brain_minneuronsatbuildtime                  [" << settings->brain_minneuronsatbuildtime << "]  Min neurons for a new critter" << endl;
	helpinfo << "  --brain_maxneuronsatbuildtime                  [" << settings->brain_maxneuronsatbuildtime << "]  Max neurons for a new critter" << endl;
	helpinfo << "  --brain_minsynapsesatbuildtime                  [" << settings->brain_minsynapsesatbuildtime << "]  Min synapses when creating new neuron" << endl;
	helpinfo << "    --brain_mutate_minsynapsesatbuildtime              If set, the value above will mutate" << endl;
	helpinfo << "  --brain_maxsynapsesatbuildtime                 [" << settings->brain_maxsynapsesatbuildtime << "]  Max synapses when creating new neuron" << endl;
	helpinfo << "    --brain_mutate_maxsynapsesatbuildtime              If set, the value above will mutate" << endl;
	helpinfo << "  --brain_percentchanceinhibitoryneuron          [" << settings->brain_percentchanceinhibitoryneuron << "]  % chance neuron is inhibitory (vs exhibitory)" << endl;
	helpinfo << "    --brain_mutate_percentchanceinhibitoryneuron       If set, the value above will mutate" << endl;
	helpinfo << "  --brain_percentchancemotorneuron               [" << settings->brain_percentchancemotorneuron << "]  % chance a neuron is a motor neuron, this value seems" << endl;
	helpinfo << "                                                       high, but when it tries to create a motor neuron that is" << endl;
	helpinfo << "                                                       is already taken, it will stay a normal neuron" << endl;
	helpinfo << "    --brain_mutate_percentchancemotorneuron            If set, the value above will mutate" << endl;
	helpinfo << "  --brain_percentchanceplasticneuron             [" << settings->brain_percentchanceplasticneuron << "]  % chance a neuron applies synaptic plasticity" << endl;
	helpinfo << "    --brain_mutate_percentchanceplasticneuron          If set, the value above will mutate" << endl;
	helpinfo << "  --brain_minplasticitystrengthen               [" << settings->brain_minplasticitystrengthen << "]  Min weight by which plastic synapses strengthen (1/" << settings->brain_minplasticitystrengthen << ")" << endl;
	helpinfo << "  --brain_maxplasticitystrengthen              [" << settings->brain_maxplasticitystrengthen << "]  Max weight by which plastic synapses strengthen (1/" << settings->brain_maxplasticitystrengthen << ")" << endl;
	helpinfo << "  --brain_minplasticityweaken                  [" << settings->brain_minplasticityweaken << "]  Min weight by which plastic synapses weaken (1/" << settings->brain_minplasticityweaken << ")" << endl;
	helpinfo << "  --brain_maxplasticityweaken                 [" << settings->brain_maxplasticityweaken << "]  Max weight by which plastic synapses weaken (1/" << settings->brain_maxplasticityweaken << ")" << endl;
	helpinfo << "    --brain_mutate_plasticityfactors                   If set, all values above will mutate" << endl;
	helpinfo << "  --brain_minfiringthreshold                      [" << settings->brain_minfiringthreshold << "]  Min firing threshold of a neuron" << endl;
	helpinfo << "    --brain_mutate_minfiringthreshold                  If set, the value above will mutate" << endl;
	helpinfo << "  --brain_maxfiringthreshold                     [" << settings->brain_maxfiringthreshold << "]  Max firing threshold of a neuron" << endl;
	helpinfo << "    --brain_mutate_maxfiringthreshold                  If set, the value above will mutate" << endl;
	helpinfo << "  --brain_maxdendridicbranches                    [" << settings->brain_maxdendridicbranches << "]  Max dendridic branches per neuron" << endl;
	helpinfo << "    --brain_mutate_maxdendridicbranches                If set, the value above will mutate" << endl;
	helpinfo << "  --brain_percentchanceconsistentsynapses        [" << settings->brain_percentchanceconsistentsynapses << "]  % chance neuron has consistent synapses" << endl;
	helpinfo << "                                                       meaning all (new) synapses are inhibitory or exhibitory" << endl;
	helpinfo << "    --brain_mutate_percentchanceconsistentsynapses     If set, the value above will mutate" << endl;
	helpinfo << "  --brain_percentchanceinhibitorysynapses        [" << settings->brain_percentchanceinhibitorysynapses << "]  % chance a synapse is inhibitory (vs exhibitory)" << endl;
	helpinfo << "    --brain_mutate_percentchanceinhibitorysynapses     If set, the value above will mutate" << endl;
	helpinfo << "  --brain_percentchancesensorysynapse            [" << settings->brain_percentchancesensorysynapse << "]  % chance a synapse connects with a sensor (inputneuron)" << endl;
	helpinfo << "    --brain_mutate_percentchancesensorysynapse         If set, the value above will mutate" << endl;
	helpinfo << "  --brain_percentmutateeffectaddneuron           [" << settings->brain_percentmutateeffectaddneuron << "]  % chance of adding a neuron for a mutationrun" << endl;
	helpinfo << "  --brain_percentmutateeffectremoveneuron        [" << settings->brain_percentmutateeffectremoveneuron << "]  % chance of removing a neuron for a mutationrun" << endl;
	helpinfo << "  --brain_percentmutateeffectalterneuron         [" << settings->brain_percentmutateeffectalterneuron << "]  % chance of altering a neuron for a mutationrun" << endl;
	helpinfo << "  --brain_percentmutateeffectaddsynapse          [" << settings->brain_percentmutateeffectaddsynapse << "]  % chance of adding a synapse for a mutationrun" << endl;
	helpinfo << "  --brain_percentmutateeffectremovesynapse       [" << settings->brain_percentmutateeffectremovesynapse << "]  % chance of removing a synapse for a mutationrun" << endl;
	helpinfo << "    --brain_mutate_mutateeffects                       If set, all values above will mutate" << endl;

	int optind=1;
	// decode arguments
	while ((optind < argc) && (argv[optind][0]=='-'))
	{
		string sw = argv[optind];

	// Global Settings

		if (sw=="--small")
		{
			settings->worldsize = 10;
			settings->startenergy = 200;
	        }

		else if (sw=="--medium")
		{
			settings->worldsize = 25;
			settings->startenergy = 500;
	        }

		else if (sw=="--big")
		{
			settings->worldsize = 50;
			settings->startenergy = 2000;
	        }

		else if (sw=="--huge")
		{
			settings->worldsize = 100;
			settings->startenergy = 8000;
	        }

		else if ( checkSwitch("--worldsize", settings->worldsize, 1, 5000, optind, argv) ) optind++;
		else if ( checkSwitch("--energy", settings->startenergy, 0, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--mincritters", settings->mincritters, 0, 1000, optind, argv) ) optind++;
		else if ( checkSwitch("--retinasperrow", settings->retinasperrow, 1, 1000, optind, argv) ) optind++;
		else if ( checkSwitch("--camerasensitivity", settings->camerasensitivity, 1, 1000, optind, argv) ) optind++;
		else if ( sw=="--exit-if-empty") settings->exit_if_empty = true;

	// Critter Settings

		else if ( checkSwitch("--critter_maxlifetime", settings->critter_maxlifetime, 1, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_maxenergy", settings->critter_maxenergy, 1, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_startenergy", settings->critter_startenergy, 1, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_procinterval", settings->critter_procinterval, 1, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_fireinterval", settings->critter_fireinterval, 0, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_minenergyproc", settings->critter_minenergyproc, 0, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_minenergyfire", settings->critter_minenergyfire, 0, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_size", settings->critter_sizeI, 1, 100, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_speed", settings->critter_speedI, 1, 1000, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_sightrange", settings->critter_sightrangeI, 1, 1000, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_retinasize", settings->critter_retinasize, 1, 1000, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_colorneurons", settings->critter_colorneurons, 2, 100, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_mutationrate", settings->critter_mutationrate, 0, 100, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_maxmutations", settings->critter_maxmutations, 1, 100, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_percentchangetype", settings->critter_percentchangetype, 0, 100, optind, argv) ) optind++;
		else if (sw=="--critter_flipnewborns") settings->critter_flipnewborns = true;
		else if (sw=="--critter_randomrotatenewborns") settings->critter_flipnewborns = true;
		else if ( checkSwitch("--critter_autosaveinterval", settings->critter_autosaveinterval, 1, 1000000, optind, argv) ) optind++;

	// Food Settings

		else if ( checkSwitch("--food_maxlifetime", settings->food_maxlifetime, 1, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--food_maxenergy", settings->food_maxenergy, 1, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--food_size", settings->food_sizeI, 1, 100, optind, argv) ) optind++;

	// Corpse Settings

		else if (sw=="--corpse_disable")
		{
			settings->corpse_maxlifetime = 0;
			settings->critter_percentchangetype = 0;
	        }
		else if ( checkSwitch("--corpse_maxlifetime", settings->corpse_maxlifetime, 0, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--corpse_maxenergy", settings->corpse_maxenergy, 1, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--corpse_size", settings->corpse_sizeI, 1, 100, optind, argv) ) optind++;

	// Brain Settings

		else if ( checkSwitch("--brain_maxneurons", settings->brain_maxneurons, 1, 1000000, optind, argv) ) optind++;

		else if ( checkSwitch("--brain_minsynapses", settings->brain_minsynapses, 1, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--brain_maxsynapses", settings->brain_maxsynapses, 1, 1000000, optind, argv) ) optind++;

		else if ( checkSwitch("--brain_minneuronsatbuildtime", settings->brain_minneuronsatbuildtime, 1, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--brain_maxneuronsatbuildtime", settings->brain_maxneuronsatbuildtime, 1, 1000000, optind, argv) ) optind++;

		else if ( checkSwitch("--brain_minsynapsesatbuildtime", settings->brain_minsynapsesatbuildtime, 1, 1000000, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_minsynapsesatbuildtime") settings->brain_mutate_minsynapsesatbuildtime = true;

		else if ( checkSwitch("--brain_maxsynapsesatbuildtime", settings->brain_maxsynapsesatbuildtime, 1, 1000000, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_maxsynapsesatbuildtime") settings->brain_mutate_maxsynapsesatbuildtime = true;

		else if ( checkSwitch("--brain_percentchanceinhibitoryneuron", settings->brain_percentchanceinhibitoryneuron, 0, 100, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_percentchanceinhibitoryneuron") settings->brain_mutate_percentchanceinhibitoryneuron = true;

		else if ( checkSwitch("--brain_percentchancemotorneuron", settings->brain_percentchancemotorneuron, 0, 100, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_percentchancemotorneuron") settings->brain_mutate_percentchancemotorneuron = true;

		else if ( checkSwitch("--brain_percentchanceplasticneuron", settings->brain_percentchanceplasticneuron, 0, 100, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_percentchanceplasticneuron") settings->brain_mutate_percentchanceplasticneuron = true;

		else if ( checkSwitch("--brain_minplasticitystrengthen", settings->brain_minplasticitystrengthen, 1, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--brain_maxplasticitystrengthen", settings->brain_maxplasticitystrengthen, 1, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--brain_minplasticityweaken", settings->brain_minplasticityweaken, 1, 1000000, optind, argv) ) optind++;
		else if ( checkSwitch("--brain_maxplasticityweaken", settings->brain_maxplasticityweaken, 1, 1000000, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_plasticityfactors") settings->brain_mutate_plasticityfactors = true;

		else if ( checkSwitch("--brain_minfiringthreshold", settings->brain_minfiringthreshold, 1, 1000000, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_minfiringthreshold") settings->brain_mutate_minfiringthreshold = true;

		else if ( checkSwitch("--brain_maxfiringthreshold", settings->brain_maxfiringthreshold, 1, 1000000, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_maxfiringthreshold") settings->brain_mutate_maxfiringthreshold = true;

		else if ( checkSwitch("--brain_maxdendridicbranches", settings->brain_maxdendridicbranches, 1, 1000, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_maxdendridicbranches") settings->brain_mutate_maxdendridicbranches = true;

		else if ( checkSwitch("--brain_percentchanceconsistentsynapses", settings->brain_percentchanceconsistentsynapses, 0, 100, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_percentchanceconsistentsynapses") settings->brain_mutate_percentchanceconsistentsynapses = true;

		else if ( checkSwitch("--brain_percentchanceinhibitorysynapses", settings->brain_percentchanceinhibitorysynapses, 0, 100, optind, argv) ) optind++;

		else if (sw=="--brain_mutate_percentchanceinhibitorysynapses") settings->brain_mutate_percentchanceinhibitorysynapses = true;

		else if ( checkSwitch("--brain_percentchancesensorysynapse", settings->brain_percentchancesensorysynapse, 0, 100, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_percentchancesensorysynapse") settings->brain_mutate_percentchancesensorysynapse = true;

		else if ( checkSwitch("--brain_percentmutateeffectaddneuron", settings->brain_percentmutateeffectaddneuron, 0, 100, optind, argv) ) optind++;
		else if ( checkSwitch("--brain_percentmutateeffectremoveneuron", settings->brain_percentmutateeffectremoveneuron, 0, 100, optind, argv) ) optind++;
		else if ( checkSwitch("--brain_percentmutateeffectalterneuron", settings->brain_percentmutateeffectalterneuron, 0, 100, optind, argv) ) optind++;
		else if ( checkSwitch("--brain_percentmutateeffectaddsynapse", settings->brain_percentmutateeffectaddsynapse, 0, 100, optind, argv) ) optind++;
		else if ( checkSwitch("--brain_percentmutateeffectremovesynapse", settings->brain_percentmutateeffectremovesynapse, 0, 100, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_mutateeffects") settings->brain_mutate_mutateeffects = true;

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
	glwindow.create("Critterding beta8", 600, 600, 24, False);

		Evolution mainscene;

		mainscene.camera.position = Vector3f(-0.5f*settings->worldsize, -1.1f*settings->worldsize, -0.9f*settings->worldsize);
		mainscene.camera.sensitivity = settings->camerasensitivity;

		// calc some floats
		settings->critter_size = (float)settings->critter_sizeI / 100.0f;
		settings->critter_speed = (float)settings->critter_speedI / 1000.0f;
		settings->critter_sightrange = (float)settings->critter_sightrangeI / 10.0f;

		settings->food_size = (float)settings->food_sizeI / 100.0f;
		settings->corpse_size = (float)settings->corpse_sizeI / 100.0f;


		// global
		mainscene.world.resize(settings->worldsize);
		mainscene.world.startfoodamount(settings->startenergy);

		mainscene.world.printSettings();

		glwindow.runGLScene(mainscene);

	glwindow.destroy();
}
