#include "gl/glwindow.h"
#include "utils/headless.h"
#include "scenes/evolution.h"
#include "utils/settings.h"

using namespace std;

Settings *settings = Settings::Instance();

int main(int argc, char *argv[])
{
	settings->doCommandLineOptions(argc,argv);

	if ( settings->getCVar("headless") )
	{
		Headless headless;
		headless.create();
		Evolution* mainscene = new Evolution();
		headless.runGLScene(mainscene);
		delete mainscene;
	}
	else
	{
		GLWindow glwindow;
		glwindow.create("Critterding beta12", 800, 600);
		Evolution* mainscene = new Evolution();
		glwindow.runGLScene(mainscene);
		delete mainscene;
	}


}
