#include "gl/glwindow.h"
#include "scenes/evolution.h"

using namespace std;

// Global Settings
	unsigned int worldsize			= 25;
	unsigned int energy			= 500;
	unsigned int mincritters		= 10;
	unsigned int startcritters		= 0;
	unsigned int retinasperrow		= 20;

// Critter Settings
	unsigned int critter_maxlifetime	= 2000;
	unsigned int critter_maxenergy		= 5000;
	float        critter_size		= 0.1f;
	float        critter_speed		= 0.05f;
	float        critter_sightrange		= 4.0f;
	unsigned int critter_visionres		= 7;
	unsigned int critter_colorneurons	= 3;
	unsigned int critter_mutationrate	= 10;
	unsigned int critter_maxmutateruns	= 1;

// Food Settings
	unsigned int food_maxlifetime		= 1000;
	unsigned int food_maxenergy		= 2500;
	float        food_size			= 0.15f;

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
		else if (sw=="--startcritters")
		{
			optind++;
			startcritters = atoi(argv[optind]);
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
		else if (sw=="--critter_visionres")
		{
			optind++;
			critter_visionres = atoi(argv[optind]);
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

		else
		{
			cout << "Unknown switch: " << argv[optind] << endl;
		}
		optind++;
	}

	// report settings
	cout << endl << "Global Settings" << endl;
	cout << "  World Size                  = " << worldsize << "x" << worldsize << endl;
	cout << "  Energy in system            = " << energy << "*" << food_maxenergy << " = " << energy*food_maxenergy << endl;
	cout << "  Minimal Amount of Critters  = " << mincritters << endl;
	cout << "  Starting Amount of critters = " << startcritters << endl;
	cout << "  Retinas per row             = " << retinasperrow << endl;

	cout << endl << "Critter Settings" << endl;
	cout << "  Lifetime                    = " << critter_maxlifetime << endl;
	cout << "  Maximum Energy              = " << critter_maxenergy << endl;
	cout << "  Size                        = " << critter_size*100.0f << endl;
	cout << "  Speed                       = " << critter_speed*1000.0f << endl;
	cout << "  Sight Range                 = " << critter_sightrange*10.0f << endl;
	cout << "  Vision Resolution           = " << critter_visionres << endl;
	cout << "  Color Neurons               = " << critter_colorneurons << endl;
	cout << "  Mutation Rate               = " << critter_mutationrate << endl;
	cout << "  Mutation Runs               = " << critter_maxmutateruns << endl;



	cout << endl << "Food Settings" << endl;
	cout << "  Lifetime                    = " << food_maxlifetime << endl;
	cout << "  Maximum Energy              = " << food_maxenergy << endl;
	cout << "  Size                        = " << food_size*100.0f << endl;

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

		mainscene.world.critter_maxlifetime = critter_maxlifetime;
		mainscene.world.critter_maxenergy = critter_maxenergy;
		mainscene.world.critter_size = critter_size;
		mainscene.world.critter_speed = critter_speed;
		mainscene.world.critter_sightrange = critter_sightrange;
		mainscene.world.critter_visionres = critter_visionres;
		mainscene.world.critter_colorneurons = critter_colorneurons;
		mainscene.world.critter_maxmutateruns = critter_maxmutateruns;
		mainscene.world.critter_mutationrate = critter_mutationrate;

		mainscene.world.food_maxlifetime = food_maxlifetime;
		mainscene.world.food_maxenergy = food_maxenergy;
		mainscene.world.food_size = food_size;

		mainscene.world.retinasperrow = retinasperrow;
		mainscene.world.resize(worldsize);
		mainscene.world.startfoodamount(energy);
		mainscene.world.setMincritters(mincritters);
		for (unsigned int i=0; i < startcritters; i++) mainscene.world.insertCritter();


		glwindow.runGLScene(mainscene);

	glwindow.destroy();
}
