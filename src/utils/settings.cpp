#include "settings.h"

Settings* Settings::Instance () 
{
	static Settings t;
	return &t;
}

Settings::Settings()
{
	profileName			= "default";

	registerCVar("worldsizeX",						16, 1, 5000);
	registerCVar("worldsizeY",						12, 1, 5000);

	registerCVar("energy",							100, 0, 1000000);
	registerCVar("mincritters",						10, 0, 1000);

	registerCVar("insertcritterevery",					0, 0, 1000);
	registerCVar("retinasperrow",						20, 1, 1000);
	registerCVar("camerasensitivity",					20, 1, 1000);

	registerCVar("colormode",						0, 0, 1, true);
	registerCVar("exit_if_empty",						0, 0, 1, true);
	registerCVar("autoload",						0, 0, 1, true);

	registerCVar("critter_maxlifetime",					10000, 1, 1000000);
	registerCVar("critter_maxenergy",					5000, 1, 1000000);

	registerCVar("critter_startenergy",					2500, 1, 1000000);
	registerCVar("critter_procinterval",					20, 1, 1000000);
	registerCVar("critter_minenergyproc",					3000, 2, 1000000);
	registerCVar("critter_sightrange",					70, 1, 1000000);

	registerCVar("critter_retinasize",					6, 1, 1000);
	registerCVar("critter_autosaveinterval",				0, 0, 1000000);
	registerCVar("critter_killhalfat",					1000, 2, 1000000);
	registerCVar("critter_enableherbivores",				0, 0, 1);
	
	registerCVar("food_maxlifetime",					2000, 1, 1000000);
	registerCVar("food_maxenergy",						1000, 1, 1000000);
// 	registerCVar("food_size",						15, 1, 100);

	registerCVar("body_maxmutations",					5, 1, 1000000);
	registerCVar("body_mutationrate",					10, 0, 100);

	registerCVar("body_maxbodyparts",					30, 0, 1000000);
	registerCVar("body_maxbodypartsatbuildtime",				5, 0, 1000000);
	
	registerCVar("body_percentmutateeffectaddbodypart",			10, 0, 100);
	registerCVar("body_percentmutateeffectremovebodypart",			10, 0, 100);
	registerCVar("body_percentmutateeffectresizebodypart",			10, 0, 100);
	registerCVar("body_percentmutateeffectchangeconstraintlimits",		10, 0, 100);
	registerCVar("body_percentmutateeffectchangeconstraintangles",		10, 0, 100);
	registerCVar("body_percentmutateeffectchangeconstraintposition",	10, 0, 100);
	registerCVar("body_percentmutateeffectrepositionmouth",			10, 0, 100);
	
	

	registerCVar("brain_maxmutations",					10, 1, 1000000);
	registerCVar("brain_mutationrate",					10, 0, 100);

	registerCVar("brain_maxneurons",					1000, 1, 1000000);
	registerCVar("brain_minsynapses",					1, 1, 1000000);
	registerCVar("brain_maxsynapses",					100, 1, 1000000);
	registerCVar("brain_minneuronsatbuildtime",				50, 1, 1000000);
	registerCVar("brain_maxneuronsatbuildtime",				200, 1, 1000000);

	registerCVar("brain_minsynapsesatbuildtime",				1, 1, 1000000);
	registerCVar("brain_mutate_minsynapsesatbuildtime",			0, 0, 1, true);

	registerCVar("brain_maxsynapsesatbuildtime",				40, 1, 1000000);
	registerCVar("brain_mutate_maxsynapsesatbuildtime",			0, 0, 1, true);

	registerCVar("brain_percentchanceinhibitoryneuron",			50, 0, 100);
	registerCVar("brain_mutate_percentchanceinhibitoryneuron",		0, 0, 1, true);

	registerCVar("brain_percentchancemotorneuron",				50, 0, 100);
	registerCVar("brain_mutate_percentchancemotorneuron",			0, 0, 1, true);

	registerCVar("brain_percentchanceplasticneuron",			20, 0, 100);
	registerCVar("brain_mutate_percentchanceplasticneuron",			0, 0, 1, true);

	registerCVar("brain_minplasticitystrengthen",				100, 1, 1000000);
	registerCVar("brain_maxplasticitystrengthen",				1000, 1, 1000000);
	registerCVar("brain_minplasticityweaken",				1000, 1, 1000000);
	registerCVar("brain_maxplasticityweaken",				10000, 1, 1000000);
	registerCVar("brain_mutate_plasticityfactors",				0, 0, 1, true);

	registerCVar("brain_minfiringthreshold",				2, 1, 1000000);
	registerCVar("brain_mutate_minfiringthreshold",				0, 0, 1, true);

	registerCVar("brain_maxfiringthreshold",				10, 1, 1000000);
	registerCVar("brain_mutate_maxfiringthreshold",				0, 0, 1, true);

	registerCVar("brain_maxdendridicbranches",				3, 1, 1000000);
	registerCVar("brain_mutate_maxdendridicbranches",			0, 0, 1, true);

	registerCVar("brain_percentchanceconsistentsynapses",			0, 0, 100);
	registerCVar("brain_mutate_percentchanceconsistentsynapses",		0, 0, 1, true);

	registerCVar("brain_percentchanceinhibitorysynapses",			50, 0, 100);
	registerCVar("brain_mutate_percentchanceinhibitorysynapses",		0, 0, 1, true);

	registerCVar("brain_percentchancesensorysynapse",			20, 0, 100);
	registerCVar("brain_mutate_percentchancesensorysynapse",		0, 0, 1, true);

	registerCVar("brain_percentmutateeffectaddneuron",			10, 0, 100);
	registerCVar("brain_percentmutateeffectremoveneuron",			10, 0, 100);
	registerCVar("brain_percentmutateeffectalterneuron",			20, 0, 100);
	registerCVar("brain_percentmutateeffectaddsynapse",			29, 0, 100);
	registerCVar("brain_percentmutateeffectremovesynapse",			29, 0, 100);
	registerCVar("brain_percentMutateEffectAlterMutable",			1, 0, 100);

	registerCVar("brain_mutate_mutateeffects",				0, 0, 1, true);

	registerCVar("brain_costhavingneuron",					50, 0, 1000000);
	registerCVar("brain_costfiringneuron",					10, 0, 1000000);
	registerCVar("brain_costfiringmotorneuron",				1000, 0, 1000000);
	registerCVar("brain_costhavingsynapse",					1, 0, 1000000);

	info_critters = 0;
	info_food = 0;

	info_totalNeurons = 0;
	info_totalSynapses = 0;
	info_totalAdamDistance = 0;
	
	createHelpInfo();
}

