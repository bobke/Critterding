#include "headless.h"

Headless::Headless()
{
}

void Headless::create()
{
	w_width = 0;
	w_height = 0;
	Settings::Instance()->winWidth = &w_width;
	Settings::Instance()->winHeight = &w_height;
}

void Headless::runGLScene(GLScene* glscene)
{
	while(1)
		glscene->draw();

	SDL_Quit();
	exit(0);
}


Headless::~Headless()
{

}


