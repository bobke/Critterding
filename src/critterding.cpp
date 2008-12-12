#include "gl/glwindow.h"
#include "scenes/evolution.h"
#include "utils/settings.h"

using namespace std;

Settings *settings = Settings::Instance();

int main(int argc, char *argv[])
{

	settings->doCommandLineOptions(argc,argv);

	GLWindow glwindow;
	glwindow.create("Critterding beta9", 600, 600, 24, False);

		Evolution mainscene;

		mainscene.camera.position = Vector3f(-0.5f*settings->worldsize, -1.1f*settings->worldsize, -0.9f*settings->worldsize);
		mainscene.camera.sensitivity = settings->camerasensitivity;

		// global
		mainscene.world.resize(settings->worldsize);
		mainscene.world.startfoodamount(settings->startenergy);

		settings->printSettings();

		if (settings->autoload)
			mainscene.world.loadAllCritters();

		mainscene.world.createWall();

		glwindow.runGLScene(mainscene);

	glwindow.destroy();
}