void Settings::registerCVar(const string& name, const unsigned int& defaultvalue, const unsigned int& min_val, const unsigned int& max_val)
{
	cvar* v = new cvar();

	v->int_val = defaultvalue;
	v->int_min = min_val;
	v->int_max = max_val;
	v->loop = false;

	unregisterCVar(name);
	cvarlist[name] = v;
}

void Settings::registerCVar(const string& name, const unsigned int& defaultvalue, const unsigned int& min_val, const unsigned int& max_val, bool loop)
{
	registerCVar( name, defaultvalue, min_val, max_val );
	cvarlist[name]->loop = true;
}

unsigned int Settings::getCVar(const string& name)
{
	return cvarlist[name]->int_val;
	
/*	cvarit = cvarlist.find(name);
	if ( cvarit != cvarlist.end() )
		return cvarit->second->int_val;
	else 
		cerr << "getCVar: no such key: " << name << endl;

	return 0;*/
}

const unsigned int* Settings::getCVarPtr(const string& name)
{
	return &cvarlist[name]->int_val;
}

bool Settings::setCVar(const string& name, const unsigned int& value)
{
	if ( value >= cvarlist[name]->int_min && value <= cvarlist[name]->int_max )
	{
		cvarlist[name]->int_val = value;
		return true;
	}
	else
	{
		cerr << name << " expects a value that is >=" << cvarlist[name]->int_min << " and <=" << cvarlist[name]->int_max << endl;
		return false;
	}
}

