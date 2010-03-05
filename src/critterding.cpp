#include "gl/glwindow.h"
#include "utils/headless.h"
#include "scenes/evolution.h"
#include "utils/settings.h"

using namespace std;

int main(int argc, char* argv[])
{
	Settings *settings = Settings::Instance();
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
