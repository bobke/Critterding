#include "gl/glwindow.h"
#include "scenes/evolution.h"
#include "utils/settings.h"

using namespace std;

Settings *settings = Settings::Instance();

int main(int argc, char *argv[])
{

	settings->doCommandLineOptions(argc,argv);

	GLWindow glwindow;
	glwindow.create("Critterding beta9", 640, 480, 24);

		Evolution mainscene;

		// global
		mainscene.world.resize(settings->worldsizeX, settings->worldsizeY);
		mainscene.world.startfoodamount(settings->startenergy);

		//settings->printSettings();

		if (settings->autoload)
			mainscene.world.loadAllCritters();

		mainscene.world.createWall();

		mainscene.resetCamera();
		mainscene.camera.sensitivity = settings->camerasensitivity;

		glwindow.runGLScene(mainscene);

	glwindow.destroy();
}