void Settings::increaseCVar(const string& name, const unsigned int& value)
{
	unsigned int diff = cvarlist[name]->int_val + value;
	if ( diff >= cvarlist[name]->int_min && diff <= cvarlist[name]->int_max )
		cvarlist[name]->int_val += value;
	else if ( cvarlist[name]->loop )
	{
		cvarlist[name]->int_val = cvarlist[name]->int_min;
	}
}

void Settings::decreaseCVar(const string& name, const unsigned int& value)
{
	unsigned int diff = cvarlist[name]->int_val - value;
	if ( diff >= cvarlist[name]->int_min && diff <= cvarlist[name]->int_max )
		cvarlist[name]->int_val -= value;
}

void Settings::unregisterCVar(const string& name)
{
	cvarit = cvarlist.find(name);
	if ( cvarit != cvarlist.end() )
	{
		delete cvarit->second;
		cvarlist.erase(cvarit->first);
	}
}

bool Settings::isCVar(const string& name)
{
	cvarit = cvarlist.find(name);
	if ( cvarit != cvarlist.end() )
		return true;

	return false;
}

void Settings::createHelpInfo()
{
// 	helpinfo << "STARTUP OPTIONS" << endl << endl;
// 	helpinfo << "  option           [default value]" << endl << endl;
// 	helpinfo << "  Global Settings" << endl;
// 
// 	helpinfo << "  --profile                 [none]  Load a settings profile" << endl << endl;
// 
// // 	helpinfo << "  --worldsizeX                [" << worldsizeX << "]  Width of the world (" << worldsizeX << ")" << endl;
// // 	helpinfo << "  --worldsizeY                [" << worldsizeY << "]  Depth of the world (" << worldsizeY << ")" << endl;
// // 	helpinfo << "  --energy                   [" << startenergy << "]  Energy in the system: " << startenergy << "*food_maxenergy(" << food_maxenergy << ") = " << startenergy*food_maxenergy << "" << endl;
// // 	helpinfo << "  --mincritters               [" << mincritters << "]  If less than " << mincritters << " critters are present, insert an adam" << endl;
// // 	helpinfo << "  --retinasperrow             [" << retinasperrow << "]  Place " << retinasperrow << " retinas on a row (bottom left of window)" << endl;
// // 	helpinfo << "  --camerasensitivity         [" << camerasensitivity << "]  Camera sensitivity" << endl;
// 	helpinfo << "  --exit-if-empty                   If set, the program will exit when no are left" << endl;
// 	helpinfo << "  --autoload                        If set, critters from the load directory will be loaded at startup" << endl;
// 
// 	helpinfo << endl;
// 	helpinfo << "  Critter Settings" << endl;
// 	helpinfo << "  --critter_maxlifetime     [" << critter_maxlifetime << "]  Max amount of frames a critter can live" << endl;
// 	helpinfo << "  --critter_maxenergy       [" << critter_maxenergy << "]  Max amount of energy in a critter" << endl;
// 	helpinfo << "  --critter_startenergy     [" << critter_startenergy << "]  Starting amount of energy for a new critter" << endl;
// 	helpinfo << "  --critter_procinterval      [" << critter_procinterval << "]  Time (in frames) between procreations" << endl;
// 	helpinfo << "  --critter_minenergyproc   [" << critter_minenergyproc << "]  Min amount of energy required for procreation" << endl;
// 
// 	helpinfo << "  --critter_sightrange        [" << critter_sightrangeI << "]  Distance a critter can see (" << critter_sightrangeI*10.0f << " = " << critter_sightrangeI << " floor squares)" << endl;
// 	helpinfo << "  --critter_retinasize         [" << critter_retinasize << "]  Resolution of critter's retina: " << critter_retinasize << "x" << critter_retinasize << "" << endl;
// 	helpinfo << "  --critter_autosaveinterval   [" << critter_autosaveinterval << "]  Save all critters every N seconds (0=disabled)" << endl;
// 	helpinfo << endl;
// 	helpinfo << "  Food Settings" << endl;
// 	helpinfo << "  --food_maxlifetime         [" << food_maxlifetime << "]  Maximum amount of frames food exists" << endl;
// 	helpinfo << "  --food_maxenergy          [" << food_maxenergy << "]  Maximum amount of energy in a food unit" << endl;
// 	helpinfo << "  --food_size                 [" << food_sizeI << "]  Size of a food unit" << endl;
// 	helpinfo << endl;
// 
// 	helpinfo << "  Body Settings" << endl;
// 	helpinfo << "  --body_mutationrate      [" << body_mutationrate << "]  When a critter procreates there is a " << body_mutationrate << "% chance its body will mutate" << endl;
// 	helpinfo << "  --body_maxmutations       [" << body_maxmutations << "]  When a critters body mutates, it can do " << body_maxmutations << " mutations at maximum" << endl;
// 
// 	helpinfo << endl;
// 	helpinfo << "  Brain Settings" << endl;
// 	helpinfo << "  --brain_mutationrate      [" << brain_mutationrate << "]  When a critter procreates there is a " << brain_mutationrate << "% chance its brain will mutate" << endl;
// 	helpinfo << "  --brain_maxmutations       [" << brain_maxmutations << "]  When a critters brain mutates, it can do " << brain_maxmutations << " mutations at maximum" << endl;
// 
// 	helpinfo << "  --brain_maxneurons                           [" << brain_maxneurons << "]  Max neurons per critter" << endl;
// 	helpinfo << "  --brain_minsynapses                             [" << brain_minsynapses << "]  Min synapses per neuron" << endl;
// 	helpinfo << "  --brain_maxsynapses                           [" << brain_maxsynapses << "]  Max synapses per neuron" << endl;
// 	helpinfo << "  --brain_minneuronsatbuildtime                  [" << brain_minneuronsatbuildtime << "]  Min neurons for a new critter" << endl;
// 	helpinfo << "  --brain_maxneuronsatbuildtime                  [" << brain_maxneuronsatbuildtime << "]  Max neurons for a new critter" << endl;
// 	helpinfo << "  --brain_minsynapsesatbuildtime                  [" << brain_minsynapsesatbuildtime << "]  Min synapses when creating new neuron" << endl;
// 	helpinfo << "    --brain_mutate_minsynapsesatbuildtime              If set, the value above will mutate" << endl;
// 	helpinfo << "  --brain_maxsynapsesatbuildtime                 [" << brain_maxsynapsesatbuildtime << "]  Max synapses when creating new neuron" << endl;
// 	helpinfo << "    --brain_mutate_maxsynapsesatbuildtime              If set, the value above will mutate" << endl;
// 	helpinfo << "  --brain_percentchanceinhibitoryneuron          [" << brain_percentchanceinhibitoryneuron << "]  % chance neuron is inhibitory (vs exhibitory)" << endl;
// 	helpinfo << "    --brain_mutate_percentchanceinhibitoryneuron       If set, the value above will mutate" << endl;
// 	helpinfo << "  --brain_percentchancemotorneuron               [" << brain_percentchancemotorneuron << "]  % chance a neuron is a motor neuron, this value seems" << endl;
// 	helpinfo << "                                                       high, but when it tries to create a motor neuron that is" << endl;
// 	helpinfo << "                                                       is already taken, it will stay a normal neuron" << endl;
// 	helpinfo << "    --brain_mutate_percentchancemotorneuron            If set, the value above will mutate" << endl;
// 	helpinfo << "  --brain_percentchanceplasticneuron             [" << brain_percentchanceplasticneuron << "]  % chance a neuron applies synaptic plasticity" << endl;
// 	helpinfo << "    --brain_mutate_percentchanceplasticneuron          If set, the value above will mutate" << endl;
// 	helpinfo << "  --brain_minplasticitystrengthen               [" << brain_minplasticitystrengthen << "]  Min weight by which plastic synapses strengthen (1/" << brain_minplasticitystrengthen << ")" << endl;
// 	helpinfo << "  --brain_maxplasticitystrengthen              [" << brain_maxplasticitystrengthen << "]  Max weight by which plastic synapses strengthen (1/" << brain_maxplasticitystrengthen << ")" << endl;
// 	helpinfo << "  --brain_minplasticityweaken                  [" << brain_minplasticityweaken << "]  Min weight by which plastic synapses weaken (1/" << brain_minplasticityweaken << ")" << endl;
// 	helpinfo << "  --brain_maxplasticityweaken                 [" << brain_maxplasticityweaken << "]  Max weight by which plastic synapses weaken (1/" << brain_maxplasticityweaken << ")" << endl;
// 	helpinfo << "    --brain_mutate_plasticityfactors                   If set, all values above will mutate" << endl;
// 	helpinfo << "  --brain_minfiringthreshold                      [" << brain_minfiringthreshold << "]  Min firing threshold of a neuron" << endl;
// 	helpinfo << "    --brain_mutate_minfiringthreshold                  If set, the value above will mutate" << endl;
// 	helpinfo << "  --brain_maxfiringthreshold                     [" << brain_maxfiringthreshold << "]  Max firing threshold of a neuron" << endl;
// 	helpinfo << "    --brain_mutate_maxfiringthreshold                  If set, the value above will mutate" << endl;
// 	helpinfo << "  --brain_maxdendridicbranches                    [" << brain_maxdendridicbranches << "]  Max dendridic branches per neuron" << endl;
// 	helpinfo << "    --brain_mutate_maxdendridicbranches                If set, the value above will mutate" << endl;
// 	helpinfo << "  --brain_percentchanceconsistentsynapses        [" << brain_percentchanceconsistentsynapses << "]  % chance neuron has consistent synapses" << endl;
// 	helpinfo << "                                                       meaning all (new) synapses are inhibitory or exhibitory" << endl;
// 	helpinfo << "    --brain_mutate_percentchanceconsistentsynapses     If set, the value above will mutate" << endl;
// 	helpinfo << "  --brain_percentchanceinhibitorysynapses        [" << brain_percentchanceinhibitorysynapses << "]  % chance a synapse is inhibitory (vs exhibitory)" << endl;
// 	helpinfo << "    --brain_mutate_percentchanceinhibitorysynapses     If set, the value above will mutate" << endl;
// 	helpinfo << "  --brain_percentchancesensorysynapse            [" << brain_percentchancesensorysynapse << "]  % chance a synapse connects with a sensor (inputneuron)" << endl;
// 	helpinfo << "    --brain_mutate_percentchancesensorysynapse         If set, the value above will mutate" << endl;
// 	helpinfo << "  --brain_percentmutateeffectaddneuron           [" << brain_percentmutateeffectaddneuron << "]  % chance of adding a neuron for a mutationrun" << endl;
// 	helpinfo << "  --brain_percentmutateeffectremoveneuron        [" << brain_percentmutateeffectremoveneuron << "]  % chance of removing a neuron for a mutationrun" << endl;
// 	helpinfo << "  --brain_percentmutateeffectalterneuron         [" << brain_percentmutateeffectalterneuron << "]  % chance of altering a neuron for a mutationrun" << endl;
// 	helpinfo << "  --brain_percentmutateeffectaddsynapse          [" << brain_percentmutateeffectaddsynapse << "]  % chance of adding a synapse for a mutationrun" << endl;
// 	helpinfo << "  --brain_percentmutateeffectremovesynapse       [" << brain_percentmutateeffectremovesynapse << "]  % chance of removing a synapse for a mutationrun" << endl;
// 	helpinfo << "  --brain_percentMutateEffectAlterMutable         [" << brain_percentMutateEffectAlterMutable << "]  % chance of altering a mutable" << endl;
// 
// 	helpinfo << "    --brain_mutate_mutateeffects                       If set, all values above will mutate" << endl;
// 
// 	helpinfo << "  --brain_costhavingneuron                      [" << brain_costhavingneuron << "]  Energycost per frame for having a neuron" << endl;
// 	helpinfo << "  --brain_costfiringneuron                      [" << brain_costfiringneuron << "]  Energycost per frame for firing a neuron" << endl;
// 	helpinfo << "  --brain_costfiringmotorneuron                 [" << brain_costfiringmotorneuron << "]  Energycost per frame for firing a motorneuron" << endl;
// 	helpinfo << "  --brain_costhavingsynapse                      [" << brain_costhavingsynapse << "]  Energycost per frame for having a synapse" << endl;

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
		content.append("\n");
		string line = parseH->Instance()->returnUntillStrip( "\n", content );

		while ( !content.empty() )
		{
			// trim spaces
			while ( parseH->Instance()->beginMatchesStrip( " ", line ) ) {};

			// remove comment lines
			if ( parseH->Instance()->beginMatchesStrip( "#", line ) )
				line.clear();

			if ( !line.empty() )
			{
				string sw = parseH->Instance()->returnUntillStrip( " ", line );
				if ( !sw.empty() )
				{
					if ( isCVar(sw) )
					{
						while ( parseH->Instance()->beginMatchesStrip( " ", line ) ) {};
						if ( !line.empty() )
						{
							unsigned int value = atoi( line.c_str() );
							line.clear();

							if ( !setCVar(sw, value) )
								exit(1);
						}
						else
						{
							cerr << "Option expects an argument: " << sw << endl;
							exit(1);
						}

					}
					else
					{
						cerr << "Unknown option in profile: " << sw << endl;
						exit(1);
					}
				}
				else
				{
					cerr << "Option without an argument: " << line << endl;
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

void Settings::saveProfile()
{
	stringstream buf;

	for( cvarit = cvarlist.begin(); cvarit != cvarlist.end(); cvarit++ )
		buf << cvarit->first << " " << cvarit->second->int_val << endl;

	fileH.save(profileName, buf.str());
}

void Settings::doCommandLineOptions(int argc, char *argv[])
{

	// first check if --help occurs, overrides the rest
	for (int i=1; i < argc; i++ )
	{
		string sw = argv[i];
		if ( sw == "--help" )
		{
			cout << helpinfo.str() << endl;
			exit(1);
	        }
	}

	// decode arguments
	int optind=1;
	while ((optind < argc) && (argv[optind][0]=='-'))
	{
		string sw = argv[optind];

		if ( sw=="--profile" )
		{
			if ( argv[++optind] )
			{
				loadProfile(argv[optind]);
			}
			else
			{
				cerr << "--profile expects a filename" << endl;
				exit(1);
			}
	        }

		else if ( parseH->Instance()->beginMatchesStrip( "--", sw ) )
		{
			if ( isCVar(sw) )
			{
				if ( argv[++optind] )
				{
					if ( !setCVar(sw, atoi( argv[optind] )) )
						exit(1);
				}
				else
				{
					cerr << "--" << sw << " expects an argument" << endl;
					exit(1);
				}
			}
			else
			{
				cerr << "Unknown commandline option: --" << sw << endl;
				cerr << "use --help for more information" << endl;
				exit(1);
			}
		}

		optind++;
	}
 
	if (optind<argc)
	{
		cerr << "Unknown commandline option: " << argv[optind] << endl;
		cerr << "use --help for more information" << endl;
		exit(1);
	}
	cout << endl << endl;
}

Settings::~Settings()
{
	for( cvarit = cvarlist.begin(); cvarit != cvarlist.end(); cvarit++ )
	{
// 		cout << cvarit->first <<'\t' << cvarit->second->int_val << endl;
		delete cvarit->second;
		cvarlist.erase(cvarit->first);
	}
}
