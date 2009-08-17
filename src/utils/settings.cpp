#include "settings.h"

Settings* Settings::Instance () 
{
	static Settings t;
	return &t;
}

Settings::Settings()
{
	profileName			= "default";

	worldsizeX			= 16;
	worldsizeY			= 12;
		worldsizeMin			= 1;
		worldsizeMax			= 5000;
	startenergy			= 100;
		startenergyMin			= 0;
		startenergyMax			= 1000000;
	mincritters			= 10;
		mincrittersMin			= 0;
		mincrittersMax			= 1000;
	insertcritterevery		= 0;
		insertcrittereveryMin		= 0;
		insertcrittereveryMax		= 1000;
	retinasperrow			= 20;
		retinasperrowMin		= 1;
		retinasperrowMax		= 1000;
	camerasensitivity		= 20;
		camerasensitivityMin		= 1;
		camerasensitivityMax		= 1000;
	colormode			= 0;
		colormodeMin			= 0;
		colormodeMax			= 1;

	exit_if_empty			= false;
	autoload			= false;

	critter_maxlifetime		= 10000;
		critter_maxlifetimeMin		= 1;
		critter_maxlifetimeMax		= 1000000;
	critter_maxenergy		= 5000;
		critter_maxenergyMin		= 1;
		critter_maxenergyMax		= 1000000;
	critter_startenergy		= 2500;
		critter_startenergyMin		= 1;
		critter_startenergyMax		= 1000000;
	critter_procinterval		= 20;
		critter_procintervalMin		= 1;
		critter_procintervalMax		= 1000000;
	critter_minenergyproc		= 3000;
		critter_minenergyprocMin	= 0;
		critter_minenergyprocMax	= 1000000;
	critter_sightrangeI		= 70;
		critter_sightrangeIMin		= 1;
		critter_sightrangeIMax		= 1000;
	critter_retinasize		= 6;
		critter_retinasizeMin		= 1;
		critter_retinasizeMax		= 1000;
	critter_autosaveinterval	= 0;
		critter_autosaveintervalMin	= 0;
		critter_autosaveintervalMax	= 1000000;
	critter_killhalfat		= 1000;
		critter_killhalfatMin		= 2;
		critter_killhalfatMax		= 1000000;

	food_maxlifetime		= 2000;
		food_maxlifetimeMin		= 1;
		food_maxlifetimeMax		= 1000000;
	food_maxenergy			= 1000;
		food_maxenergyMin		= 1;
		food_maxenergyMax		= 1000000;
	food_sizeI			= 15;
		food_sizeIMin			= 1;
		food_sizeIMax			= 100;

	body_mutationrate		= 10;
		body_mutationrateMin		= 0;
		body_mutationrateMax		= 100;
	body_maxmutations		= 10;
		body_maxmutationsMin		= 1;
		body_maxmutationsMax		= 100;

	brain_mutationrate		= 10;
		brain_mutationrateMin		= 0;
		brain_mutationrateMax		= 100;
	brain_maxmutations		= 10;
		brain_maxmutationsMin		= 1;
		brain_maxmutationsMax		= 100;

	brain_maxneurons		= 1000;
		brain_maxneuronsMin		= 1;
		brain_maxneuronsMax		= 1000000;
	brain_minsynapses		= 1;
		brain_minsynapsesMin		= 1;
		brain_minsynapsesMax		= 1000000;
	brain_maxsynapses		= 100;
		brain_maxsynapsesMin		= 1;
		brain_maxsynapsesMax		= 1000000;
	brain_minneuronsatbuildtime	= 40;
		brain_minneuronsatbuildtimeMin	= 1;
		brain_minneuronsatbuildtimeMax	= 1000000;
	brain_maxneuronsatbuildtime	= 100;
		brain_maxneuronsatbuildtimeMin	= 1;
		brain_maxneuronsatbuildtimeMax	= 1000000;

	brain_minsynapsesatbuildtime			= 1;
		brain_minsynapsesatbuildtimeMin			= 1;
		brain_minsynapsesatbuildtimeMax			= 1000000;
		brain_mutate_minsynapsesatbuildtime		= false;

	brain_maxsynapsesatbuildtime			= 50;
		brain_maxsynapsesatbuildtimeMin			= 1;
		brain_maxsynapsesatbuildtimeMax			= 1000000;
		brain_mutate_maxsynapsesatbuildtime		= false;

	brain_percentchanceinhibitoryneuron		= 50;
		brain_percentchanceinhibitoryneuronMin		= 0;
		brain_percentchanceinhibitoryneuronMax		= 100;
		brain_mutate_percentchanceinhibitoryneuron	= false;

	brain_percentchancemotorneuron			= 50;
		brain_percentchancemotorneuronMin		= 0;
		brain_percentchancemotorneuronMax		= 100;
		brain_mutate_percentchancemotorneuron		= false;

	brain_percentchanceplasticneuron		= 20;
		brain_percentchanceplasticneuronMin		= 0;
		brain_percentchanceplasticneuronMax		= 100;
		brain_mutate_percentchanceplasticneuron		= false;

	brain_minplasticitystrengthen			= 100;
		brain_minplasticitystrengthenMin		= 1;
		brain_minplasticitystrengthenMax		= 1000000;
	brain_maxplasticitystrengthen			= 1000;
		brain_maxplasticitystrengthenMin		= 1;
		brain_maxplasticitystrengthenMax		= 1000000;
	brain_minplasticityweaken			= 1000;
		brain_minplasticityweakenMin			= 1;
		brain_minplasticityweakenMax			= 1000000;
	brain_maxplasticityweaken			= 10000;
		brain_maxplasticityweakenMin			= 1;
		brain_maxplasticityweakenMax			= 1000000;
		brain_mutate_plasticityfactors			= false;

	brain_minfiringthreshold			= 2;
		brain_minfiringthresholdMin			= 1;
		brain_minfiringthresholdMax			= 1000000;
		brain_mutate_minfiringthreshold			= false;

	brain_maxfiringthreshold			= 10;
		brain_maxfiringthresholdMin			= 1;
		brain_maxfiringthresholdMax			= 1000000;
		brain_mutate_maxfiringthreshold			= false;

	brain_maxdendridicbranches			= 3;
		brain_maxdendridicbranchesMin			= 1;
		brain_maxdendridicbranchesMax			= 1000;
		brain_mutate_maxdendridicbranches		= false;

	brain_percentchanceconsistentsynapses		= 0;
		brain_percentchanceconsistentsynapsesMin	= 0;
		brain_percentchanceconsistentsynapsesMax	= 100;
		brain_mutate_percentchanceconsistentsynapses	= false;

	brain_percentchanceinhibitorysynapses		= 50;
		brain_percentchanceinhibitorysynapsesMin	= 0;
		brain_percentchanceinhibitorysynapsesMax	= 100;
		brain_mutate_percentchanceinhibitorysynapses	= false;

	brain_percentchancesensorysynapse		= 20;
		brain_percentchancesensorysynapseMin		= 0;
		brain_percentchancesensorysynapseMax		= 100;
		brain_mutate_percentchancesensorysynapse	= false;

	brain_percentmutateeffectaddneuron		= 10;
		brain_percentmutateeffectaddneuronMin		= 0;
		brain_percentmutateeffectaddneuronMax		= 100;
	brain_percentmutateeffectremoveneuron		= 10;
		brain_percentmutateeffectremoveneuronMin	= 0;
		brain_percentmutateeffectremoveneuronMax	= 100;
	brain_percentmutateeffectalterneuron		= 20;
		brain_percentmutateeffectalterneuronMin		= 0;
		brain_percentmutateeffectalterneuronMax		= 100;
	brain_percentmutateeffectaddsynapse		= 29;
		brain_percentmutateeffectaddsynapseMin		= 0;
		brain_percentmutateeffectaddsynapseMax		= 100;
	brain_percentmutateeffectremovesynapse		= 29;
		brain_percentmutateeffectremovesynapseMin	= 0;
		brain_percentmutateeffectremovesynapseMax	= 100;
	brain_percentMutateEffectAlterMutable		= 1;
		brain_percentMutateEffectAlterMutableMin	= 0;
		brain_percentMutateEffectAlterMutableMax	= 100;

		brain_mutate_mutateeffects			= false;

	brain_costhavingneuron				= 50;
		brain_costhavingneuronMin			= 0;
		brain_costhavingneuronMax			= 1000000;
	brain_costfiringneuron				= 10;
		brain_costfiringneuronMin			= 0;
		brain_costfiringneuronMax			= 1000000;
	brain_costfiringmotorneuron			= 1000;
		brain_costfiringmotorneuronMin			= 0;
		brain_costfiringmotorneuronMax			= 1000000;
	brain_costhavingsynapse				= 1;
		brain_costhavingsynapseMin			= 0;
		brain_costhavingsynapseMax			= 1000000;

	info_critters = 0;
	info_food = 0;

	info_totalNeurons = 0;
	info_totalSynapses = 0;
	info_totalAdamDistance = 0;
	
	createHelpInfo();
}

