#include "infobar.h"

Infobar::Infobar()
{
	critters = 0;
	food = 0;
	corpses = 0;
	bullets = 0;

	active = true;
}

void Infobar::draw()
{
	if (active)
	{
		fps.mark();

		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glColor4f(0.05f, 0.05f, 0.05f, 0.9f);
		glBegin(GL_QUADS);
			glVertex2f(0.0f, 36.0f);
			glVertex2f(0.0f, 0.0f);
			glVertex2f(*Settings::Instance()->winWidth, 0.0f);
			glVertex2f(*Settings::Instance()->winWidth, 36.0f);
		glEnd();
		glDisable(GL_BLEND);

		glEnable(GL_TEXTURE_2D);

		glColor3f(1.0, 1.0, 1.0);

		Textprinter::Instance()->print(5.0f, 15.0f, "fps: %7.0f", fps.currentfps);
		Textprinter::Instance()->print((*Settings::Instance()->winWidth/4), 15.0f, "critters: %7u", critters);
		Textprinter::Instance()->print((*Settings::Instance()->winWidth/4)*2, 15.0f, "food: %4u/%4u", food, (unsigned int)(Settings::Instance()->freeEnergyInfo/Settings::Instance()->food_maxenergy));
		Textprinter::Instance()->print((*Settings::Instance()->winWidth/4)*3, 15.0f, "corpses: %3u", corpses);
		Textprinter::Instance()->print(5.0f, 30.0f, "n/c: %6.2f", (float)Settings::Instance()->totalNeurons / critters);
		Textprinter::Instance()->print((*Settings::Instance()->winWidth/4), 30.0f, "s/c: %10.2f", (float)Settings::Instance()->totalSynapses / critters);
		Textprinter::Instance()->print((*Settings::Instance()->winWidth/4)*2, 30.0f, "s/n: %10.2f", (float)Settings::Instance()->totalSynapses / Settings::Instance()->totalNeurons);
		Textprinter::Instance()->print((*Settings::Instance()->winWidth/4)*3, 30.0f, "bullets: %3u", bullets);

		glDisable(GL_TEXTURE_2D);
	}
}

void Infobar::swap()
{
	active = !active;
}

Infobar::~Infobar()
{
}
