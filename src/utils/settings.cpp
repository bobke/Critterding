#include "settings.h"

Settings* Settings::Instance () 
{
	static Settings t;
	return &t;
}

Settings::Settings()
{
	profileName			= "default";

	registerCVar("fullscreen",						0, 0, 1, true, "enable fullscreen mode");
	registerCVar("threads",							1, 1, 16, false, "threads to use");
	registerCVar("headless",						0, 0, 1, true, "do not open gl context");
	registerCVar("drawscene",						1, 0, 1, true, "draw the scene");
	registerCVar("fsX",							800, 1, 1000000, false, "fullscreen resolution X");
	registerCVar("fsY",							600, 1, 1000000, false, "fullscreen resolution Y");
	registerCVar("startseed",						0, 0, 4000000000, true, "enable fullscreen mode");
	registerCVar("benchmark",						0, 0, 1, true, "run the critterding benchmark");

	registerCVar("race",							0, 0, 1, false, "enable race simulation");
	registerCVar("roundworld",						0, 0, 1, false, "enable round planet");
	registerCVar("testworld",						0, 0, 1, false, "a world for test purposes");

	registerCVar("worldsizeX",						23, 1, 5000, false, "size of the world along axis X");
	registerCVar("worldsizeY",						13, 1, 5000, false, "size of the world along axis Y");
	registerCVar("worldwalls",						1, 0, 1, false, "enable walls around the world");

	registerCVar("killhalf_decrenergypct",					1, 0, 100, false, "decrease energy by n percent when killhalfat triggers");
	registerCVar("killhalf_incrworldsizeX",					0, 0, 100, false, "increase worldsizeX by n when killhalfat triggers");
	registerCVar("killhalf_incrworldsizeY",					0, 0, 100, false, "increase worldsizeY by n when killhalfat triggers");
	registerCVar("killhalf_decrmaxlifetimepct",				0, 0, 100, false, "decrease critter_maxlifetime by n when killhalfat triggers");

	registerCVar("energy",							400, 0, 1000000, false, "energy in the system by number of food cubes");
	registerCVar("mincritters",						10, 0, 1000, false, "minimum number of critters");

	registerCVar("retinasperrow",						20, 1, 1000, false, "number of vision retinas to stack per row onscreen");
	registerCVar("camerasensitivity",					20, 1, 1000, false, "sensitivity of the camera");

	registerCVar("colormode",						0, 0, 1, true, "colors genetically exact critters identically");
	registerCVar("exit_if_empty",						0, 0, 1, true, "exit simulation if there are no critters");
	registerCVar("autoload",						0, 0, 1, true, "autoload critters from ~/.critterding/load");
	registerCVar("autoloadlastsaved",					0, 0, 1, true, "autoload critters from ~/.critterding/lastsaved");
	registerCVar("fpslimit",						30, 1, 1000, false, "frames per second for the fps limiter");

	registerCVar("critter_insertevery",					0, 0, 1000000, false, "inserts a random critter every n frames");
	registerCVar("critter_maxlifetime",					40000, 1, 1000000, false, "maximum number of frames a critter lives");
	registerCVar("critter_maxenergy",					5000, 1, 1000000, false, "maximum amount of energy a critter has");

	registerCVar("critter_startenergy",					3000, 1, 1000000, false, "energy a new critter (adam) starts with");
	registerCVar("critter_procinterval",					20, 1, 1000000, false, "minimum frames between procreations");
	registerCVar("critter_minenergyproc",					3000, 1, 1000000, false, "energy a critters needs to procreate");
	registerCVar("critter_sightrange",					70, 1, 1000000, false, "distance a critter can see (10 = 1 worldsize)");

	registerCVar("critter_retinasize",					8, 1, 1000, false, "size of a critters eye retina");
	registerCVar("critter_autosaveinterval",				0, 0, 1000000, false, "save critters every n seconds");
	registerCVar("critter_autoexchangeinterval",				0, 0, 1000000, false, "save critters every n seconds");
	registerCVar("critter_killhalfat",					120, 2, 1000000, false, "kill 50% of critters if population reaches n");
	registerCVar("critter_enableomnivores",					1, 0, 1, true, "enables critters to eat each other");
	registerCVar("critter_raycastvision",					0, 0, 1, true, "use raycast vision instead of opengl");
	
	registerCVar("food_maxlifetime",					10000, 1, 1000000, false, "maximum number of frames a food unit exists");
	registerCVar("food_maxenergy",						1500, 1, 1000000, false, "maximum amount of energy a food unit has");
	registerCVar("food_size",						200, 1, 1000000, false, "size of a food unit");

	registerCVar("body_maxmutations",					3, 1, 1000000, false, "maximum mutations on a body mutant");
	registerCVar("body_mutationrate",					10, 0, 100, false, "percentage of newborns that mutate bodies");

	registerCVar("body_maxbodyparts",					30, 0, 1000000, false, "maximum body parts per critter");
	registerCVar("body_maxbodypartsatbuildtime",				6, 1, 1000000, false, "maximum body parts for a new critter");

	registerCVar("body_minbodypartsize",					20, 1, 1000000, false, "minimum size of a critters body part");
	registerCVar("body_maxbodypartsize",					200, 1, 1000000, false, "maximum size of a critters body part");
	registerCVar("body_minheadsize",					30, 1, 1000000, false, "minimum size of a critters head");
	registerCVar("body_maxheadsize",					80, 1, 1000000, false, "maximum size of a critters head");

	registerCVar("body_percentmutateeffectchangecolor",			1, 0, 100, false, "chance of changing body color");
	registerCVar("body_percentmutateeffectchangecolor_slightly",		5, 0, 100, false, "chance of changing body color");
	registerCVar("body_percentmutateeffectaddbodypart",			1, 0, 100, false, "chance of adding a body part");
	registerCVar("body_percentmutateeffectremovebodypart",			1, 0, 100, false, "chance of removing a body part");
	registerCVar("body_percentmutateeffectresizebodypart",			1, 0, 100, false, "chance of resizing a body part");
	registerCVar("body_percentmutateeffectresizebodypart_slightly",		5, 0, 100, false, "chance of slightly resizing a body part");
	registerCVar("body_percentmutateeffectchangeconstraintlimits",		1, 0, 100, false, "chance of changing a joints motion limits");
	registerCVar("body_percentmutateeffectchangeconstraintlimits_slightly",	5, 0, 100, false, "chance of slightly changing a joints motion limits");
	registerCVar("body_percentmutateeffectchangeconstraintangles",		1, 0, 100, false, "chance of changing a joints position angles");
	registerCVar("body_percentmutateeffectchangeconstraintangles_slightly",	5, 0, 100, false, "chance of changing a joints position angles");
	registerCVar("body_percentmutateeffectchangeconstraintposition",	1, 0, 100, false, "chance of changing a joints position");
	registerCVar("body_percentmutateeffectchangeconstraintposition_slightly", 5, 0, 100, false, "chance of slightly changing a joints position");
	registerCVar("body_percentmutateeffectresizehead",			1, 0, 100, false, "chance of resizing a head");
	registerCVar("body_percentmutateeffectresizehead_slightly",		5, 0, 100, false, "chance of slightly resizing a head");
	registerCVar("body_percentmutateeffectrepositionhead",			5, 0, 100, false, "chance of repositioning head");

	registerCVar("brain_maxmutations",					10, 1, 1000000, false, "maximum mutations on a brain mutant");
	registerCVar("brain_mutationrate",					10, 0, 100, false, "percentage of newborns that mutate brains");

	registerCVar("brain_maxneurons",					1000, 1, 1000000, false, "maximum neurons per critter");
	registerCVar("brain_minsynapses",					1, 1, 1000000, false, "minimum synapses per neuron");
	registerCVar("brain_maxsynapses",					100, 1, 1000000, false, "maximum synapses per neuron");
	registerCVar("brain_minneuronsatbuildtime",				50, 1, 1000000, false, "minimum neurons for a new critter");
	registerCVar("brain_maxneuronsatbuildtime",				200, 1, 1000000, false, "maximum neurons for a new critter");

	registerCVar("brain_minsynapsesatbuildtime",				1, 1, 1000000, false, "minimum synapses for a new neuron");
	registerCVar("brain_maxsynapsesatbuildtime",				40, 1, 1000000, false, "maximum synapses for a new neuron of a new critter");

	registerCVar("brain_percentchanceinhibitoryneuron",			50, 0, 100, false, "percent chance a neuron is inhibotory");
	registerCVar("brain_mutate_percentchanceinhibitoryneuron",		0, 0, 1, true, "mutate this value");

	registerCVar("brain_percentchancemotorneuron",				50, 0, 100, false, "percent chance a neuron is a motor neuron");
	registerCVar("brain_mutate_percentchancemotorneuron",			0, 0, 1, true, "mutate this value");

	registerCVar("brain_percentchanceplasticneuron",			20, 0, 100, false, "percent chance a neuron has plastic synapses");
	registerCVar("brain_mutate_percentchanceplasticneuron",			0, 0, 1, true, "mutate this value");

	registerCVar("brain_minplasticitystrengthen",				100, 1, 1000000, false, "minimum weight by which plastic synapses strengthen");
	registerCVar("brain_maxplasticitystrengthen",				1000, 1, 1000000, false, "maximum weight by which plastic synapses strengthen");
	registerCVar("brain_minplasticityweaken",				1000, 1, 1000000, false, "minimum weight by which plastic synapses weaken");
	registerCVar("brain_maxplasticityweaken",				10000, 1, 1000000, false, "maximum weight by which plastic synapses weaken");
	registerCVar("brain_mutate_plasticityfactors",				0, 0, 1, true, "mutate min/max plasticity values");

	registerCVar("brain_minfiringthreshold",				2, 1, 1000000, false, "minimum firingthreshold of a neuron");
	registerCVar("brain_mutate_minfiringthreshold",				0, 0, 1, true, "mutate this value");

	registerCVar("brain_maxfiringthreshold",				10, 1, 1000000, false, "maximum firingthreshold of a neuron");
	registerCVar("brain_mutate_maxfiringthreshold",				0, 0, 1, true, "mutate this value");

	registerCVar("brain_maxdendridicbranches",				3, 1, 1000000, false, "maximum number of dendrites per neuron");
	registerCVar("brain_mutate_maxdendridicbranches",			0, 0, 1, true, "mutate this value");

	registerCVar("brain_percentchanceconsistentsynapses",			0, 0, 100, false, "percent chance a neurons synapses are all inhibitory or excitatory");
	registerCVar("brain_mutate_percentchanceconsistentsynapses",		0, 0, 1, true, "mutate this value");

	registerCVar("brain_percentchanceinhibitorysynapses",			50, 0, 100, false, "percent chance a synapse is inhibitory");
	registerCVar("brain_mutate_percentchanceinhibitorysynapses",		0, 0, 1, true, "mutate this value");

	registerCVar("brain_percentchancesensorysynapse",			20, 0, 100, false, "percent change a synapse connects to an input");
	registerCVar("brain_mutate_percentchancesensorysynapse",		0, 0, 1, true, "mutate this value");

	registerCVar("brain_percentmutateeffectaddneuron",			1, 0, 100, false, "chance of adding a neuron");
	registerCVar("brain_percentmutateeffectremoveneuron",			1, 0, 100, false, "chance of removing a neuron");
	registerCVar("brain_percentmutateeffectalterneuron",			2, 0, 100, false, "chance of altering a neuron");
	registerCVar("brain_percentmutateeffectaddsynapse",			5, 0, 100, false, "chance of adding a synapse");
	registerCVar("brain_percentmutateeffectremovesynapse",			5, 0, 100, false, "chance of removing a synapse");
	registerCVar("brain_mutate_mutateeffects",				0, 0, 1, true, "mutate mutation effects");

	registerCVar("brain_percentmutateeffectaltermutable",			1, 0, 100, false,"mutate value of a mutatable option");

	registerCVar("brain_costhavingneuron",					50, 0, 1000000, false, "cost of having a neuron (1/100000 energy)");
	registerCVar("brain_costfiringneuron",					10, 0, 1000000, false, "cost of firing a neuron");
	registerCVar("brain_costfiringmotorneuron",				100, 0, 1000000, false, "cost of firing a motor neuron");
	registerCVar("brain_costhavingsynapse",					1, 0, 1000000, false, "cost of having a synapse");

	dirlayout = Dirlayout::Instance();
	
	createHelpInfo();
}

