#include "gl/glwindow.h"
#include "scenes/evolution.h"
#include "utils/settings.h"

using namespace std;

Settings *settings = Settings::Instance();

int main(int argc, char *argv[])
{

	settings->doCommandLineOptions(argc,argv);

	GLWindow glwindow;
	glwindow.create("Critterding beta11", 800, 600);

	Evolution* mainscene = new Evolution();

		glwindow.runGLScene(mainscene);

	delete mainscene;

}
