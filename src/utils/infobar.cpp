#include "infobar.h"

Infobar::Infobar()
{
	critters = 0;
	food = 0;
	corpses = 0;

	active = true;
}

void Infobar::draw()
{
	if (active)
	{
		fps.mark();

		glPushMatrix();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glOrtho(0, *Settings::Instance()->winWidth, *Settings::Instance()->winHeight, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
			glHint(GL_FOG_HINT, GL_FASTEST);
			glDisable(GL_COLOR_MATERIAL);
			glDisable(GL_DITHER);
			glDisable(GL_POLYGON_SMOOTH);
			glDisable(GL_DEPTH_TEST);
			glDisable (GL_LIGHTING);

			glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);

			glColor4f(0.0f, 0.0f, 0.0f, 0.9f);
			glBegin(GL_QUADS);
				glVertex2f(0.0f, 20.0f);
				glVertex2f(0.0f, 0.0f);
				glVertex2f(*Settings::Instance()->winWidth, 0.0f);
				glVertex2f(*Settings::Instance()->winWidth, 20.0f);
			glEnd();

			glDisable(GL_BLEND);

			glColor4f(1.0f, 1.0f, 1.0f, 0.0f);

			glPushAttrib(GL_LIST_BIT);

			glRasterPos2f(5.0f, 15.0f);
			printGLf("fps: %3.0f", fps.currentfps);

			glRasterPos2f((*Settings::Instance()->winWidth/4), 15.0f);
			printGLf("critters: %3u", critters);
	
			glRasterPos2f((*Settings::Instance()->winWidth/4)*2, 15.0f);
			printGLf("food: %3u", food);
	
			glRasterPos2f((*Settings::Instance()->winWidth/4)*3, 15.0f);
			printGLf("corpses: %3u", corpses);

	// 		glRasterPos2f(10.0f, 75.0f);
	// 		printGLf("Energy in system: %3.0f", (settings->freeEnergyInfo / settings->food_maxenergy));

	/*		glRasterPos2f(10.0f, 90.0f);
			printGLf("Free Energy: %3.0f", world.freeEnergy);*/
			glPopAttrib();
			
		glPopMatrix();
	}
}

void Infobar::printGLf(const char *fmt, ...)
{
    va_list ap;     /* our argument pointer */
    char text[256];
    if (fmt == NULL)
        return;
    va_start(ap, fmt);  /* make ap point to first unnamed arg */
    /* FIXME: we *should* do boundschecking or something to prevent buffer
     * overflows/segmentations faults
     */
    vsprintf(text, fmt, ap);
    va_end(ap);
    glListBase(Settings::Instance()->fontbase - 32);
    glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
}

void Infobar::swap()
{
	active = !active;
	//fps.swap();
}

Infobar::~Infobar()
{
}
