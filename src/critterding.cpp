#include "gl/glwindow.h"
#include "scenes/evolution.h"

using namespace std;

unsigned int worldsizeparam = 25;
unsigned int foodparam = 500;

unsigned int mincritters = 10;
unsigned int startcritters = 0;

unsigned int mutationrate = 10;
unsigned int maxmutateruns = 1;

unsigned int critterenergy = 5000;
unsigned int foodenergy = 2500;

unsigned int critterlifetime = 2000;
unsigned int foodlifetime = 2000;

unsigned int retinasperrow = 20;

float crittersize = 0.1f;
float foodsize = 0.15f;

float critterspeed = 0.05f;

float crittersightrange = 4.0f;


int main(int argc, char *argv[])
{

	int optind=1;
	// decode arguments
	while ((optind < argc) && (argv[optind][0]=='-'))
	{
		string sw = argv[optind];
		if (sw=="--worldsize")
		{
			optind++;
			worldsizeparam = atoi(argv[optind]);
	        }
		else if (sw=="--food")
		{
			optind++;
			foodparam = atoi(argv[optind]);
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
		else if (sw=="--mutationrate")
		{
			optind++;
			mutationrate = atoi(argv[optind]);
	        }
		else if (sw=="--maxmutateruns")
		{
			optind++;
			maxmutateruns = atoi(argv[optind]);
	        }
		else if (sw=="--critterenergy")
		{
			optind++;
			critterenergy = atoi(argv[optind]);
	        }
		else if (sw=="--foodenergy")
		{
			optind++;
			foodenergy = atoi(argv[optind]);
	        }
		else if (sw=="--critterspeed")
		{
			optind++;
			critterspeed = (float)atoi(argv[optind]) / 1000.0f;
	        }
		else if (sw=="--critterlifetime")
		{
			optind++;
			critterlifetime = atoi(argv[optind]);
	        }
		else if (sw=="--foodlifetime")
		{
			optind++;
			foodlifetime = atoi(argv[optind]);
	        }
		else if (sw=="--crittersize")
		{
			optind++;
			crittersize = (float)atoi(argv[optind]) / 100.0f;
	        }
		else if (sw=="--foodsize")
		{
			optind++;
			foodsize = (float)atoi(argv[optind]) / 100.0f;
	        }
		else if (sw=="--retinasperrow")
		{
			optind++;
			retinasperrow = atoi(argv[optind]);
	        }
		else if (sw=="--crittersightrange")
		{
			optind++;
			crittersightrange = (float)atoi(argv[optind]) / 10.0f;
	        }

		else
		{
			cout << "Unknown switch: " << argv[optind] << endl;
		}
		optind++;
	}

	// report settings
	cout << "World Size = " << worldsizeparam << "x" << worldsizeparam << endl;
	cout << "Food Amount = " << foodparam << endl;
	cout << "Minimum Critters = " << mincritters << endl;
	cout << "Starting Amount of critters = " << startcritters << endl;
	cout << "Mutation Runs per Mutating Critter = " << maxmutateruns << endl;
	cout << "Critter Mutation Rate = " << mutationrate << endl;

	cout << "Critter Energy = " << critterenergy << endl;
	cout << "Food Energy = " << foodenergy << endl;

	cout << "Critter Lifetime = " << critterlifetime << endl;
	cout << "Food Lifetime = " << foodlifetime << endl;

	cout << "Critter Size = " << crittersize*100.0f << endl;
	cout << "Food Size = " << foodsize*100.0f << endl;

	cout << "Critter Speed = " << critterspeed*1000.0f << endl;

	cout << "Retinas per row = " << retinasperrow << endl;

	cout << "Critter Sight Range = " << crittersightrange*10.0f << endl;



	cout << "Remaining arguments = ";
	for (;optind<argc;optind++)
	{
		cout << argv[optind];
	}
	cout << endl << endl;

	//cerr << "Starting application" << endl;
	GLWindow glwindow;
	glwindow.create("Critterding beta2", 600, 600, 24, False);

		Evolution mainscene;

		mainscene.world.resize(worldsizeparam);
		mainscene.world.foodenergy = foodenergy;
		mainscene.world.critterenergy = critterenergy;
		mainscene.world.foodsize = foodsize;
		mainscene.world.crittersize = crittersize;
		mainscene.world.startfoodamount(foodparam);
		mainscene.world.setMincritters(mincritters);
		mainscene.world.maxMutateRuns = maxmutateruns;
		mainscene.world.mutationRate = mutationrate;
		mainscene.world.critterspeed = critterspeed;
		mainscene.world.critterlifetime = critterlifetime;
		mainscene.world.foodlifetime = foodlifetime;
		mainscene.world.retinasperrow = retinasperrow;
		mainscene.world.critterSightRange = crittersightrange;


		for (unsigned int i=0; i < startcritters; i++) mainscene.world.insertCritter();

		glwindow.runGLScene(mainscene);

	glwindow.destroy();
}
