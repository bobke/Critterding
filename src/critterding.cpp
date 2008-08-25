#include "gl/glwindow.h"
#include "scenes/evolution.h"

using namespace std;

unsigned int worldsizeparam = 25;
unsigned int foodparam = 500;
unsigned int mincritters = 10;
unsigned int startcritters = 0;
unsigned int mutationrate = 10;
unsigned int maxmutateruns = 3;

// double  dparam=0;
// string  sparam="";
// int     fparam=0;

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
		else
		{
			cout << "Unknown switch: " << argv[optind] << endl;
		}
		optind++;
	}

	// report settings
	cout << "World Size = " << worldsizeparam << endl;
	cout << "Food Amount = " << foodparam << endl;
	cout << "Minimum Critters = " << mincritters << endl;
	cout << "Starting Amount of critters = " << startcritters << endl;
	cout << "Mutation Runs per Mutating Critter = " << maxmutateruns << endl;
	cout << "Critter Mutation Rate = " << mutationrate << endl;
	cout << "Remaining arguments = ";
	for (;optind<argc;optind++)
	{
		cout << argv[optind];
	}
	cout << endl;

	//cerr << "Starting application" << endl;
	GLWindow glwindow;
	glwindow.create("Critterding 0.01", 600, 600, 24, False);

		Evolution mainscene;

		mainscene.world.resize(worldsizeparam);
		mainscene.world.startfoodamount(foodparam);
		mainscene.world.setMincritters(mincritters);
		mainscene.world.maxMutateRuns = maxmutateruns;
		mainscene.world.mutationRate = mutationrate;

		for (unsigned int i=0; i < startcritters; i++) mainscene.world.insertCritter();

		glwindow.runGLScene(mainscene);

	glwindow.destroy();
}
