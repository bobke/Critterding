#include "gl/glwindow.h"
#include "scenes/evolution.h"
#include "utils/settings.h"

using namespace std;

Settings *settings = Settings::Instance();

int main(int argc, char *argv[])
{

	settings->doCommandLineOptions(argc,argv);

	GLWindow glwindow;
// 	glwindow.create("Critterding 2.01 alpha", 1920, 1200, 24);
	glwindow.create("Critterding 2.01 alpha", 640, 640, 24);

	Evolution* mainscene = new Evolution();

	glwindow.runGLScene(mainscene);
	
	delete mainscene;

}