void Settings::createHelpInfo()
{
	helpinfo << "STARTUP OPTIONS" << endl << endl;
	helpinfo << "  option           [default value]" << endl << endl;
	helpinfo << "  Global Settings" << endl;

	helpinfo << "  --profile                 [none]  Load a settings profile" << endl << endl;

	helpinfo << "  --worldsizeX                [" << worldsizeX << "]  Width of the world (" << worldsizeX << ")" << endl;
	helpinfo << "  --worldsizeY                [" << worldsizeY << "]  Depth of the world (" << worldsizeY << ")" << endl;
	helpinfo << "  --energy                   [" << startenergy << "]  Energy in the system: " << startenergy << "*food_maxenergy(" << food_maxenergy << ") = " << startenergy*food_maxenergy << "" << endl;
	helpinfo << "  --mincritters               [" << mincritters << "]  If less than " << mincritters << " critters are present, insert an adam" << endl;
	helpinfo << "  --retinasperrow             [" << retinasperrow << "]  Place " << retinasperrow << " retinas on a row (bottom left of window)" << endl;
	helpinfo << "  --camerasensitivity         [" << camerasensitivity << "]  Camera sensitivity" << endl;
	helpinfo << "  --exit-if-empty                   If set, the program will exit when no are left" << endl;
	helpinfo << "  --autoload                        If set, critters from the load directory will be loaded at startup" << endl;

	helpinfo << endl;
	helpinfo << "  Critter Settings" << endl;
	helpinfo << "  --critter_maxlifetime     [" << critter_maxlifetime << "]  Max amount of frames a critter can live" << endl;
	helpinfo << "  --critter_maxenergy       [" << critter_maxenergy << "]  Max amount of energy in a critter" << endl;
	helpinfo << "  --critter_startenergy     [" << critter_startenergy << "]  Starting amount of energy for a new critter" << endl;
	helpinfo << "  --critter_procinterval      [" << critter_procinterval << "]  Time (in frames) between procreations" << endl;
	helpinfo << "  --critter_minenergyproc   [" << critter_minenergyproc << "]  Min amount of energy required for procreation" << endl;

	helpinfo << "  --critter_sightrange        [" << critter_sightrangeI << "]  Distance a critter can see (" << critter_sightrangeI*10.0f << " = " << critter_sightrangeI << " floor squares)" << endl;
	helpinfo << "  --critter_retinasize         [" << critter_retinasize << "]  Resolution of critter's retina: " << critter_retinasize << "x" << critter_retinasize << "" << endl;
	helpinfo << "  --critter_autosaveinterval   [" << critter_autosaveinterval << "]  Save all critters every N seconds (0=disabled)" << endl;
	helpinfo << endl;
	helpinfo << "  Food Settings" << endl;
	helpinfo << "  --food_maxlifetime         [" << food_maxlifetime << "]  Maximum amount of frames food exists" << endl;
	helpinfo << "  --food_maxenergy          [" << food_maxenergy << "]  Maximum amount of energy in a food unit" << endl;
	helpinfo << "  --food_size                 [" << food_sizeI << "]  Size of a food unit" << endl;
	helpinfo << endl;

	helpinfo << "  Body Settings" << endl;
	helpinfo << "  --body_mutationrate      [" << body_mutationrate << "]  When a critter procreates there is a " << body_mutationrate << "% chance its body will mutate" << endl;
	helpinfo << "  --body_maxmutations       [" << body_maxmutations << "]  When a critters body mutates, it can do " << body_maxmutations << " mutations at maximum" << endl;

	helpinfo << endl;
	helpinfo << "  Brain Settings" << endl;
	helpinfo << "  --brain_mutationrate      [" << brain_mutationrate << "]  When a critter procreates there is a " << brain_mutationrate << "% chance its brain will mutate" << endl;
	helpinfo << "  --brain_maxmutations       [" << brain_maxmutations << "]  When a critters brain mutates, it can do " << brain_maxmutations << " mutations at maximum" << endl;

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
	helpinfo << "  --brain_percentMutateEffectAlterMutable         [" << brain_percentMutateEffectAlterMutable << "]  % chance of altering a mutable" << endl;

	helpinfo << "    --brain_mutate_mutateeffects                       If set, all values above will mutate" << endl;

	helpinfo << "  --brain_costhavingneuron                      [" << brain_costhavingneuron << "]  Energycost per frame for having a neuron" << endl;
	helpinfo << "  --brain_costfiringneuron                      [" << brain_costfiringneuron << "]  Energycost per frame for firing a neuron" << endl;
	helpinfo << "  --brain_costfiringmotorneuron                 [" << brain_costfiringmotorneuron << "]  Energycost per frame for firing a motorneuron" << endl;
	helpinfo << "  --brain_costhavingsynapse                      [" << brain_costhavingsynapse << "]  Energycost per frame for having a synapse" << endl;

}

