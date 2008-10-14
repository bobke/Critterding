#include "settings.h"

Settings* Settings::Instance () 
{
	static Settings t;
	return &t;
}

Settings::Settings()
{
	profileName			= "default";

	worldsize			= 25;
		worldsizeMin			= 1;
		worldsizeMax			= 5000;
	startenergy			= 500;
		startenergyMin			= 0;
		startenergyMax			= 1000000;
	mincritters			= 10;
		mincrittersMin			= 0;
		mincrittersMax			= 1000;
	retinasperrow			= 20;
		retinasperrowMin		= 1;
		retinasperrowMax		= 1000;
	camerasensitivity		= 10;
		camerasensitivityMin		= 1;
		camerasensitivityMax		= 1000;
	exit_if_empty			= false;

	critter_maxlifetime		= 1000;
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
	critter_fireinterval		= 10;
		critter_fireintervalMin		= 0;
		critter_fireintervalMax		= 1000000;
	critter_minenergyproc		= 3000;
		critter_minenergyprocMin	= 0;
		critter_minenergyprocMax	= 1000000;
	critter_minenergyfire		= 1;
		critter_minenergyfireMin	= 0;
		critter_minenergyfireMax	= 1000000;
	critter_sizeI			= 10;
		critter_sizeIMin		= 1;
		critter_sizeIMax		= 100;
	critter_speedI			= 50;
		critter_speedIMin		= 1;
		critter_speedIMax		= 1000;
	critter_sightrangeI		= 40;
		critter_sightrangeIMin		= 1;
		critter_sightrangeIMax		= 1000;
	critter_retinasize		= 7;
		critter_retinasizeMin		= 1;
		critter_retinasizeMax		= 1000;
	critter_colorneurons		= 3;
		critter_colorneuronsMin		= 2;
		critter_colorneuronsMax		= 100;
	critter_mutationrate		= 10;
		critter_mutationrateMin		= 0;
		critter_mutationrateMax		= 100;
	critter_maxmutations		= 10;
		critter_maxmutationsMin		= 1;
		critter_maxmutationsMax		= 100;
	critter_percentchangetype	= 0;
		critter_percentchangetypeMin	= 0;
		critter_percentchangetypeMax	= 100;
	critter_flipnewborns		= false;
	critter_randomrotatenewborns	= false;
	critter_autosaveinterval	= 0;
		critter_autosaveintervalMin	= 0;
		critter_autosaveintervalMax	= 1000000;

	food_maxlifetime		= 500;
		food_maxlifetimeMin		= 1;
		food_maxlifetimeMax		= 1000000;
	food_maxenergy			= 1000;
		food_maxenergyMin		= 1;
		food_maxenergyMax		= 1000000;
	food_sizeI			= 15;
		food_sizeIMin			= 1;
		food_sizeIMax			= 100;

	corpse_enable			= false;
	corpse_maxlifetime		= 1200;
		corpse_maxlifetimeMin		= 1;
		corpse_maxlifetimeMax		= 1000000;
	corpse_maxenergy		= 2500;
		corpse_maxenergyMin		= 1;
		corpse_maxenergyMax		= 1000000;
	corpse_sizeI			= 15;
		corpse_sizeIMin			= 1;
		corpse_sizeIMax			= 100;

	food_lifeenergyratio		= 0;
	corpse_lifeenergyratio		= 0;



	brain_maxneurons		= 1000;
		brain_maxneuronsMin		= 1;
		brain_maxneuronsMax		= 1000000;
	brain_minsynapses		= 1;
		brain_minsynapsesMin		= 1;
		brain_minsynapsesMax		= 1000000;
	brain_maxsynapses		= 100;
		brain_maxsynapsesMin		= 1;
		brain_maxsynapsesMax		= 1000000;
	brain_minneuronsatbuildtime	= 20;
		brain_minneuronsatbuildtimeMin	= 1;
		brain_minneuronsatbuildtimeMax	= 1000000;
	brain_maxneuronsatbuildtime	= 30;
		brain_maxneuronsatbuildtimeMin	= 1;
		brain_maxneuronsatbuildtimeMax	= 1000000;

	brain_minsynapsesatbuildtime			= 1;
		brain_minsynapsesatbuildtimeMin			= 1;
		brain_minsynapsesatbuildtimeMax			= 1000000;
		brain_mutate_minsynapsesatbuildtime		= false;

	brain_maxsynapsesatbuildtime			= 60;
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

	brain_percentchanceconsistentsynapses		= 50;
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

			if ( checkConfigFileValue("worldsize ", worldsize, worldsizeMin, worldsizeMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("energy ", startenergy, startenergyMin, startenergyMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("mincritters ", mincritters, mincrittersMin, mincrittersMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("retinasperrow ", retinasperrow, retinasperrowMin, retinasperrowMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("camerasensitivity ", camerasensitivity, camerasensitivityMin, camerasensitivityMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("exit-if-empty", exit_if_empty, line) ) uselesscounter++;

			else if ( checkConfigFileValue("critter_maxlifetime ", critter_maxlifetime, critter_maxlifetimeMin, critter_maxlifetimeMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("critter_maxenergy ", critter_maxenergy, critter_maxenergyMin, critter_maxenergyMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("critter_startenergy ", critter_startenergy, critter_startenergyMin, critter_startenergyMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("critter_procinterval ", critter_procinterval, critter_procintervalMin, critter_procintervalMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("critter_fireinterval ", critter_fireinterval, critter_fireintervalMin, critter_fireintervalMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("critter_minenergyproc ", critter_minenergyproc, critter_minenergyprocMin, critter_minenergyprocMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("critter_minenergyfire ", critter_minenergyfire, critter_minenergyfireMin, critter_minenergyfireMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("critter_size ", critter_sizeI, critter_sizeIMin, critter_sizeIMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("critter_speed ", critter_speedI, critter_speedIMin, critter_speedIMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("critter_sightrange ", critter_sightrangeI, critter_sightrangeIMin, critter_sightrangeIMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("critter_retinasize ", critter_retinasize, critter_retinasizeMin, critter_retinasizeMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("critter_colorneurons ", critter_colorneurons, critter_colorneuronsMin, critter_colorneuronsMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("critter_mutationrate ", critter_mutationrate, critter_mutationrateMin, critter_mutationrateMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("critter_maxmutations ", critter_maxmutations, critter_maxmutationsMin, critter_maxmutationsMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("critter_percentchangetype ", critter_percentchangetype, critter_percentchangetypeMin, critter_percentchangetypeMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("critter_flipnewborns", critter_flipnewborns, line) ) uselesscounter++;
			else if ( checkConfigFileValue("critter_randomrotatenewborns", critter_randomrotatenewborns, line) ) uselesscounter++;
			else if ( checkConfigFileValue("critter_autosaveinterval ", critter_autosaveinterval, critter_autosaveintervalMin, critter_autosaveintervalMax, line) ) uselesscounter++;

			else if ( checkConfigFileValue("food_maxlifetime ", food_maxlifetime, food_maxlifetimeMin, food_maxlifetimeMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("food_maxenergy ", food_maxenergy, food_maxenergyMin, food_maxenergyMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("food_size ", food_sizeI, food_sizeIMin, food_sizeIMax, line) ) uselesscounter++;

			else if ( checkConfigFileValue("corpse_enable", corpse_enable, line) ) uselesscounter++;
			else if ( checkConfigFileValue("corpse_maxlifetime ", corpse_maxlifetime, corpse_maxlifetimeMin, corpse_maxlifetimeMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("corpse_maxenergy ", corpse_maxenergy, corpse_maxenergyMin, corpse_maxenergyMax, line) ) uselesscounter++;
			else if ( checkConfigFileValue("corpse_size ", corpse_sizeI, corpse_sizeIMin, corpse_sizeIMax, line) ) uselesscounter++;

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
			else if ( checkConfigFileValue("brain_mutate_mutateeffects", brain_mutate_mutateeffects, line) ) uselesscounter++;

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

		else if (sw=="--small")
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

		else if ( checkSwitch("--worldsize", worldsize, worldsizeMin, worldsizeMax, optind, argv) ) optind++;
		else if ( checkSwitch("--energy", startenergy, startenergyMin, startenergyMax, optind, argv) ) optind++;
		else if ( checkSwitch("--mincritters", mincritters, mincrittersMin, mincrittersMax, optind, argv) ) optind++;
		else if ( checkSwitch("--retinasperrow", retinasperrow, retinasperrowMin, retinasperrowMax, optind, argv) ) optind++;
		else if ( checkSwitch("--camerasensitivity", camerasensitivity, camerasensitivityMin, camerasensitivityMax, optind, argv) ) optind++;
		else if ( sw=="--exit-if-empty") exit_if_empty = true;

	// Critter Settings

		else if ( checkSwitch("--critter_maxlifetime", critter_maxlifetime, critter_maxlifetimeMin, critter_maxlifetimeMax, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_maxenergy", critter_maxenergy, critter_maxenergyMin, critter_maxenergyMax, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_startenergy", critter_startenergy, critter_startenergyMin, critter_startenergyMax, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_procinterval", critter_procinterval, critter_procintervalMin, critter_procintervalMax, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_fireinterval", critter_fireinterval, critter_fireintervalMin, critter_fireintervalMax, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_minenergyproc", critter_minenergyproc, critter_minenergyprocMin, critter_minenergyprocMax, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_minenergyfire", critter_minenergyfire, critter_minenergyfireMin, critter_minenergyfireMax, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_size", critter_sizeI, critter_sizeIMin, critter_sizeIMax, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_speed", critter_speedI, critter_speedIMin, critter_speedIMax, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_sightrange", critter_sightrangeI, critter_sightrangeIMin, critter_sightrangeIMax, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_retinasize", critter_retinasize, critter_retinasizeMin, critter_retinasizeMax, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_colorneurons", critter_colorneurons, critter_colorneuronsMin, critter_colorneuronsMax, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_mutationrate", critter_mutationrate, critter_mutationrateMin, critter_mutationrateMax, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_maxmutations", critter_maxmutations, critter_maxmutationsMin, critter_maxmutationsMax, optind, argv) ) optind++;
		else if ( checkSwitch("--critter_percentchangetype", critter_percentchangetype, critter_percentchangetypeMin, critter_percentchangetypeMax, optind, argv) ) optind++;
		else if (sw=="--critter_flipnewborns") critter_flipnewborns = true;
		else if (sw=="--critter_randomrotatenewborns") critter_randomrotatenewborns = true;
		else if ( checkSwitch("--critter_autosaveinterval", critter_autosaveinterval, critter_autosaveintervalMin, critter_autosaveintervalMax, optind, argv) ) optind++;

	// Food Settings

		else if ( checkSwitch("--food_maxlifetime", food_maxlifetime, food_maxlifetimeMin, food_maxlifetimeMax, optind, argv) ) optind++;
		else if ( checkSwitch("--food_maxenergy", food_maxenergy, food_maxenergyMin, food_maxenergyMax, optind, argv) ) optind++;
		else if ( checkSwitch("--food_size", food_sizeI, food_sizeIMin, food_sizeIMax, optind, argv) ) optind++;

	// Corpse Settings

		else if (sw=="--corpse_enable") corpse_enable = true;
		else if ( checkSwitch("--corpse_maxlifetime", corpse_maxlifetime, corpse_maxlifetimeMin, corpse_maxlifetimeMax, optind, argv) ) optind++;
		else if ( checkSwitch("--corpse_maxenergy", corpse_maxenergy, corpse_maxenergyMin, corpse_maxenergyMax, optind, argv) ) optind++;
		else if ( checkSwitch("--corpse_size", corpse_sizeI, corpse_sizeIMin, corpse_sizeIMax, optind, argv) ) optind++;

	// Brain Settings

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

