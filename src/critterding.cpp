#include "gl/glwindow.h"
#include "scenes/evolution.h"
#include "utils/settings.h"

using namespace std;

Settings *settings = Settings::Instance();

int main(int argc, char *argv[])
{

	settings->doCommandLineOptions(argc,argv);

	GLWindow glwindow;
	glwindow.create("Critterding 2.01 alpha", 640, 640, 24);

		Evolution mainscene;

		// global
// 		mainscene.world.resize(settings->worldsizeX, settings->worldsizeY);

// 		settings->printSettings();

		if (settings->autoload)
			mainscene.world.loadAllCritters();

		mainscene.resetCamera();
		mainscene.camera.sensitivity = settings->camerasensitivity;

		glwindow.runGLScene(mainscene);

}