void Settings::loadProfile(char* filename)
{
	cerr << "loading settins from '" << filename << "'" << endl;

	// nasty code for stripping dir names from the given profile name
	profileName = filename;
	string dirs("");
	dirs = parseH->Instance()->returnUntillStrip( "/", profileName );
	while ( !dirs.empty() )
	{
		dirs="";
		dirs = parseH->Instance()->returnUntillStrip( "/", profileName );
	}

	string content;
	if ( fileH.open( filename, content ) )
	{
		//cerr << "config file contains '" << content << "'" << endl;

		content.append("\n");
		string line = parseH->Instance()->returnUntillStrip( "\n", content );

		unsigned int uselesscounter = 0;
		while ( !content.empty() )
		{
			//cerr << "line contains '" << line << "'" << endl;

			// trim spaces
			while ( parseH->Instance()->beginMatchesStrip( " ", line ) || parseH->Instance()->beginMatchesStrip( "\t", line ) )
			{
				// nothing needed, i hate how this looks
			}

			// remove comment lines
			if ( parseH->Instance()->beginMatchesStrip( "#", line ) )
			{
				line="";
			}

			if ( !line.empty() )
			{

			if ( checkConfigFileValue("worldsizeX ", worldsizeX, worldsizeMin, worldsizeMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("worldsizeY ", worldsizeY, worldsizeMin, worldsizeMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("energy ", startenergy, startenergyMin, startenergyMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("mincritters ", mincritters, mincrittersMin, mincrittersMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("retinasperrow ", retinasperrow, retinasperrowMin, retinasperrowMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("camerasensitivity ", camerasensitivity, camerasensitivityMin, camerasensitivityMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("autoload", autoload, line) ) uselesscounter++;

			else if ( checkConfigFileValue("critter_maxlifetime ", critter_maxlifetime, critter_maxlifetimeMin, critter_maxlifetimeMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("critter_maxenergy ", critter_maxenergy, critter_maxenergyMin, critter_maxenergyMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("critter_startenergy ", critter_startenergy, critter_startenergyMin, critter_startenergyMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("critter_procinterval ", critter_procinterval, critter_procintervalMin, critter_procintervalMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("critter_minenergyproc ", critter_minenergyproc, critter_minenergyprocMin, critter_minenergyprocMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("critter_sightrange ", critter_sightrangeI, critter_sightrangeIMin, critter_sightrangeIMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("critter_retinasize ", critter_retinasize, critter_retinasizeMin, critter_retinasizeMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("critter_autosaveinterval ", critter_autosaveinterval, critter_autosaveintervalMin, critter_autosaveintervalMax, line) ) uselesscounter++;

			else if ( checkConfigFileValue("food_maxlifetime ", food_maxlifetime, food_maxlifetimeMin, food_maxlifetimeMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("food_maxenergy ", food_maxenergy, food_maxenergyMin, food_maxenergyMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("food_size ", food_sizeI, food_sizeIMin, food_sizeIMax, line) ) uselesscounter++;

			else if ( checkConfigFileValue("body_mutationrate ", body_mutationrate, body_mutationrateMin, body_mutationrateMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("body_maxmutations ", body_maxmutations, body_maxmutationsMin, body_maxmutationsMax, line) ) uselesscounter++;

			else if ( checkConfigFileValue("brain_mutationrate ", brain_mutationrate, brain_mutationrateMin, brain_mutationrateMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("brain_maxmutations ", brain_maxmutations, brain_maxmutationsMin, brain_maxmutationsMax, line) ) uselesscounter++;

			else if ( checkConfigFileValue("brain_maxneurons ", brain_maxneurons, brain_maxneuronsMin, brain_maxneuronsMax, line) ) uselesscounter++;

			else if ( checkConfigFileValue("brain_minsynapses ", brain_minsynapses, brain_minsynapsesMin, brain_minsynapsesMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("brain_maxsynapses ", brain_maxsynapses, brain_maxsynapsesMin, brain_maxsynapsesMax, line) ) uselesscounter++;

			else if ( checkConfigFileValue("brain_minneuronsatbuildtime ", brain_minneuronsatbuildtime, brain_minneuronsatbuildtimeMin, brain_minneuronsatbuildtimeMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("brain_maxneuronsatbuildtime ", brain_maxneuronsatbuildtime, brain_maxneuronsatbuildtimeMin, brain_maxneuronsatbuildtimeMax, line) ) uselesscounter++;

			else if ( checkConfigFileValue("brain_minsynapsesatbuildtime ", brain_minsynapsesatbuildtime, brain_minsynapsesatbuildtimeMin, brain_minsynapsesatbuildtimeMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("brain_mutate_minsynapsesatbuildtime", brain_mutate_minsynapsesatbuildtime, line) ) uselesscounter++;

			else if ( checkConfigFileValue("brain_maxsynapsesatbuildtime ", brain_maxsynapsesatbuildtime, brain_maxsynapsesatbuildtimeMin, brain_maxsynapsesatbuildtimeMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("brain_mutate_maxsynapsesatbuildtime", brain_mutate_maxsynapsesatbuildtime, line) ) uselesscounter++;

			else if ( checkConfigFileValue("brain_percentchanceinhibitoryneuron ", brain_percentchanceinhibitoryneuron, brain_percentchanceinhibitoryneuronMin, brain_percentchanceinhibitoryneuronMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("brain_mutate_percentchanceinhibitoryneuron", brain_mutate_percentchanceinhibitoryneuron, line) ) uselesscounter++;

			else if ( checkConfigFileValue("brain_percentchancemotorneuron ", brain_percentchancemotorneuron, brain_percentchancemotorneuronMin, brain_percentchancemotorneuronMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("brain_mutate_percentchancemotorneuron", brain_mutate_percentchancemotorneuron, line) ) uselesscounter++;

			else if ( checkConfigFileValue("brain_percentchanceplasticneuron ", brain_percentchanceplasticneuron, brain_percentchanceplasticneuronMin, brain_percentchanceplasticneuronMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("brain_mutate_percentchanceplasticneuron", brain_mutate_percentchanceplasticneuron, line) ) uselesscounter++;

			else if ( checkConfigFileValue("brain_minplasticitystrengthen ", brain_minplasticitystrengthen, brain_minplasticitystrengthenMin, brain_minplasticitystrengthenMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("brain_maxplasticitystrengthen ", brain_maxplasticitystrengthen, brain_maxplasticitystrengthenMin, brain_maxplasticitystrengthenMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("brain_minplasticityweaken ", brain_minplasticityweaken, brain_minplasticityweakenMin, brain_minplasticityweakenMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("brain_maxplasticityweaken ", brain_maxplasticityweaken, brain_maxplasticityweakenMin, brain_maxplasticityweakenMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("brain_mutate_plasticityfactors", brain_mutate_plasticityfactors, line) ) uselesscounter++;

			else if ( checkConfigFileValue("brain_minfiringthreshold ", brain_minfiringthreshold, brain_minfiringthresholdMin, brain_minfiringthresholdMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("brain_mutate_minfiringthreshold", brain_mutate_minfiringthreshold, line) ) uselesscounter++;

			else if ( checkConfigFileValue("brain_maxfiringthreshold ", brain_maxfiringthreshold, brain_maxfiringthresholdMin, brain_maxfiringthresholdMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("brain_mutate_maxfiringthreshold", brain_mutate_maxfiringthreshold, line) ) uselesscounter++;

			else if ( checkConfigFileValue("brain_maxdendridicbranches ", brain_maxdendridicbranches, brain_maxdendridicbranchesMin, brain_maxdendridicbranchesMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("brain_mutate_maxdendridicbranches", brain_mutate_maxdendridicbranches, line) ) uselesscounter++;

			else if ( checkConfigFileValue("brain_percentchanceconsistentsynapses ", brain_percentchanceconsistentsynapses, brain_percentchanceconsistentsynapsesMin, brain_percentchanceconsistentsynapsesMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("brain_mutate_percentchanceconsistentsynapses", brain_mutate_percentchanceconsistentsynapses, line) ) uselesscounter++;

			else if ( checkConfigFileValue("brain_percentchanceinhibitorysynapses ", brain_percentchanceinhibitorysynapses, brain_percentchanceinhibitorysynapsesMin, brain_percentchanceinhibitorysynapsesMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("brain_mutate_percentchanceinhibitorysynapses", brain_mutate_percentchanceinhibitorysynapses, line) ) uselesscounter++;

			else if ( checkConfigFileValue("brain_percentchancesensorysynapse ", brain_percentchancesensorysynapse, brain_percentchancesensorysynapseMin, brain_percentchancesensorysynapseMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("brain_mutate_percentchancesensorysynapse", brain_mutate_percentchancesensorysynapse, line) ) uselesscounter++;

			else if ( checkConfigFileValue("brain_percentmutateeffectaddneuron ", brain_percentmutateeffectaddneuron, brain_percentmutateeffectaddneuronMin, brain_percentmutateeffectaddneuronMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("brain_percentmutateeffectremoveneuron ", brain_percentmutateeffectremoveneuron, brain_percentmutateeffectremoveneuronMin, brain_percentmutateeffectremoveneuronMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("brain_percentmutateeffectalterneuron ", brain_percentmutateeffectalterneuron, brain_percentmutateeffectalterneuronMin, brain_percentmutateeffectalterneuronMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("brain_percentmutateeffectaddsynapse ", brain_percentmutateeffectaddsynapse, brain_percentmutateeffectaddsynapseMin, brain_percentmutateeffectaddsynapseMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("brain_percentmutateeffectremovesynapse ", brain_percentmutateeffectremovesynapse, brain_percentmutateeffectremovesynapseMin, brain_percentmutateeffectremovesynapseMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("brain_percentMutateEffectAlterMutable", brain_percentMutateEffectAlterMutable, brain_percentMutateEffectAlterMutableMin, brain_percentMutateEffectAlterMutableMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("brain_mutate_mutateeffects", brain_mutate_mutateeffects, line) ) uselesscounter++;

			else if ( checkConfigFileValue("brain_costhavingneuron", brain_costhavingneuron, brain_costhavingneuronMin, brain_costhavingneuronMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("brain_costfiringneuron", brain_costfiringneuron, brain_costfiringneuronMin, brain_costfiringneuronMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("brain_costfiringmotorneuron", brain_costfiringmotorneuron, brain_costfiringmotorneuronMin, brain_costfiringmotorneuronMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("brain_costhavingsynapse", brain_costhavingsynapse, brain_costhavingsynapseMin, brain_costhavingsynapseMax, line) ) uselesscounter++;

			else
			{
				cout << "Unknown option in profile: " << line << endl;
				exit(1);
			}

			}

			line = parseH->Instance()->returnUntillStrip( "\n", content );
		}
	}
	else
	{
		cerr << "cannot open profile '" << filename << "'" << endl;
		exit(1);
	}

}

void Settings::doCommandLineOptions(int argc, char *argv[])
{
	int optind=1;
	// decode arguments
	while ((optind < argc) && (argv[optind][0]=='-'))
	{
		string sw = argv[optind];

	// Global Settings

		if (sw=="--profile")
		{
			if ( argv[optind+1] )
			{
				optind++;
				loadProfile(argv[optind]);
			}
	        }

		else if ( checkSwitch("--worldsizeX", worldsizeX, worldsizeMin, worldsizeMax, optind, argv) ) optind++;
		else if ( checkSwitch("--worldsizeY", worldsizeY, worldsizeMin, worldsizeMax, optind, argv) ) optind++;
		else if ( checkSwitch("--energy", startenergy, startenergyMin, startenergyMax, optind, argv) ) optind++;
		else if ( checkSwitch("--mincritters", mincritters, mincrittersMin, mincrittersMax, optind, argv) ) optind++;
		else if ( checkSwitch("--retinasperrow", retinasperrow, retinasperrowMin, retinasperrowMax, optind, argv) ) optind++;
		else if ( checkSwitch("--camerasensitivity", camerasensitivity, camerasensitivityMin, camerasensitivityMax, optind, argv) ) optind++;
		else if ( sw=="--exit-if-empty") exit_if_empty = true;
		else if ( sw=="--autoload") autoload = true;

	// Critter Settings

		else if ( checkSwitch("--critter_maxlifetime", critter_maxlifetime, critter_maxlifetimeMin, critter_maxlifetimeMax, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_maxenergy", critter_maxenergy, critter_maxenergyMin, critter_maxenergyMax, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_startenergy", critter_startenergy, critter_startenergyMin, critter_startenergyMax, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_procinterval", critter_procinterval, critter_procintervalMin, critter_procintervalMax, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_minenergyproc", critter_minenergyproc, critter_minenergyprocMin, critter_minenergyprocMax, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_sightrange", critter_sightrangeI, critter_sightrangeIMin, critter_sightrangeIMax, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_retinasize", critter_retinasize, critter_retinasizeMin, critter_retinasizeMax, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_autosaveinterval", critter_autosaveinterval, critter_autosaveintervalMin, critter_autosaveintervalMax, optind, argv) ) optind++;

	// Food Settings

		else if ( checkSwitch("--food_maxlifetime", food_maxlifetime, food_maxlifetimeMin, food_maxlifetimeMax, optind, argv) ) optind++;
		else if ( checkSwitch("--food_maxenergy", food_maxenergy, food_maxenergyMin, food_maxenergyMax, optind, argv) ) optind++;
		else if ( checkSwitch("--food_size", food_sizeI, food_sizeIMin, food_sizeIMax, optind, argv) ) optind++;

	// Body Settings

		else if ( checkSwitch("--body_mutationrate", body_mutationrate, body_mutationrateMin, body_mutationrateMax, optind, argv) ) optind++;
		else if ( checkSwitch("--body_maxmutations", body_maxmutations, body_maxmutationsMin, body_maxmutationsMax, optind, argv) ) optind++;

	// Brain Settings

		else if ( checkSwitch("--brain_mutationrate", brain_mutationrate, brain_mutationrateMin, brain_mutationrateMax, optind, argv) ) optind++;
		else if ( checkSwitch("--brain_maxmutations", brain_maxmutations, brain_maxmutationsMin, brain_maxmutationsMax, optind, argv) ) optind++;

		else if ( checkSwitch("--brain_maxneurons", brain_maxneurons, brain_maxneuronsMin, brain_maxneuronsMax, optind, argv) ) optind++;

		else if ( checkSwitch("--brain_minsynapses", brain_minsynapses, brain_minsynapsesMin, brain_minsynapsesMax, optind, argv) ) optind++;
		else if ( checkSwitch("--brain_maxsynapses", brain_maxsynapses, brain_maxsynapsesMin, brain_maxsynapsesMax, optind, argv) ) optind++;

		else if ( checkSwitch("--brain_minneuronsatbuildtime", brain_minneuronsatbuildtime, brain_minneuronsatbuildtimeMin, brain_minneuronsatbuildtimeMax, optind, argv) ) optind++;
		else if ( checkSwitch("--brain_maxneuronsatbuildtime", brain_maxneuronsatbuildtime, brain_maxneuronsatbuildtimeMin, brain_maxneuronsatbuildtimeMax, optind, argv) ) optind++;

		else if ( checkSwitch("--brain_minsynapsesatbuildtime", brain_minsynapsesatbuildtime, brain_minsynapsesatbuildtimeMin, brain_minsynapsesatbuildtimeMax, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_minsynapsesatbuildtime") brain_mutate_minsynapsesatbuildtime = true;

		else if ( checkSwitch("--brain_maxsynapsesatbuildtime", brain_maxsynapsesatbuildtime, brain_maxsynapsesatbuildtimeMin, brain_maxsynapsesatbuildtimeMax, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_maxsynapsesatbuildtime") brain_mutate_maxsynapsesatbuildtime = true;

		else if ( checkSwitch("--brain_percentchanceinhibitoryneuron", brain_percentchanceinhibitoryneuron, brain_percentchanceinhibitoryneuronMin, brain_percentchanceinhibitoryneuronMax, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_percentchanceinhibitoryneuron") brain_mutate_percentchanceinhibitoryneuron = true;

		else if ( checkSwitch("--brain_percentchancemotorneuron", brain_percentchancemotorneuron, brain_percentchancemotorneuronMin, brain_percentchancemotorneuronMax, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_percentchancemotorneuron") brain_mutate_percentchancemotorneuron = true;

		else if ( checkSwitch("--brain_percentchanceplasticneuron", brain_percentchanceplasticneuron, brain_percentchanceplasticneuronMin, brain_percentchanceplasticneuronMax, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_percentchanceplasticneuron") brain_mutate_percentchanceplasticneuron = true;

		else if ( checkSwitch("--brain_minplasticitystrengthen", brain_minplasticitystrengthen, brain_minplasticitystrengthenMin, brain_minplasticitystrengthenMax, optind, argv) ) optind++;
		else if ( checkSwitch("--brain_maxplasticitystrengthen", brain_maxplasticitystrengthen, brain_maxplasticitystrengthenMin, brain_maxplasticitystrengthenMax, optind, argv) ) optind++;
		else if ( checkSwitch("--brain_minplasticityweaken", brain_minplasticityweaken, brain_minplasticityweakenMin, brain_minplasticityweakenMax, optind, argv) ) optind++;
		else if ( checkSwitch("--brain_maxplasticityweaken", brain_maxplasticityweaken, brain_maxplasticityweakenMin, brain_maxplasticityweakenMax, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_plasticityfactors") brain_mutate_plasticityfactors = true;

		else if ( checkSwitch("--brain_minfiringthreshold", brain_minfiringthreshold, brain_minfiringthresholdMin, brain_minfiringthresholdMax, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_minfiringthreshold") brain_mutate_minfiringthreshold = true;

		else if ( checkSwitch("--brain_maxfiringthreshold", brain_maxfiringthreshold, brain_maxfiringthresholdMin, brain_maxfiringthresholdMax, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_maxfiringthreshold") brain_mutate_maxfiringthreshold = true;

		else if ( checkSwitch("--brain_maxdendridicbranches", brain_maxdendridicbranches, brain_maxdendridicbranchesMin, brain_maxdendridicbranchesMax, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_maxdendridicbranches") brain_mutate_maxdendridicbranches = true;

		else if ( checkSwitch("--brain_percentchanceconsistentsynapses", brain_percentchanceconsistentsynapses, brain_percentchanceconsistentsynapsesMin, brain_percentchanceconsistentsynapsesMax, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_percentchanceconsistentsynapses") brain_mutate_percentchanceconsistentsynapses = true;

		else if ( checkSwitch("--brain_percentchanceinhibitorysynapses", brain_percentchanceinhibitorysynapses, brain_percentchanceinhibitorysynapsesMin, brain_percentchanceinhibitorysynapsesMax, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_percentchanceinhibitorysynapses") brain_mutate_percentchanceinhibitorysynapses = true;

		else if ( checkSwitch("--brain_percentchancesensorysynapse", brain_percentchancesensorysynapse, brain_percentchancesensorysynapseMin, brain_percentchancesensorysynapseMax, optind, argv) ) optind++;
		else if (sw=="--brain_mutate_percentchancesensorysynapse") brain_mutate_percentchancesensorysynapse = true;

		else if ( checkSwitch("--brain_percentmutateeffectaddneuron", brain_percentmutateeffectaddneuron, brain_percentmutateeffectaddneuronMin, brain_percentmutateeffectaddneuronMax, optind, argv) ) optind++;
		else if ( checkSwitch("--brain_percentmutateeffectremoveneuron", brain_percentmutateeffectremoveneuron, brain_percentmutateeffectremoveneuronMin, brain_percentmutateeffectremoveneuronMax, optind, argv) ) optind++;
		else if ( checkSwitch("--brain_percentmutateeffectalterneuron", brain_percentmutateeffectalterneuron, brain_percentmutateeffectalterneuronMin, brain_percentmutateeffectalterneuronMax, optind, argv) ) optind++;
		else if ( checkSwitch("--brain_percentmutateeffectaddsynapse", brain_percentmutateeffectaddsynapse, brain_percentmutateeffectaddsynapseMin, brain_percentmutateeffectaddsynapseMax, optind, argv) ) optind++;
		else if ( checkSwitch("--brain_percentmutateeffectremovesynapse", brain_percentmutateeffectremovesynapse, brain_percentmutateeffectremovesynapseMin, brain_percentmutateeffectremovesynapseMax, optind, argv) ) optind++;
		else if ( checkSwitch("--brain_percentMutateEffectAlterMutable", brain_percentMutateEffectAlterMutable, brain_percentMutateEffectAlterMutableMin, brain_percentMutateEffectAlterMutableMax, optind, argv) ) optind++;

		else if (sw=="--brain_mutate_mutateeffects") brain_mutate_mutateeffects = true;

		else if ( checkSwitch("--brain_costhavingneuron", brain_costhavingneuron, brain_costhavingneuronMin, brain_costhavingneuronMax, optind, argv) ) optind++;
		else if ( checkSwitch("--brain_costfiringneuron", brain_costfiringneuron, brain_costfiringneuronMin, brain_costfiringneuronMax, optind, argv) ) optind++;
		else if ( checkSwitch("--brain_costfiringmotorneuron", brain_costfiringmotorneuron, brain_costfiringmotorneuronMin, brain_costfiringmotorneuronMax, optind, argv) ) optind++;
		else if ( checkSwitch("--brain_costhavingsynapse", brain_costhavingsynapse, brain_costhavingsynapseMin, brain_costhavingsynapseMax, optind, argv) ) optind++;

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

	
	// finalizing: calc some floats
		critter_sightrange = (float)critter_sightrangeI / 10.0f;

		food_size = (float)food_sizeI / 100.0f;
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

bool Settings::checkConfigFileValue(string matchsw, unsigned int &var, unsigned int min, unsigned int max, string &line)
{
	if ( parseH->Instance()->beginMatchesStrip( matchsw, line ) )
	{
		unsigned int value;
		if(EOF == sscanf(line.c_str(), "%d", &value)) cerr << "error in config file" << endl;
//		line.clear();

			if ( value >= min && value <= max )
			{
				var = value;
				return true;
			}
			else
			{
				cerr << ",'" << line << "' current value: " << value << endl;
				cerr << matchsw << " expects a value that is >=" << min << " and <=" << max << ", current value: " << value << endl;
				exit(1);
			}


		return true;
	}
	else return false;
}

bool Settings::checkConfigFileValue(string matchsw, bool &var, string &line)
{
	if ( parseH->Instance()->beginMatchesStrip( matchsw, line ) )
	{
		unsigned int value = 0;
		bool notpassed = false;
		if(EOF == sscanf(line.c_str(), "%d", &value)) notpassed = true;

		line.clear();
		if ( notpassed || value == 1 )
			var=true;
		else
			var=false;

		return true;
	}
	else return false;
}

void Settings::printSettings()
{
	cout << endl << "CURRENT SETTINGS" << endl << endl;
	cerr << "profile " << profileName << endl;
	cerr << "worldsizeX " << worldsizeX << endl;
	cerr << "worldsizeY " << worldsizeY << endl;
	cerr << "energy " << freeEnergyInfo/food_maxenergy << endl;
	cerr << "mincritters " << mincritters << endl;
	cerr << "retinasperrow " << retinasperrow << endl;
	cerr << "camerasensitivity " << camerasensitivity << endl;
// 	cerr << "walltype " << walltype << endl;
// 	cerr << "spreadertype " << spreadertype << endl;
	cerr << "exit-if-empty " << exit_if_empty << endl << endl;
	cerr << "autoload " << autoload << endl << endl;

	cerr << "critter_maxlifetime " << critter_maxlifetime << endl;
	cerr << "critter_maxenergy " << critter_maxenergy << endl;
	cerr << "critter_startenergy " << critter_startenergy << endl;
	cerr << "critter_procinterval " << critter_procinterval << endl;
// 	cerr << "critter_fireinterval " << critter_fireinterval << endl;
	cerr << "critter_minenergyproc " << critter_minenergyproc << endl;
// 	cerr << "critter_minenergyfire " << critter_minenergyfire << endl;
// 	cerr << "critter_firecost " << critter_firecost << endl;
// 	cerr << "critter_size " << critter_sizeI << endl;
// 	cerr << "critter_speed " << critter_speedI << endl;
	cerr << "critter_sightrange " << critter_sightrangeI << endl;
	cerr << "critter_retinasize " << critter_retinasize << endl;
// 	cerr << "critter_percentchangetype " << critter_percentchangetype << endl;
// 	cerr << "critter_flipnewborns " << critter_flipnewborns << endl;
// 	cerr << "critter_randomrotatenewborns " << critter_randomrotatenewborns << endl;
// 	cerr << "critter_enablecarrying " << critter_enablecarrying << endl;
	cerr << "critter_autosaveinterval  " << critter_autosaveinterval << endl << endl;

	cerr << "food_maxlifetime  " << food_maxlifetime << endl;
	cerr << "food_maxenergy  " << food_maxenergy << endl;
	cerr << "food_size  " << food_sizeI << endl << endl;

// 	cerr << "corpse_disable  " << corpse_disable << endl;
// 	cerr << "corpse_maxlifetime  " << corpse_maxlifetime << endl;
// 	cerr << "corpse_maxenergy  " << corpse_maxenergy << endl;
// 	cerr << "corpse_size  " << corpse_sizeI << endl << endl;

	cerr << "body_mutationrate " << body_mutationrate << endl;
	cerr << "body_maxmutations " << body_maxmutations << endl;

	cerr << "brain_mutationrate " << brain_mutationrate << endl;
	cerr << "brain_maxmutations " << brain_maxmutations << endl;

	cerr << "brain_maxneurons  " << brain_maxneurons << endl;
	cerr << "brain_minsynapses  " << brain_minsynapses << endl;
	cerr << "brain_maxsynapses  " << brain_maxsynapses << endl;
	cerr << "brain_minneuronsatbuildtime  " << brain_minneuronsatbuildtime << endl;
	cerr << "brain_maxneuronsatbuildtime  " << brain_maxneuronsatbuildtime << endl;
	cerr << "brain_minsynapsesatbuildtime  " << brain_minsynapsesatbuildtime << endl;
	cerr << "brain_mutate_minsynapsesatbuildtime  " << brain_mutate_minsynapsesatbuildtime << endl;
	cerr << "brain_maxsynapsesatbuildtime  " << brain_maxsynapsesatbuildtime << endl;
	cerr << "brain_mutate_maxsynapsesatbuildtime  " << brain_mutate_maxsynapsesatbuildtime << endl;
	cerr << "brain_percentchanceinhibitoryneuron  " << brain_percentchanceinhibitoryneuron << endl;
	cerr << "brain_mutate_percentchanceinhibitoryneuron  " << brain_mutate_percentchanceinhibitoryneuron << endl;
	cerr << "brain_percentchancemotorneuron  " << brain_percentchancemotorneuron << endl;
	cerr << "brain_mutate_percentchancemotorneuron  " << brain_mutate_percentchancemotorneuron << endl;
	cerr << "brain_percentchanceplasticneuron  " << brain_percentchanceplasticneuron << endl;
	cerr << "brain_mutate_percentchanceplasticneuron  " << brain_mutate_percentchanceplasticneuron << endl;
	cerr << "brain_minplasticitystrengthen  " << brain_minplasticitystrengthen << endl;
	cerr << "brain_maxplasticitystrengthen  " << brain_maxplasticitystrengthen << endl;
	cerr << "brain_minplasticityweaken  " << brain_minplasticityweaken << endl;
	cerr << "brain_maxplasticityweaken  " << brain_maxplasticityweaken << endl;
	cerr << "brain_mutate_plasticityfactors  " << brain_mutate_plasticityfactors << endl;
	cerr << "brain_minfiringthreshold  " << brain_minfiringthreshold << endl;
	cerr << "brain_mutate_minfiringthreshold  " << brain_mutate_minfiringthreshold << endl;
	cerr << "brain_maxfiringthreshold  " << brain_maxfiringthreshold << endl;
	cerr << "brain_mutate_maxfiringthreshold  " << brain_mutate_maxfiringthreshold << endl;
	cerr << "brain_maxdendridicbranches  " << brain_maxdendridicbranches << endl;
	cerr << "brain_mutate_maxdendridicbranches  " << brain_mutate_maxdendridicbranches << endl;
	cerr << "brain_percentchanceconsistentsynapses  " << brain_percentchanceconsistentsynapses << endl;
	cerr << "brain_mutate_percentchanceconsistentsynapses  " << brain_mutate_percentchanceconsistentsynapses << endl;
	cerr << "brain_percentchanceinhibitorysynapses  " << brain_percentchanceinhibitorysynapses << endl;
	cerr << "brain_mutate_percentchanceinhibitorysynapses  " << brain_mutate_percentchanceinhibitorysynapses << endl;
	cerr << "brain_percentchancesensorysynapse  " << brain_percentchancesensorysynapse << endl;
	cerr << "brain_mutate_percentchancesensorysynapse  " << brain_mutate_percentchancesensorysynapse << endl;
	cerr << "brain_percentmutateeffectaddneuron  " << brain_percentmutateeffectaddneuron << endl;
	cerr << "brain_percentmutateeffectremoveneuron  " << brain_percentmutateeffectremoveneuron << endl;
	cerr << "brain_percentmutateeffectalterneuron  " << brain_percentmutateeffectalterneuron << endl;
	cerr << "brain_percentmutateeffectaddsynapse  " << brain_percentmutateeffectaddsynapse << endl;
	cerr << "brain_percentmutateeffectremovesynapse  " << brain_percentmutateeffectremovesynapse << endl;
	cerr << "brain_percentMutateEffectAlterMutable  " << brain_percentMutateEffectAlterMutable << endl;
	cerr << "brain_mutate_mutateeffects  " << brain_mutate_mutateeffects << endl;

	cerr << "brain_costhavingneuron  " << brain_costhavingneuron << endl;
	cerr << "brain_costfiringneuron  " << brain_costfiringneuron << endl;
	cerr << "brain_costfiringmotorneuron  " << brain_costfiringmotorneuron << endl;
	cerr << "brain_costhavingsynapse  " << brain_costhavingsynapse << endl;
	cout << endl;
}
