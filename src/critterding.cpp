#include "gl/glwindow.h"
#include "scenes/evolution.h"

int main(int argc, char *argv[])
{

	//cerr << "Starting application" << endl;
	GLWindow glwindow;
	glwindow.create("Critterding 0.01", 320, 300, 24, False);

		Evolution mainscene;
		glwindow.runGLScene(mainscene);

	glwindow.destroy();
}