void Settings::registerCVar(const string& name, const unsigned int& defaultvalue, const unsigned int& min_val, const unsigned int& max_val, const string& comment)
{
	registerCVar( name, defaultvalue, min_val, max_val, false, comment );
}

void Settings::registerCVar(const string& name, const unsigned int& defaultvalue, const unsigned int& min_val, const unsigned int& max_val, bool loop, const string& comment)
{
	cvar* v = new cvar();

	v->int_val = defaultvalue;
	v->int_min = min_val;
	v->int_max = max_val;
	v->loop = loop;
	v->comment = comment;

	unregisterCVar(name);
	cvarlist[name] = v;

// 	cvarlist[name]->loop = true;
}

void Settings::registerLocalCVar(const string& name, const unsigned int& defaultvalue, const unsigned int& min_val, const unsigned int& max_val, bool loop, const string& comment)
{
	cvar* v = new cvar();

	v->int_val = defaultvalue;
	v->int_min = min_val;
	v->int_max = max_val;
	v->loop = loop;
	v->local = true;
	v->comment = comment;

	unregisterCVar(name);
	cvarlist[name] = v;

// 	cvarlist[name]->loop = true;
}

unsigned int Settings::getCVar(const string& name)
{
// 	cerr << "asking for " << name << endl;

	// the fast"er" way
// 	return cvarlist[name]->int_val;
	
	// the slow way
	cvarit = cvarlist.find(name);
	if ( cvarit != cvarlist.end() )
		return cvarit->second->int_val;
	else 
		cerr << "getCVar: no such key: " << name << endl;

	return 0;
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

// FIXME private
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

// FIXME private
void Settings::decreaseCVar(const string& name, const unsigned int& value)
{
	unsigned int diff = cvarlist[name]->int_val - value;
	if ( diff >= cvarlist[name]->int_min && diff <= cvarlist[name]->int_max )
		cvarlist[name]->int_val -= value;
}

void Settings::increaseCVar(const string& name)
{
	unsigned int diff = cvarlist[name]->int_val + 1;
	if ( diff >= cvarlist[name]->int_min && diff <= cvarlist[name]->int_max )
		cvarlist[name]->int_val = diff;
	else if ( cvarlist[name]->loop )
	{
		cvarlist[name]->int_val = cvarlist[name]->int_min;
	}
	stringstream buf;
	buf << name << ": " << getCVar(name);
	Logbuffer::Instance()->add(buf);
}

void Settings::decreaseCVar(const string& name)
{
	int diff = -1 + cvarlist[name]->int_val;
	if ( diff >= (int)cvarlist[name]->int_min && diff <= (int)cvarlist[name]->int_max )
		cvarlist[name]->int_val = (unsigned int)diff;
	stringstream buf;
	buf << name << ": " << getCVar(name);
	Logbuffer::Instance()->add(buf);
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
// 	helpinfo << "  Global Settings" << endl;

	helpinfo << endl << "  option                                                    [default] [range]      [comment]" << endl << endl;
	for( cvarit = cvarlist.begin(); cvarit != cvarlist.end(); cvarit++ )
	{
		stringstream buf("");
		buf << "  --" << cvarit->first;
// 		buf << " " << buf.str().size();
		
		for ( unsigned int i=buf.str().size(); i < 62; i++ )
			buf << " ";
		
		buf << cvarit->second->int_val;

		for ( unsigned int i=buf.str().size(); i < 72; i++ )
			buf << " ";

		buf << cvarit->second->int_min << "-" << cvarit->second->int_max;

		for ( unsigned int i=buf.str().size(); i < 85; i++ )
			buf << " ";

		buf << cvarit->second->comment;

		helpinfo << buf.str() << endl;
	}

	helpinfo << endl << " To save the default settings to a profile, press \"s\" in the simulation.  \n It will be saved to ./default and can be loaded by using \"--profile ./default\"" << endl ;
	helpinfo << endl << " Use F1 in the simulation for more information about keys." << endl;

}

void Settings::loadProfile(char* filename)
{
	cerr << "loading settins from '" << filename << "'" << endl;

	// nasty code for stripping dir names from the given profile name
	profileName = filename;
	string dirs("");
	parseH->Instance()->beginMatchesStrip( "/", profileName );
	dirs = parseH->Instance()->returnUntillStrip( "/", profileName );
	while ( !dirs.empty() )
	{
		dirs="";
		dirs = parseH->Instance()->returnUntillStrip( "/", profileName );
	}
	profileName = parseH->Instance()->returnUntillStrip( ".pro", profileName );

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
// 						exit(1);
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
	string fulldir;
	fulldir = dirlayout->savedir;
	fulldir.append("/");
	fulldir.append(profileName);

	if ( !dirH.exists(fulldir) )		dirH.make(fulldir);

	stringstream filename;
	filename << fulldir << "/" << profileName << ".pro";

	stringstream buf;
	for( cvarit = cvarlist.begin(); cvarit != cvarlist.end(); cvarit++ )
	{
		if ( !cvarit->second->local )
			buf << cvarit->first << " " << cvarit->second->int_val << endl;
	}

	fileH.save(filename.str(), buf.str());
}

void Settings::doCommandLineOptions(int argc, char *argv[])
{
	// parse argv[0] for binary path
	string path;
	path.append(argv[0]);
	size_t pos = path.find_last_of("/", path.size());
	if ( pos != string::npos )
		binarypath = path.substr( 0, pos+1 );

	// check if --help occurs, overrides the rest
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
// 				cerr << "use --help for more information" << endl;
// 				exit(1);
			}
		}

		optind++;
	}
 
	if (optind<argc)
	{
		cerr << "Unknown commandline option: " << argv[optind] << endl;
// 		cerr << "use --help for more information" << endl;
// 		exit(1);
	}
	cout << endl << endl;
}

Settings::~Settings()
{
	for( cvarit = cvarlist.begin(); cvarit != cvarlist.end(); cvarit++ )
		delete cvarit->second;
}
